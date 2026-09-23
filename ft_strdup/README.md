# ft_strdup

Implementación de la función `ft_strdup` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. Esta función duplica una cadena de caracteres: primero calcula su longitud, luego reserva la memoria necesaria con `malloc` (incluyendo el espacio para el carácter nulo), copia el contenido y devuelve el nuevo puntero. Si `malloc` falla, gestiona el error devolviendo `NULL` y configurando `errno`.

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia entre la lógica de alto nivel en C y el ensamblador:

| Concepto en C | Equivalente en Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `const char *s` | `rdi` | Primer argumento (puntero a la cadena original). |
| Guardar `s` temporalmente | `push rbx` <br>

<br> `mov rbx, rdi` | Se usa un registro "callee-saved" (`rbx`) para guardar el puntero original, ya que las llamadas a funciones destruirán `rdi`. |
| `len = ft_strlen(s)` | `call ft_strlen` | Llama a tu propia función. El resultado (longitud) queda en `rax`. |
| `len + 1` | `inc rax` | Suma 1 para hacer espacio para el carácter nulo terminador `\0`. |
| `malloc(len + 1)` | `mov rdi, rax` <br>

<br> `call malloc` | Mueve el tamaño a `rdi` (primer argumento) y llama a la función de la libc. Devuelve el puntero en `rax`. |
| `if (!new_string)` | `test rax, rax` <br>

<br> `je error` | Comprueba si `malloc` devolvió nulo (`0`). Si es así, salta al manejo de errores. |
| `ft_strcpy(new, s)` | `mov rdi, rax` <br>

<br> `mov rsi, rbx` <br>

<br> `call ft_strcpy` | Prepara los argumentos: `rdi` = nuevo puntero (`rax`), `rsi` = puntero original (`rbx`). `ft_strcpy` devolverá el puntero destino en `rax`. |
| `errno = ENOMEM;` (12) | `call __errno_location` <br>

<br> `mov dword ptr [rax], 12` | Obtiene la dirección de `errno` y escribe un entero de 4 bytes (12 = Out of memory). |
| `return NULL;` | `xor eax, eax` | Pone `rax` a 0 para devolver un puntero nulo. |

---

## Conceptos Clave y Aprendizajes

Este código es un hito de aprendizaje porque es la primera vez que tu ensamblador orquesta múltiples funciones (tanto tuyas como del sistema). Has dejado unos comentarios excelentes en tu código; vamos a explicar por qué son tan importantes.

### 1. Registros "Callee-saved" (`rbx`)

La regla de oro de la ABI System V x86-64 dice que registros como `rdi`, `rsi`, `rax`, `rcx`, `rdx` son **Volátiles (Caller-saved)**. Es decir, `malloc` destruirá el valor original de la cadena que tenías en `rdi`. Para sobrevivir a `malloc`, debes guardar tu cadena en un registro seguro: `rbx` es un registro **No volátil (Callee-saved)**. Sin embargo, como tú estás modificando `rbx`, tienes la obligación de restaurar su valor original antes de hacer `ret` (por eso usas `push rbx` al inicio y `pop rbx` al final).

### 2. La Alineación de la Pila (Stack Alignment)

¡Este es el motivo por el que muchos programas en ASM sufren un *Segmentation Fault* misterioso al llamar a `malloc`!
La ABI de Linux exige que **la pila (RSP) sea múltiplo de 16 bytes** justo antes de ejecutar una instrucción `call`.

* Al entrar en tu función, el `call ft_strdup` previo apiló la dirección de retorno (8 bytes), desalineando la pila.
* Al hacer `push rbx`, apilas otros 8 bytes. $8 + 8 = 16$. **¡La pila vuelve a estar alineada a 16 bytes!** Gracias a esto, puedes llamar a `malloc` sin que las instrucciones vectoriales (SSE) internas de la libc crasheen.

### 3. Tamaños de variables de C (`dword ptr`)

Como bien anotaste, `errno` en C es un `int`, y un `int` en arquitectura de 64 bits ocupa **4 bytes (32 bits)**, no 8. Si haces `mov [rax], rdi` por defecto moverá 64 bits (8 bytes), sobreescribiendo 4 bytes de memoria vecina a `errno`, lo cual puede corromper el programa. Usar `dword ptr` asegura que modificas exclusivamente los 4 bytes del entero.

### 4. `test` vs `cmp`

Como apuntaste en tus comentarios, `test rax, rax` es la forma idiomática y eficiente de comprobar si un registro es cero. Hace un "AND" a nivel de bits sin modificar el registro, ocupa menos espacio en memoria que `cmp rax, 0` y la CPU lo procesa más rápido.

---

## Propuesta de Código Optimizado

Tu lógica es perfecta. El código a continuación es simplemente tu misma versión, pero aplicando formalmente tus propios comentarios de mejora (`test`, `dword ptr`, `xor eax`) e integrando una limpieza directa para evitar cargar el 12 en `rdi` (puedes mover constantes directamente a memoria).

```assembly
.intel_syntax noprefix
.global ft_strdup
.extern ft_strlen
.extern ft_strcpy
.extern malloc
.extern __errno_location

ft_strdup:
    push rbx                # Alinea la pila a 16 bytes y guarda el valor original de rbx
    mov rbx, rdi            # Salvaguardamos el puntero a la cadena original en rbx

    call ft_strlen          # rdi ya tiene el puntero. rax = longitud de la cadena
    inc rax                 # sumamos 1 para el '\0'

    mov rdi, rax            # Pasamos (len + 1) como primer argumento para malloc
    call malloc             # Llamamos a malloc. rax = puntero al nuevo espacio (o 0 si falla)

    test rax, rax           # Comprobamos si malloc devolvió NULL (0)
    je .error               # Si rax es 0, saltamos a la gestión del error

    mov rdi, rax            # rdi = destino (el puntero recién devuelto por malloc)
    mov rsi, rbx            # rsi = origen (recuperamos el puntero original que guardamos en rbx)
    call ft_strcpy          # ft_strcpy devolverá en rax el mismo puntero destino (rdi)

    pop rbx                 # Restauramos el valor original del registro callee-saved
    ret                     # Retornamos la nueva cadena duplicada

.error:
    call __errno_location   # Obtiene la dirección de errno en rax
    mov dword ptr [rax], 12 # 12 es ENOMEM. Se usa dword ptr porque errno es un int de 4 bytes

    xor eax, eax            # eax = 0 (limpia rax por completo). Devolvemos NULL.

    pop rbx                 # Restauramos la pila y el registro original de rbx
    ret                     # Retornamos NULL (0)

```