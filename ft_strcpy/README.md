# ft_strcpy

Implementación de la función `ft_strcpy` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. La función copia una cadena de caracteres desde un origen (`src`) a un destino (`dest`), incluyendo el byte nulo terminador (`\0`), y devuelve el puntero original al inicio de la cadena de destino.

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia conceptual entre la lógica de C y los registros/instrucciones en Ensamblador, recordando la regla de oro: **no se puede mover un dato directamente de memoria a memoria (`mov [rdi], [rsi]` es inválido)**, por lo que siempre se necesita un registro intermedio temporal (como `al` o `dl` de 8 bits).

| Concepto en C | Equivalente en Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `char *dest` | `rdi` | Primer argumento (puntero destino). |
| `const char *src` | `rsi` | Segundo argumento (puntero origen). |
| `int i = 0;` | `xor rcx, rcx` | Inicialización de contador (solo usado en el enfoque por índice). |
| `src[i] != '\0'` | `cmp byte ptr [rcx + rsi], 0` | Comprueba si el byte actual de origen es nulo. |
| `dest[i] = src[i];` | `mov al, [rsi]` \| `mov [rdi], al` | Uso de registro intermedio (`al` o `dl`) para copiar el byte. |
| `i++` (o `dest++`, `src++`) | `inc rcx` (o `inc rdi`, `inc rsi`) | Incremento del índice o de los punteros para avanzar al siguiente carácter. |
| `dest[i] = '\0';` | `mov byte ptr [rdi], 0` | Inserción manual del terminador nulo al final del bucle. |
| `return (original_dest);` | `mov rax, rdi` | El puntero original de `dest` debe devolverse en `rax`. |

---

## Comparación de Implementaciones

A continuación se analizan los dos enfoques que has proporcionado.

### 1. Enfoque por Índice (Variable `i` en `rcx`)

```assembly
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
* **Pros:** El puntero original `rdi` nunca se modifica, por lo que al final simplemente se mueve a `rax` para el retorno.
* **Contras:** Poco eficiente. La CPU calcula dos direcciones de memoria complejas por vuelta (`[rcx + rsi]` y `[rcx + rdi]`). Además, lee la memoria origen dos veces por iteración (una para `cmp`, otra para `mov al`).

### 2. Enfoque por Aritmética de Punteros

```assembly
	mov rax, rdi
loop:
	cmp byte ptr [rsi], 0
	je salir
	mov dl, [rsi]
	mov [rdi], dl
	inc rdi
	inc rsi
	jmp loop
salir:
	mov byte ptr [rdi], 0
	ret

```

* **Lógica:** Equivalente a `while (*src != '\0') { *dest = *src; dest++; src++; }`.
* **Pros:** Guarda inteligentemente `rdi` en `rax` al principio, protegiendo el valor de retorno. Usa accesos de memoria directos (`[rsi]`, `[rdi]`), lo que elimina el cálculo del offset en el procesador.
* **Contras:** Sigue leyendo la memoria `[rsi]` dos veces por ciclo (una para el `cmp` y otra para mover el dato a `dl`).

---

## El Código Proporcionado Más Eficiente

El **Enfoque 2 (Aritmética de Punteros)** es claramente superior. Al prescindir del registro `rcx` y acceder directamente a las direcciones apuntadas por `rdi` y `rsi`, reduce el trabajo de cálculo de direcciones (Address Generation Interlock) de la CPU. Además, asume de forma brillante la convención de retorno guardando `rdi` en `rax` en la primera línea.

## Propuesta de Código Optimizado

Aunque tu Enfoque 2 es muy bueno, tiene un "cuello de botella": lee la misma dirección de memoria dos veces por iteración y nos obliga a poner el `\0` a mano al final.

Podemos optimizarlo basándonos en el clásico de C `while (*dest++ = *src++);`. Si **primero copiamos el byte al registro temporal, lo guardamos en destino y luego miramos si era cero**, nos ahorramos una lectura a memoria y la escritura final del `\0` (porque el `\0` también se copia dentro del bucle).

```assembly
.intel_syntax noprefix
.global ft_strcpy

ft_strcpy:
    mov rax, rdi            # Salvaguardar el puntero original de dest para el return

.loop_start:
    mov dl, byte ptr [rsi]  # 1. Leemos el byte de origen a un registro (solo un acceso a memoria)
    mov byte ptr [rdi], dl  # 2. Lo copiamos inmediatamente a destino (incluyendo el \0 cuando toque)
    
    inc rsi                 # 3. Avanzamos puntero origen
    inc rdi                 # 4. Avanzamos puntero destino
    
    cmp dl, 0               # 5. Comparamos si el byte que acabamos de copiar era el final
    jne .loop_start         # Si no era 0, iteramos de nuevo

    ret                     # Si era 0, rax ya tiene el puntero original, fin de la función.

```

**Por qué es más eficiente:**

1. **Reduce accesos a memoria a la mitad:** En lugar de hacer `cmp [rsi]` (acceso 1) y `mov dl, [rsi]` (acceso 2), leemos a `dl` una sola vez y hacemos todo el trabajo con el registro.
2. **Copia el terminador gratis:** Al copiar a destino *antes* de saltar, el `\0` se transfiere naturalmente sin necesidad de añadir código en una etiqueta `salir`.
3. **Menos saltos y etiquetas:** El código fluye directamente hacia el `ret`, evitando instrucciones extra fuera del bucle.