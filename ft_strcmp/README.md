# ft_strcmp

Implementación de `ft_strcmp` en lenguaje Ensamblador (x86-64, sintaxis Intel). Compara dos cadenas de caracteres byte a byte y devuelve la diferencia aritmética entre el primer par de caracteres que no coinciden. La comparación se hace con caracteres sin signo (`unsigned char`).

## Traducción de C a Ensamblador

| `(unsigned char)s1[i]` | `movzx rax, al` | Expande el registro de 8 bits (`al`) a 64 bits (`rax`) rellenando con ceros. Fundamental para comparar sin signo. |

---

## Conceptos Clave

### 1. La importancia de `unsigned char`

El estándar de C dicta que la comparación de caracteres es sin signo `unsigned char`, ya que si no interpreta la tabla ASCII extendida como números negativos. Solucionamos esto manipulando exclusivamente registros de 8 bits (`al`, `dl`) dentro del bucle.

### 2. Instrucción `movzx` (Move with Zero-Extend)

Al hacer `movzx rax, al` copias los 8 bits (`al`) en un registro de 64 bits (`rax`), y rellena los 56 bits restantes con ceros.
`mov rax, al` y `movsx` (Move with Sign-Extend) rellenan un carácter extendido con 1 hacia la izquierda para mantener el signo negativo, dando un retorno incorrecto.

### 3. Doble validación (`cmp al, dl` y `cmp al, 0`)

Resuelve tres casos a la vez:

1. **Los caracteres son distintos:** `cmp al, dl` detecta sin son diferentes y sale del bucle para  calcular la diferencia.
2. **Las cadenas han terminado y son iguales:** al saltar `jne`, `al == dl`. El `cmp al, 0` comprueba si llegamos al byte nulo `\0`. Así que sale del bucle si las dos cadenas han terminado `0 - 0 = 0`.
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