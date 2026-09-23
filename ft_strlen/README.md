# ft_strlen

Implementación de la función `ft_strlen` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. La función calcula la longitud de una cadena de caracteres, iterando sobre ella hasta encontrar el byte nulo (`\0`) que indica su final.

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia conceptual entre la lógica de C y los registros/instrucciones en Ensamblador para esta función:

| Concepto en C | Equivalente en Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `const char *s` | `rdi` | Primer argumento pasado a la función (puntero a la cadena). |
| `size_t i;` | `rcx` o aritmética de punteros | Registro utilizado como contador o índice. |
| `i = 0;` | `xor rcx, rcx` (o `mov rcx, 0`) | Inicialización del contador. `xor` es más óptimo (ocupa 3 bytes, 1 ciclo). |
| `s[i] == '\0'` | `cmp byte ptr [rdi + rcx], 0` | Compara un byte (`char`) en la dirección de memoria con 0 (`\0`). |
| `while (...)` | `loop: ... jmp loop` | Etiqueta de inicio de bucle y salto incondicional al final del cuerpo. |
| `if (!cond)` | `je salir` | Salto condicional si la comparación anterior es igual a cero (Jump if Equal). |
| `i++` | `inc rcx` (o `inc rdi`) | Incremento unitario del contador o del puntero. |
| `return (i);` | `mov rax, ...` / `ret` | El valor de retorno debe almacenarse obligatoriamente en `rax` antes de hacer `ret`. |

---

## Comparación de Implementaciones

### 1. Enfoque por Índice (Variable `i`)

```assembly
    mov rcx, 0
loop:
    cmp byte ptr [rcx + rdi], 0
    je end
    inc rcx
    jmp loop
end:
    mov rax, rcx
    ret

```

* **Lógica:** Idéntica a `while (s[i]) i++;`.
* **Pros:** Intuitivo y directo si se viene de C.
* **Contras:** La CPU tiene que calcular la dirección de memoria en cada iteración sumando la base (`rdi`) más el índice (`rcx`).

### 2. Enfoque por Aritmética de Punteros

```assembly
    mov rax, rdi
loop:
    cmp byte ptr [rdi], 0
    je salir
    inc rdi
    jmp loop
salir:
    sub rdi, rax
    mov rax, rdi
    ret

```

* **Lógica:** Mueve el puntero original hasta el final y resta `direccion_final - direccion_inicial`.
* **Pros:** Evita la suma de registros dentro del bucle (`[rdi]` es más rápido de evaluar que `[rcx + rdi]`).
* **Contras:** Guarda la base en `rax` y modifica `rdi`, requiriendo un paso extra al final (`mov rax, rdi`) para colocar el resultado en el registro de retorno.

### 3. Enfoque Redundante (Contador + Puntero)

```assembly
    mov rcx, 0
loop:
    cmp byte ptr [rdi], 0
    je salir
    inc rdi
    inc rcx
    jmp loop
salir:
    mov rax, rcx
    ret

```

* **Lógica:** Incrementa tanto la posición en memoria como una variable contador independiente.
* **Pros:** Lectura secuencial simple.
* **Contras:** Es el menos eficiente. Ejecuta dos instrucciones `inc` por cada vuelta del bucle, malgastando ciclos de CPU.

---

## El Código Proporcionado Más Eficiente

El **Enfoque 2 (Aritmética de Punteros)** es el más eficiente en su núcleo. Usa solo `[rdi]` en lugar de `[rdi + rcx]`, lo que reduce el cálculo de direccionamiento de memoria (Address Generation Interlock) en cada iteración del bucle, aunque el final sea un poco redundante.

## Propuesta de Código Optimizado

Podemos mejorar el Enfoque 2 para que sea aún más limpio, aplicando las reglas de registros (el retorno va en `rax`) y evitando mover datos innecesariamente al final del proceso.

En lugar de mover el puntero de argumento (`rdi`), movemos directamente el registro de retorno (`rax`).

```assembly
.intel_syntax noprefix
.global ft_strlen

ft_strlen:
    mov rax, rdi             # Copiamos el puntero inicial a RAX

.loop_start:
    cmp byte ptr [rax], 0    # Comparamos el valor apuntado por RAX con '\0'
    je .loop_end             # Si es nulo, salimos del bucle
    inc rax                  # Avanzamos el puntero al siguiente byte
    jmp .loop_start          # Repetimos el bucle

.loop_end:
    sub rax, rdi             # Restamos: puntero final (RAX) - puntero inicial (RDI)
    ret                      # El tamaño ya está en RAX (registro de retorno)

```

**Por qué es mejor:**

1. **Sin variables innecesarias:** No necesita usar `rcx` para nada.
2. **Direccionamiento directo:** `[rax]` es una lectura directa de memoria, sin cálculos adicionales.
3. **Retorno automático:** Al hacer `sub rax, rdi`, el resultado de la resta (la longitud exacta) queda directamente alojado en `rax`, listo para el `ret`, ahorrando instrucciones extra antes de salir de la función.