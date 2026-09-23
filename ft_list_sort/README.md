# ft_list_sort

Implementación de la función `ft_list_sort` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. Esta función ordena una lista enlazada comparando sus elementos mediante una función de comparación pasada como puntero `(*cmp)()`. En lugar de desarmar y rearmar los nodos de la lista (lo cual es complejo), el enfoque utilizado es intercambiar (swap) únicamente el contenido `data` de los nodos cuando están desordenados, usando el algoritmo de ordenamiento de burbuja (Bubble Sort).

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia conceptual entre C y Ensamblador. Se incluye tu enfoque original y la corrección necesaria para los registros (explicada más abajo).

| Concepto en C | Registro (Tu código) | Registro Seguro (Corregido) | Explicación |
| --- | --- | --- | --- |
| `t_list **begin_list` | `rdi` | `rdi` | Puntero a la cabeza de la lista. |
| `int (*cmp)()` | `rsi` | `r13` | Puntero a la función de comparación. |
| `t_list *i` (outer loop) | `r8` | `rbx` | Nodo actual (bucle externo). |
| `t_list *j` (inner loop) | `r9` | `r12` | Nodo a comparar (bucle interno). |
| `i->data` | `[r8]` | `[rbx]` | Primeros 8 bytes del struct del nodo actual. |
| `j->next` | `[r9 + 8]` | `[r12 + 8]` | Últimos 8 bytes del struct (puntero al siguiente nodo). |
| `cmp(i->data, j->data)` | `call [rsp]` | `call r13` | Llama a la función de comparación. |
| `swap(data1, data2)` | `swap_datas` | bloque `swap` | Intercambia valores si `cmp` devuelve `> 0`. |

---

## Conceptos Clave y Aprendizajes (Y resolución de bugs)

Tu código tiene **ideas avanzadas geniales** (como la forma creativa en la que llamas a la función apuntada desde la pila), pero contiene un par de *bugs* críticos de lógica de punteros y de convención de llamadas que provocarían un *Segmentation Fault*. Aprender de esto te dará un nivel experto:

### 1. Punteros a Funciones (`call` dinámico)

Has descubierto cómo usar punteros a funciones en ensamblador. Cuando en C haces `cmp(a, b)`, la CPU simplemente hace un `call` a una dirección de memoria variable.
Tu idea de hacer `push rsi` y luego `call [rsp]` es muy astuta para proteger el puntero a función. Sin embargo, la forma más limpia en ensamblador es mover el puntero a un registro seguro y simplemente hacer `call r13`.

### 2. El Desastre de los Registros Volátiles (¡Cuidado con `r8` y `r9`!)

Este es el error más grave (e invisible) del código. Has usado `r8` para tu nodo actual `i` y `r9` para tu nodo `j`.
Según la convención de llamadas System V, **los registros `r8`, `r9`, `r10` y `r11` son Caller-Saved (volátiles)**. Cuando haces el `call` a la función `cmp()`, esa función externa **tiene derecho a destruir y reescribir `r8` y `r9**`. Al volver de `cmp()`, tus nodos de la lista habrán desaparecido o apuntarán a basura, provocando un crasheo al intentar hacer `[r8 + 8]`.
*Solución:* Debes usar registros Callee-Saved (`rbx`, `r12`, `r13`, `r14`) y guardarlos con `push`/`pop`.

### 3. Bugs en la Aritmética de Punteros

Hay varias líneas en tu código donde la manipulación de punteros se confunde con la reasignación de valores en memoria:

* `mov r11, [r9 + r8]`: No se pueden sumar dos punteros para navegar por un struct. Para avanzar, simplemente es `[r9 + 8]`.
* `mov [r8], r11` (en tu `exit_loop_next_node`): Esto **sobreescribe el `data**` del nodo con el puntero al siguiente nodo, corrompiendo la lista. Lo que querías era avanzar el registro: `mov r8, [r8 + 8]`.
* El bloque `swap_datas` no vuelve a saltar al bucle tras ejecutarse, simplemente cae hacia el `return`.

---

## Propuesta de Código Optimizado y Seguro

Aquí tienes el código reescrito. Mantiene tu fantástica idea de iterar con dos bucles e intercambiar solo la información (`data`), pero respeta estrictamente la convención de llamadas (usando `rbx`, `r12`, `r13`) y corrige el avance de punteros.

```assembly
.intel_syntax noprefix
.global ft_list_sort

ft_list_sort:
    # 1. PRÓLOGO: Guardamos los registros callee-saved que vamos a usar
    # Así los protegemos y evitamos que se destruyan durante toda la función
    push rbx                
    push r12
    push r13

    # 2. COMPROBACIONES INICIALES
    test rdi, rdi           # if (!begin_list)
    je .end
    mov rbx, [rdi]          # rbx = *begin_list (Este será nuestro nodo 'i')
    test rbx, rbx           # if (!*begin_list)
    je .end
    test rsi, rsi           # if (!cmp)
    je .end

    mov r13, rsi            # Guardamos el puntero a la función cmp en r13 (Seguro)

    # 3. BUCLE EXTERNO (node 'i' en rbx)
.outer_loop:
    test rbx, rbx           # if (i == NULL) salir del bucle exterior
    je .end
    mov r12, [rbx + 8]      # r12 = i->next (Este será nuestro nodo 'j')

    # 4. BUCLE INTERNO (node 'j' en r12)
.inner_loop:
    test r12, r12           # if (j == NULL) fin del bucle interior, avanzar 'i'
    je .advance_outer

    # Preparamos los argumentos para llamar a cmp()
    mov rdi, [rbx]          # arg1: i->data
    mov rsi, [r12]          # arg2: j->data
    call r13                # eax = cmp(i->data, j->data)

    # Evaluamos si hay que hacer SWAP (si eax > 0)
    test eax, eax           # equivalente a cmp eax, 0
    jle .advance_inner      # Si es <= 0, no intercambiamos, pasamos al siguiente

    # 5. LÓGICA DE SWAP (Intercambiamos los punteros data)
    mov r8, [rbx]           # r8 = tmp = i->data
    mov r9, [r12]           # r9 = j->data
    mov [rbx], r9           # i->data = r9
    mov [r12], r8           # j->data = tmp

.advance_inner:
    mov r12, [r12 + 8]      # j = j->next (Avanzamos el puntero, no machacamos memoria)
    jmp .inner_loop         # Repetimos bucle interno

.advance_outer:
    mov rbx, [rbx + 8]      # i = i->next (Avanzamos el nodo exterior)
    jmp .outer_loop         # Repetimos bucle externo

.end:
    # 6. EPÍLOGO: Restauramos los registros originales antes de salir
    pop r13
    pop r12
    pop rbx
    ret

```