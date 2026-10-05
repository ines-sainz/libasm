# ft_strcmp

Implementación de `ft_strcmp` en lenguaje Ensamblador (x86-64, sintaxis Intel). Compara dos cadenas de caracteres byte a byte y devuelve la diferencia aritmética entre el primer par de caracteres que no coinciden. La comparación se hace con caracteres sin signo (`unsigned char`).

## Código

Al poner a cero un registro de 32 bits (`eax`), automáticamente se ponen a cero los 64 bits completos (`rax`). Cuando hacemos `mov al, [rdi]` después, solo modificamos los 8 bits del final manteniendo el resto a cero y evitando los movzx. Se consigue el mismo efecto con menos instrucciones.

```assembly
.intel_syntax noprefix
.global ft_strcmp

ft_strcmp:
    xor eax, eax            # Limpiamos eax (se limpia rax también)
    xor edx, edx            # Limpiamos edx (se limpia rdx también)

.loop:
    mov al, byte ptr [rdi]  # Cargamos el byte de s1 en al
    mov dl, byte ptr [rsi]  # Cargamos el byte de s2 en dl

    cmp al, dl              # Comparamos los caracteres
    jne .return             # Si son diferentes, saltamos al final

    cmp al, 0               # Si son iguales, comprobamos si hemos llegado al '\0'
    je .return              # Si es nulo, terminamos (ambas cadenas terminaron a la vez)

    inc rdi                 # Avanzamos el puntero s1
    inc rsi                 # Avanzamos el puntero s2
    jmp .loop               # Siguiente iteración

.return:
    sub rax, rdx            # restamos rax y rdx
    ret                     # Devolvemos la resta

```

* **Lógica:** `xor eax, eax` en vez de `movzx` para romper las dependencias de datos previos de la CPU, y optimizar las instrucciones.
* **Pros:** return optimizado con una resta y el uso de xor para los registros manteniendo el unsigned.

---

## Conceptos Clave

### 1. `unsigned char`

El estándar de C dicta que la comparación de caracteres es sin signo `unsigned char`, ya que si no interpreta la tabla ASCII extendida como números negativos. Solucionamos esto manipulando exclusivamente registros de 8 bits (`al`, `dl`) dentro del bucle.

### 2. `movzx` (Move with Zero-Extend)

`movzx rax, al` copia los 8 bits (`al`) en un registro de 64 bits (`rax`), y rellena los 56 bits restantes con ceros.
`mov rax, al` y `movsx` (Move with Sign-Extend) rellenan un carácter extendido con 1 hacia la izquierda para mantener el signo negativo, dando un retorno incorrecto.

### 3. Doble validación (`cmp al, dl` y `cmp al, 0`)

1. **Los caracteres son distintos:** `cmp al, dl` detecta sin son diferentes y sale del bucle para  calcular la diferencia.
2. **Las cadenas han terminado y son iguales:** al saltar `jne`, `al == dl`. El `cmp al, 0` comprueba si llegamos al byte nulo `\0`. Así que sale del bucle si las dos cadenas han terminado `0 - 0 = 0`.
3. **Los caracteres son iguales pero no es el final:** Ninguno de los dos saltos se activa, por lo que se incrementan los punteros y el bucle continúa.

---

## Otras Implementaciones

### Con movzx

```assembly
ft_strcmp:

loop:

	mov al, [rdi]
	mov dl, [rsi]

	cmp al, dl
	jne salir

	cmp al, 0
	je salir

	inc rdi
	inc rsi
	jmp loop

salir:
	movzx rax, al
	movzx rdx, dl
	sub rax, rdx
	ret
```

* **Pros:** mantiene el unsigned a hacer las operaciones y usa aritmética de punteros para optimizarlo.
* **Contras:** Poco eficiente al tener dos `movzx` al final.
