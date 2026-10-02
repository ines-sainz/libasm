# ft_strcpy

Implementación de `ft_strcpy` en lenguaje Ensamblador (x86-64, sintaxis Intel). Copia una cadena de caracteres desde un origen (`src`) a un destino (`dest`), incluyendo el byte nulo (`\0`), y devuelve el puntero original al inicio de la cadena de destino.

## Código

La Aritmética de Punteros es lo más eficiente. Usa `[rsi]` y `[rdi]` reduciendo el cálculo de direccionamiento de memoria (Address Generation Interlock) en cada iteración del bucle. Asume la convención de retorno guardando `rdi` en `rax` en la primera línea.

**No se puede mover un dato directamente de memoria a memoria (`mov [rdi], [rsi]`)**. Siempre se necesita un registro intermedio temporal (como `al` o `dl` de 8 bits).

```assembly
.intel_syntax noprefix
.global ft_strcpy

ft_strcpy:
    mov rax, rdi            # Guarda el puntero original de dest para el return

.loop:
    mov dl, byte ptr [rsi]  # 1. Movemos el byte de origen a un registro (un acceso a memoria)
    mov byte ptr [rdi], dl  # 2. Lo copiamos a destino (incluye el \0 del final)
    
    inc rsi                 # 3. Avanzamos puntero origen
    inc rdi                 # 4. Avanzamos puntero destino
    
    cmp dl, 0               # 5. Compronamos si el byte que copiamos era el \0
    jne .loop               # Si no era 0, iteramos de nuevo

    ret                     # Si es 0 salimos, rax tiene el puntero original

```

* **Lógica:** Reduce accesos a memoria a la mitad. En lugar de hacer `cmp [rsi]` (acceso 1) y `mov dl, [rsi]` (acceso 2), leemos a `dl` una sola vez y hacemos todo el trabajo con el registro.
* **Pros:** nos basamos en `while (*dest++ = *src++);`. Primero copiamos el byte al registro temporal, lo guardamos en destino y luego miramos si era cero. Ahorrar una lectura a memoria y el escribir `\0` manualmente.

---

## Otras Implementaciones

### 1. Enfoque por Índice (Variable `i` en `rcx`)

```assembly
ft_strcpy:
	xor rcx, rcx
loop:
	cmp byte ptr [rcx + rsi], 0
	je salir
	mov al, [rcx + rsi]
	mov [rcx + rdi], al
	inc rcx
	jmp loop
salir:
	mov byte ptr [rcx + rdi], 0
	mov rax, rdi
	ret

```

* **Lógica:** Equivalente a `while (src[i] != '\0') { dest[i] = src[i]; i++; }`.
* **Pros:** El puntero original `rdi` no se modifica, por lo que al final simplemente se mueve a `rax` para el retorno.
* **Contras:** Poco eficiente. La CPU calcula dos direcciones de memoria complejas por vuelta (`[rcx + rsi]` y `[rcx + rdi]`). Lee la memoria origen dos veces por iteración (una para `cmp`, otra para `mov al`).

### 2. Enfoque por Aritmética de Punteros

```assembly
ft_strcpy:
	mov rax, rdi

.loop:
	cmp byte ptr [rsi], 0
	je .return

	mov dl, [rsi]
	mov [rdi], dl

	inc rdi
	inc rsi

	jmp .loop

.return:
	mov byte ptr [rdi], 0
	ret

```

* **Lógica:** Equivalente a `while (*src != '\0') { *dest = *src; dest++; src++; }`.
* **Pros:** Guarda `rdi` en `rax` al principio, protegiendo el valor de retorno. Usa accesos de memoria directos (`[rsi]`, `[rdi]`), eliminando el cálculo del offset en el procesador.
* **Contras:** lee la memoria `[rsi]` dos veces por ciclo (una para el `cmp` y otra para mover el dato a `dl`).
