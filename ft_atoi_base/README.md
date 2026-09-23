# ft_atoi_base

Implementación de la función `ft_atoi_base` en lenguaje Ensamblador (x86-64, sintaxis Intel). Esta es una de las funciones más complejas de `libasm` porque requiere validaciones anidadas, operaciones aritméticas (multiplicación) y múltiples bucles. Convierte una cadena de texto en un número entero basándose en una base numérica proporcionada como argumento (ej. binario `"01"`, hexadecimal `"0123456789ABCDEF"`).

## Traducción de C a Ensamblador

La siguiente tabla mapea la lógica mental de un programa en C a los registros que has utilizado en tu ensamblador:

| Concepto en C | Registro / Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `char *str` | `rdi` | Primer argumento (cadena a convertir). |
| `char *base` | `rsi` | Segundo argumento (cadena con los caracteres de la base). |
| `int i`, `int j` | `rcx`, `rdx` | Índices para recorrer las cadenas. |
| `int eq` | `r8` | Bandera (flag) para comprobar si un carácter existe en la base. |
| `int result` | `r9` | Acumulador donde se va calculando el número final. |
| `int base_len` | `r10` | Longitud de la base (multiplicador). |
| `result * base_len` | `imul r9, r10` | Instrucción de multiplicación con signo. Guarda en `r9` el resultado de `r9 * r10`. |
| `result += pos` | `add r9, rax` | Suma el valor de la posición del carácter al acumulador. |

---

## Conceptos Clave y Aprendizajes

Tu código es un salto gigantesco en complejidad. Aquí hay conceptos muy valiosos que has implementado, junto con algunas lecciones arquitectónicas:

### 1. Instrucción `imul` (Multiplicación)

Por primera vez usas `imul r9, r10`. Esta instrucción multiplica el registro destino (`r9`) por el origen (`r10`) y guarda el resultado en el destino. Es el corazón lógico de la conversión de bases: `numero = (numero * longitud_base) + valor_del_caracter`.

### 2. Preservación de Registros Volátiles (`push` y `pop`)

Has hecho un uso excelente de la pila al hacer `push rdi` antes de llamar a `ft_strlen(rsi)` y `pop rdi` después. Sabes que `ft_strlen` destruirá tu registro `rdi` (porque es caller-saved), así que lo proteges. ¡Esta es una práctica obligatoria y lo has hecho perfecto!

### 3. El Peligro de las Subrutinas Internas (El coste de `call`)

Tu código tiene subrutinas como `check_eq` y `get_pos` a las que accedes usando `call` desde dentro de un bucle.
**Cuidado:** Las instrucciones `call` y `ret` son costosas en ciclos de reloj porque interactúan con la pila (apilan y desapilan la dirección de retorno). Hacer un `call` dentro de un bucle anidado (como tu `loop2_j`) mata el rendimiento. En ensamblador, para comprobaciones de 2 líneas, **es mucho mejor usar saltos condicionales (`jmp`, `je`) integrados** (lo que en C se llamaría "inline") en lugar de funciones internas.

### 4. Lógica Incompleta de `atoi` (Aviso sobre el Subject)

El subject de 42 dice: *"Except for the base rule, the function should behave exactly like ft_atoi"*.
Tu código actual asume que `str` empieza directamente con los números. El `atoi` original ignora los espacios en blanco iniciales (espacio, `\t`, `\n`, etc.) y acepta múltiples signos `+` y `-` (o un solo signo, dependiendo de tu versión de libc). Debes procesar esto antes de empezar a multiplicar.

---

## Propuesta de Código Optimizado

Tu código funciona lógicamente, pero se puede refactorizar para que sea inmensamente más rápido, compacto y libre de `call` internos.

En esta optimización:

1. Validamos la base en una sola pasada eficiente.
2. Evitamos hacer `call` internos (todo fluye con saltos).
3. Añadimos la lógica estándar de `atoi` (saltar espacios, procesar signo).

```assembly
.intel_syntax noprefix
.global ft_atoi_base

ft_atoi_base:
    # --- 1. VALIDACIÓN DE LA BASE ---
    test rsi, rsi           # Si base == NULL
    je .error
    
    xor rcx, rcx            # rcx = i = 0 (longitud de la base)
.check_base_loop:
    mov al, byte ptr [rsi + rcx]
    test al, al
    je .check_base_end      # Si llegamos al '\0'

    # Comprobar caracteres inválidos (+, -, espacio)
    cmp al, '+'
    je .error
    cmp al, '-'
    je .error
    cmp al, ' '
    je .error
    # (Nota: aquí se podrían añadir \t, \n, \v, \f, \r para ser 100% estricto)

    # Comprobar duplicados (bucle interno)
    mov rdx, rcx            
    inc rdx                 # rdx = j = i + 1
.check_dup_loop:
    mov r8b, byte ptr [rsi + rdx]
    test r8b, r8b
    je .next_char           # Fin del bucle interno
    cmp al, r8b             # ¿base[i] == base[j]?
    je .error               # Si hay duplicado, error
    inc rdx
    jmp .check_dup_loop

.next_char:
    inc rcx
    jmp .check_base_loop

.check_base_end:
    cmp rcx, 2              # rcx ahora tiene el strlen(base)
    jl .error               # La base debe tener al menos 2 caracteres
    mov r10, rcx            # r10 = base_len

    # --- 2. SALTAR ESPACIOS (Lógica ft_atoi) ---
    xor rcx, rcx            # rcx = índice para str (rdi)
.skip_spaces:
    mov al, byte ptr [rdi + rcx]
    cmp al, ' '
    je .inc_space
    cmp al, 9               # '\t'
    jl .check_sign
    cmp al, 13              # '\r'
    jg .check_sign
.inc_space:
    inc rcx
    jmp .skip_spaces

    # --- 3. PROCESAR SIGNO ---
.check_sign:
    mov r11, 1              # r11 = signo = 1 (positivo por defecto)
    cmp al, '-'
    je .is_negative
    cmp al, '+'
    je .is_positive
    jmp .convert_loop       # Si no hay signo, empezamos a convertir

.is_negative:
    mov r11, -1             # signo = -1
.is_positive:
    inc rcx                 # Avanzamos el puntero tras el signo

    # --- 4. CONVERSIÓN ---
    xor r9, r9              # r9 = resultado = 0
.convert_loop:
    mov al, byte ptr [rdi + rcx]
    test al, al
    je .end_atoi            # Si str[i] == '\0', terminamos

    # Buscar el carácter en la base
    xor rdx, rdx            # rdx = posición en la base
.find_pos:
    mov r8b, byte ptr [rsi + rdx]
    test r8b, r8b
    je .end_atoi            # Si no se encuentra en la base, el atoi estándar se detiene aquí
    cmp al, r8b
    je .found_pos           # Lo hemos encontrado
    inc rdx
    jmp .find_pos

.found_pos:
    # result = (result * base_len) + pos
    imul r9, r10            # r9 = r9 * r10 (base_len)
    add r9, rdx             # r9 = r9 + rdx (pos)
    
    inc rcx                 # Avanzamos en str
    jmp .convert_loop

.end_atoi:
    # Aplicar signo: result * signo
    imul r9, r11
    mov rax, r9             # Retornamos el resultado en rax
    ret

.error:
    xor rax, rax            # Retornamos 0 en caso de error de base
    ret

```