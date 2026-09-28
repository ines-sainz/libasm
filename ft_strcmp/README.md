# ft_strcmp

Implementación de la función `ft_strcmp` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. La función compara dos cadenas de caracteres byte a byte y devuelve la diferencia aritmética entre el primer par de caracteres que no coinciden. La comparación se hace con caracteres sin signo (`unsigned char`), tal como dicta el estándar de C.

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia conceptual entre la lógica de C y tu código en Ensamblador:

| Concepto en C | Equivalente en Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `char *s1` | `rdi` | Primer argumento (puntero a la primera cadena). |
| `char *s2` | `rsi` | Segundo argumento (puntero a la segunda cadena). |
| `s1[i]` (o `*s1`) | `al` (vía `mov al, [rdi]`) | El byte actual de la primera cadena en un registro de 8 bits. |
| `s2[i]` (o `*s2`) | `dl` (vía `mov dl, [rsi]`) | El byte actual de la segunda cadena en un registro de 8 bits. |
| `s1[i] != s2[i]` | `cmp al, dl` \| `jne salir` | Compara los registros. Si son diferentes (Jump if Not Equal), sale del bucle. |
| `s1[i] == '\0'` | `cmp al, 0` \| `je salir` | Comprueba si se alcanzó el fin de la cadena. Al haber pasado el `jne` anterior, sabemos que `dl` también es `0`. |
| `i++` | `inc rdi` / `inc rsi` | Incrementa los punteros para avanzar al siguiente carácter. |
| `(unsigned char)s1[i]` | `movzx rax, al` | Expande el registro de 8 bits (`al`) a 64 bits (`rax`) rellenando con ceros. Fundamental para comparar sin signo. |
| `return s1[i] - s2[i];` | `sub rax, rdx` \| `ret` | Resta el valor de la segunda cadena a la primera y devuelve el resultado en `rax`. |

---

## Conceptos Clave y Aprendizajes

Este código es excelente para entender cómo interactúan los tamaños de los registros y el manejo de signos a bajo nivel. Aquí están las partes más importantes:

### 1. La importancia de `unsigned char`

El estándar de C dicta que `strcmp` debe comparar los caracteres como si fueran `unsigned char` (sin signo). Si un carácter de la tabla ASCII extendida (por ejemplo, `é`, `ñ` o caracteres especiales donde el primer bit es `1`) se interpreta con signo, la CPU lo considerará un número negativo, lo que arruinaría el resultado matemático de la resta final. Tu código soluciona esto manipulando exclusivamente registros de 8 bits (`al`, `dl`) dentro del bucle.

### 2. La instrucción `movzx` (Move with Zero-Extend)

Esta es la verdadera estrella de tu código de salida. Cuando haces `movzx rax, al`, le estás diciendo a la CPU: *"Copia estos 8 bits (`al`) en un registro de 64 bits (`rax`), y rellena los 56 bits restantes exclusivamente con ceros"*.
Si hicieras un simple `mov rax, al` (ilegal por tener distintos tamaños) o usaras `movsx` (Move with Sign-Extend), un carácter extendido se rellenaría con unos (`1`) hacia la izquierda para mantener el signo negativo, dando un retorno completamente incorrecto.

### 3. La doble validación en el bucle (`cmp al, dl` y `cmp al, 0`)

El bucle resuelve tres casos posibles de manera muy eficiente:

1. **Los caracteres son distintos:** El primer `cmp al, dl` detecta la diferencia y el `jne` nos saca del bucle inmediatamente para calcular la resta.
2. **Las cadenas han terminado y son iguales:** Si no saltó el `jne`, significa que `al == dl`. Luego, el `cmp al, 0` comprueba si llegamos al byte nulo `\0`. Si es así, ambas cadenas terminaron al unísono y son idénticas, saliendo al bloque final (donde `0 - 0 = 0`).
3. **Los caracteres son iguales pero no es el final:** Ninguno de los dos saltos se activa, por lo que se incrementan los punteros y el bucle continúa.

---

## Análisis del Código Proporcionado

Solo has proporcionado una versión, pero es una **excelente implementación**.

Has resuelto brillantemente el mayor problema de `ft_strcmp` en ensamblador: la convención de C exige que la resta final se haga evaluando los caracteres como `unsigned char`. Si usaras registros extendidos con signo (por ejemplo `movsx`) o restaras registros de 8 bits en negativo (lo que altera el bit de signo de forma imprevista en el retorno de 32/64 bits), fallarías en las pruebas estrictas.

Al utilizar **`movzx` (Move with Zero-Extend)**, garantizas que un carácter extendido del ASCII como `é` (que en binario tiene el primer bit a 1) no se interprete erróneamente como un número negativo al pasarlo a `rax`.

* **Pros:** Es seguro, lógico y completamente respetuoso con la conversión a `unsigned char`. El uso de aritmética de punteros en lugar de índices (evitando `rcx`) reduce la carga de la CPU.
* **Contras:** Se puede hacer un "truco" de ensamblador para evitar los dos `movzx` al final y rascar un par de ciclos de reloj.

---

## Propuesta de Código Optimizado

Podemos optimizar tu código utilizando una propiedad fundamental de la arquitectura x86-64: **si pones a cero un registro de 32 bits (como `eax`), automáticamente se ponen a cero los 64 bits completos (`rax`)**.

En ensamblador se suele utilizar un truco clásico de optimización para evitar los `movzx` del final. Si limpiamos `rax` y `rdx` al *principio* de la función con un `xor`, cuando hagamos `mov al, [rdi]` dentro del bucle, solo estaremos modificando los 8 bits más bajos; el resto del registro seguirá siendo cero. Todo lo que escribamos en `al` y `dl` quedará aislado en un mar de ceros, logrando el mismo efecto que `movzx` pero ahorrando instrucciones en la ruta de salida. Esto nos permite eliminar las instrucciones `movzx` al final y hacer directamente la resta.

```assembly
.intel_syntax noprefix
.global ft_strcmp

ft_strcmp:
    xor eax, eax            # Limpiamos eax (y rax por extensión) a 0
    xor edx, edx            # Limpiamos edx (y rdx por extensión) a 0

.loop_start:
    mov al, byte ptr [rdi]  # Cargamos el byte de s1 en al
    mov dl, byte ptr [rsi]  # Cargamos el byte de s2 en dl

    cmp al, dl              # Comparamos los caracteres
    jne .salir              # Si son diferentes, saltamos al final

    cmp al, 0               # Si son iguales, comprobamos si hemos llegado al '\0'
    je .salir               # Si es nulo, terminamos (ambas cadenas terminaron a la vez)

    inc rdi                 # Avanzamos el puntero s1
    inc rsi                 # Avanzamos el puntero s2
    jmp .loop_start         # Siguiente iteración

.salir:
    sub rax, rdx            # rax y rdx ya tienen los valores correctos (rellenados con 0)
    ret                     # Devolvemos la resta

```

**Por qué es más eficiente:**

1. **Limpieza anticipada (Dependency Breaking):** `xor eax, eax` rompe las dependencias de datos previas de la CPU y es una instrucción superoptimizada que ocupa menos espacio que `movzx`.
2. **Camino de salida más rápido:** El bloque final (`.salir`) ahora solo tiene una resta y el retorno, agilizando el final de la ejecución cuando se encuentra una diferencia.
3. **Mantiene la seguridad `unsigned`:** Al escribir solo en `al` y `dl` habiendo limpiado previamente el registro entero, emulamos exactamente el comportamiento de `movzx` sin coste adicional al salir.