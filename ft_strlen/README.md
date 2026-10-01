# ft_strlen

Implementación de `ft_strlen` en lenguaje Ensamblador (x86-64, sintaxis Intel). Calcula la longitud de una cadena de caracteres, iterando sobre ella hasta encontrar el byte nulo (`\0`).

## Código

La Aritmética de Punteros es lo más eficiente. Usa `[rdi]`reduciendo el cálculo de direccionamiento de memoria (Address Generation Interlock) en cada iteración del bucle.

Aplicando las reglas de registros (el retorno va en `rax`). Evitando mover datos innecesariamente al final del proceso. Movemos el puntero del registro de retorno (`rax`).

```assembly
.intel_syntax noprefix
.global ft_strlen

ft_strlen:
    mov rax, rdi             # Copiamos el puntero inicial a RAX

.loop:
    cmp byte ptr [rax], 0    # Comparamos el valor apuntado por RAX con '\0'
    je .return               # Si es nulo, salimos del bucle
    inc rax                  # Avanzamos el puntero al siguiente byte
    jmp .loop                # Repetimos el bucle

.return:
    sub rax, rdi             # Restamos: puntero final (RAX) - puntero inicial (RDI)
    ret                      # El tamaño ya está en RAX (registro de retorno)

```

* **Lógica:** Mueve el puntero original hasta el final y resta `direccion_final - direccion_inicial`.
* **Pros:** Evita la suma de registros dentro del bucle. `[rax]` es una lectura directa de memoria que es más rápida que `[rcx + rdi]` al no necesitar variables innecesarias (contadores). Al hacer `sub rax, rdi`, el resultado de la resta (la longitud de la cadena), queda en `rax` ahorrando instrucciones extra antes de salir.

---

## Otras Implementaciones

### 1. Enfoque por Índice (Variable `i` en rcx)

```assembly
ft_strlen:
    xor rcx, rcx
.loop:
    cmp byte ptr [rcx + rdi], 0
    je .return
    inc rcx
    jmp .loop
.return:
    mov rax, rcx
    ret
```

* **Lógica:** Idéntica a `while (s[i]) i++;`.
* **Pros:** Intuitivo y directo si se viene de C.
* **Contras:** La CPU tiene que calcular la dirección de memoria en cada iteración sumando la base (`rdi`) más el índice (`rcx`).

### 2. Enfoque con Contador + Puntero

```assembly
ft_strlen:
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
