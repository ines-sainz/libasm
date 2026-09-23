# ft_write

Implementación de la función `ft_write` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. Esta función es un "wrapper" (envoltorio) de la llamada al sistema (`syscall`) `write`, utilizada para escribir datos en un descriptor de archivo (como la terminal o un archivo de texto).

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia entre los argumentos de la función C, los registros utilizados por la convención de llamadas y los requisitos del Kernel de Linux para la syscall `write`.

| Concepto en C | Registro / Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `int fd` | `rdi` | Primer argumento (descriptor de archivo, ej. `1` para stdout). |
| `const void *buf` | `rsi` | Segundo argumento (puntero a la cadena/datos a escribir). |
| `size_t count` | `rdx` | Tercer argumento (cantidad de bytes a escribir). |
| `write` (syscall) | `mov rax, 1` | `1` es el número de identificación de la syscall `write` en Linux x86-64. |
| (Transición al kernel) | `syscall` | Interrumpe el modo usuario y cede el control al SO para que ejecute la escritura. |
| `return (bytes)` | `rax` | El kernel devuelve en `rax` la cantidad de bytes escritos (o un número negativo si hubo error). |

---

## Conceptos Clave y Aprendizajes

Tu código es extremadamente minimalista y expone una coincidencia maravillosa en la arquitectura x86-64, pero omite una parte vital del estándar de C (el manejo de errores).

### 1. La "Magia" de la Convención de Registros

En C, cuando llamas a `write(fd, buf, count)`, el compilador pone los argumentos en `rdi`, `rsi` y `rdx`. ¡Casualmente, el Kernel de Linux **también** espera los primeros tres argumentos de una syscall exactamente en `rdi`, `rsi` y `rdx`!
Por eso tu código no necesita mover ningún argumento de un registro a otro. Simplemente pones el "ID de la acción" en `rax` (`mov rax, 1`), ejecutas `syscall`, y el kernel ya sabe dónde encontrar los datos.

### 2. Syscalls vs Funciones Normales

A diferencia de `ft_strlen` o `ft_strcmp`, aquí no hay bucles ni comparaciones de memoria. Tú no estás escribiendo en la pantalla; le estás **pidiendo permiso al Sistema Operativo** para que él lo haga por ti. La instrucción `syscall` es ese puente entre tu programa (Modo Usuario) y el sistema operativo (Modo Kernel).

### 3. El Problema del Código Proporcionado (Falta `errno`)

El código que has proporcionado asume que la escritura siempre será exitosa. Sin embargo, si `write` falla (por ejemplo, si le pasas un `fd` inválido), el kernel de Linux devuelve un número de error negativo en `rax` (como `-9` para `EBADF`).
El estándar de C dicta que, si hay un error, la función debe devolver `-1` y guardar el código de error positivo en una variable global llamada `errno`. Tu código actual simplemente devolvería el número negativo directamente, lo cual rompería el comportamiento esperado de `write` en C.

---

## Propuesta de Código Optimizado y Correcto

Para que la función se comporte exactamente igual que la original en C, debemos comprobar qué devuelve el kernel tras el `syscall`. Si devuelve un número negativo, debemos llamar a la función de C `__errno_location` para obtener la dirección de memoria de la variable global `errno` y guardar allí el error.

```assembly
.intel_syntax noprefix
.global ft_write
.extern __errno_location    # Declaramos la función externa de C para el errno

ft_write:
    mov rax, 1              # 1 es el código para la syscall 'write'
    syscall                 # Llamamos al kernel de Linux

    cmp rax, 0              # Comprobamos si el kernel devolvió un número negativo (error)
    jl .error               # Si rax < 0, saltamos a la etiqueta de error
    
    ret                     # Si todo fue bien, retornamos (rax ya tiene los bytes escritos)

.error:
    neg rax                 # El error devuelto es negativo (ej. -9). Lo pasamos a positivo (9).
    push rax                # Guardamos el código de error en la pila (el stack) temporalmente
    
    call __errno_location   # Obtiene la dirección de memoria de 'errno'. La deja en rax.
    
    pop rdi                 # Recuperamos el código de error de la pila a rdi
    mov [rax], rdi          # Guardamos el código de error en la dirección de 'errno' (*errno = rdi)
    
    mov rax, -1             # La función write en C debe devolver -1 cuando hay un error
    ret

```