# ft_read

Implementación de la función `ft_read` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. Esta función es un "wrapper" de la llamada al sistema (`syscall`) `read`, utilizada para leer datos desde un descriptor de archivo y guardarlos en un buffer.

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia entre los argumentos de la función C, los registros y la syscall del Kernel de Linux.

| Concepto en C | Registro / Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `int fd` | `rdi` | Primer argumento (descriptor de archivo a leer, ej. `0` para stdin). |
| `void *buf` | `rsi` | Segundo argumento (puntero al buffer donde se guardará lo leído). |
| `size_t count` | `rdx` | Tercer argumento (cantidad máxima de bytes a leer). |
| `read` (syscall) | `mov rax, 0` | `0` es el número de identificación de la syscall `read` en Linux. |
| (Transición al kernel) | `syscall` | Cede el control al SO para que ejecute la lectura. |
| `return (bytes)` | `rax` | El kernel devuelve en `rax` la cantidad de bytes leídos (o negativo si hay error). |

---

## Conceptos Clave y Aprendizajes

Tu código introduce de lleno el manejo de errores interactuando con funciones de C externas (`__errno_location`), pero esconde una "trampa" muy común relacionada con la convención de llamadas (System V ABI).

### 1. Simetría con `write`

Al igual que en `ft_write`, los argumentos en C (`fd`, `buf`, `count`) entran en los registros `rdi`, `rsi` y `rdx`. Casualmente, la syscall `read` espera sus parámetros exactamente en esos mismos registros. Por tanto, solo necesitas poner el número de syscall en `rax` (en este caso `0`) y ejecutar `syscall`.

### 2. Uso de Punteros Devueltos por C (`[rax]`)

La función de C `__errno_location` no devuelve el *valor* del error, sino **la dirección de memoria** de la variable global `errno`. Por eso, cuando haces el `call`, la dirección de memoria se guarda en `rax`. Para escribir el error real allí, usas los corchetes `[rax] = rdi`, que es el equivalente exacto en C a hacer `*errno = valor`.

### 3. ¡Peligro de Registros Destruidos (Caller-saved)!

Tu código conceptualmente es perfecto, pero **tiene un bug crítico** en estas líneas:

```assembly
mov rdi, rax
call __errno_location
mov [rax], rdi

```

Según la convención de llamadas de 64 bits, **`rdi` es un registro "Caller-saved" (volátil)**. Esto significa que cuando llamas a una función externa como `__errno_location`, esa función tiene total libertad para modificar `rdi` (y `rcx`, `rdx`, `rsi`, etc.) para sus propios cálculos internos.
Si `__errno_location` altera `rdi`, cuando intentes hacer `mov [rax], rdi`, estarás guardando basura en `errno` en lugar de tu código de error.

---

## Propuesta de Código Optimizado y Seguro

Para solucionar el problema de la destrucción de registros al llamar a funciones externas de C, la práctica más segura y común es usar **la Pila (Stack)** mediante las instrucciones `push` y `pop`.

Al guardar el valor en la pila antes del `call`, lo protegemos completamente de cualquier alteración.

```assembly
.intel_syntax noprefix
.global ft_read
.extern __errno_location    # Función de C que devuelve el puntero a errno

ft_read:
    mov rax, 0              # 0 es el código de la syscall 'read'
    syscall                 # Ejecuta la llamada al sistema

    cmp rax, 0              # Comprueba si hubo un error (resultado negativo)
    jl .error               # Salto si es menor que 0
    
    ret                     # Si todo fue bien, retorna rax (bytes leídos)

.error:
    neg rax                 # Convierte el error negativo en positivo
    push rax                # GUARDAMOS el error en la pila para protegerlo del call
    
    call __errno_location   # Obtiene la dirección de 'errno' y la deja en rax
    
    pop rcx                 # RECUPERAMOS el error de la pila (lo metemos en rcx o rdi, da igual)
    mov [rax], rcx          # Asignamos el valor del error a la dirección de errno (*errno = rcx)
    
    mov rax, -1             # La función debe devolver -1 en caso de error
    ret

```