# ft_write

Implementación de `ft_write` en lenguaje Ensamblador (x86-64, sintaxis Intel). Escribe una cantidad de bytes determinada desde un búfer hacia un file descriptor. Actúa como un puente hacia la llamada al sistema original, gestionando correctamente el valor de retorno y asignando el código de error adecuado si falla.

## Código

Para que la función se comporte exactamente igual que la original en C, los argumentos ya vienen listos en los registros correctos. Solo debemos comprobar qué devuelve el kernel tras el `syscall`. Si devuelve un número negativo, debemos llamar a la función `__errno_location` para obtener la dirección de memoria de la variable global `errno` y asignarle el código del fallo.

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
    push rax                # Guardamos el código de error en la pila alineando la pila a 16 bytes.
    
    call __errno_location   # Obtiene la dirección de memoria de 'errno'. La deja en rax.
    
    pop rdi                 # Recuperamos el código de error de la pila a rdi
    mov [rax], rdi          # Guardamos el código de error en la dirección de 'errno' (*errno = rdi)
    
    mov rax, -1             # La función write en C debe devolver -1 cuando hay un error
    ret

```

* **Lógica**: El uso de push rax y pop rdi protege el código del error para que la llamada a __errno_location no lo sobrescriba y alinea la pila (RSP) a 16 bytes

* **Pros:** Gestión de errores en caso de que la llamada a write falle.

---

## Conceptos Clave

### 1. Convención de Registros

Tanto `write(fd, buf, count)` como `syscall write` esperan recibir los argumentos en `rdi`, `rsi` y `rdx` en el mismo orden, por lo que no se necesita cambiarlos de sitio ya que ya están en la posición correcta. Solo se necesita mover el ID de la acción write `1`en `rax` para que el kernel sepa qué operación ejecutar.

### 2. Syscalls

Le pides permiso al Sistema Operativo para que él ejecute la operación. `Syscall` es el puente entre el programa (Modo Usuario) y el sistema operativo (Modo Kernel). Una vez termina le devuelve el control al usuario.

### 3. `errno`

Si `write` falla (`fd` inválido), el kernel de Linux devuelve un número de error negativo en `rax`. El estándar de C dicta que, si hay un error, la función debe devolver `-1` y guardar el código de error positivo en una variable global llamada `errno`. Al llamar a la función externa `__errno_location` desde ensamblador, es obligatorio que la pila sea múltiplo de 16 bytes. Nuestro push rax cuadra la pila perfectamente antes del `syscall`.

---

## Otras Implementaciones

### Con registros no volátiles (Callee-saved)

```assembly
ft_write:

	mov rax, 1
	syscall

	cmp rax, 0
	jl error
	ret

error:
	neg rax
	mov rdi, rax
	call __errno_location
	mov [rax], rdi
	mov rax, -1
	ret

```