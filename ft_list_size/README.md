# ft_list_size

Implementación de la función `ft_list_size` en lenguaje Ensamblador (x86-64, sintaxis Intel) para la librería `libasm`. Esta función recorre una lista enlazada desde el primer nodo hasta el final, contando cuántos elementos contiene, y devuelve ese contador.

## Traducción de C a Ensamblador

La siguiente tabla muestra la correspondencia conceptual entre la iteración de la lista en C y los accesos a memoria en Ensamblador:

| Concepto en C | Equivalente en Ensamblador (x86-64) | Explicación |
| --- | --- | --- |
| `t_list *lst` | `rdi` | Primer argumento (puntero al nodo actual). |
| `int i = 0;` | `xor rax, rax` | Inicialización del contador a 0 directamente en el registro de retorno. |
| `lst == NULL` | `cmp rdi, 0` | Comprueba si el puntero actual apunta a nulo (0). |
| `if (!lst) break;` | `je return` | Si el puntero es nulo, sale del bucle iterativo. |
| `lst = lst->next;` | `mov rdi, [rdi + 8]` | Desplaza el puntero 8 bytes (tamaño de `data`) para leer el campo `next` y sobreescribe `rdi` con la dirección del siguiente nodo. |
| `i++;` | `inc rax` | Incrementa el contador de nodos iterados. |
| `return i;` | `ret` | El valor ya está en `rax`, simplemente retorna. |

---

## Conceptos Clave y Aprendizajes

Este código es brillante por su minimalismo. Has captado perfectamente la esencia de cómo se manejan las listas enlazadas y los bucles en ensamblador sin malgastar recursos.

### 1. Reutilización destructiva de Registros (`rdi`)

En funciones anteriores donde necesitabas conservar el puntero original, utilizabas registros adicionales o guardabas en la pila. Aquí, como la función solo tiene que devolver el número (el tamaño) y a C no le importa dónde acabe el puntero local `lst`, **sobreescribes directamente `rdi**` en cada iteración (`mov rdi, [rdi + 8]`). Esto es altamente eficiente porque evita el uso de registros intermediarios.

### 2. Uso directo del registro de retorno (`rax`)

En lugar de usar `rcx` o `r8` para contar y al final hacer un `mov rax, rcx`, has sido inteligente inicializando `rax` a cero al principio. Todo el conteo ocurre en la variable que finalmente se va a devolver, ahorrando instrucciones de transferencia al salir.

### 3. El desplazamiento en estructuras (`[rdi + 8]`)

Esta única instrucción es el corazón del recorrido de listas en ASM. Sabiendo que un puntero de 64 bits ocupa 8 bytes, saltarse los primeros 8 bytes (`data`) y leer los siguientes 8 bytes (`next`) te da la dirección del próximo nodo. Reasignar eso a `rdi` cierra el ciclo de forma elegante.

---

## Propuesta de Código Optimizado

Tu código es casi perfecto arquitectónicamente. La única mejora que se le puede hacer es una convención clásica de optimización de ensamblador: cambiar el `cmp rdi, 0` por un `test rdi, rdi`.

```assembly
.intel_syntax noprefix
.global ft_list_size

ft_list_size:
    xor rax, rax            # Inicializa el contador (y registro de retorno) a 0

.loop:
    test rdi, rdi           # Comprueba si lst es NULL (mucho más eficiente que cmp rdi, 0)
    je .return              # Si es NULL (0), sale del bucle

    mov rdi, [rdi + 8]      # lst = lst->next (avanza al siguiente nodo)
    inc rax                 # Incrementa el contador (tamaño)
    
    jmp .loop               # Repite el proceso

.return:
    ret                     # Retorna con el tamaño en rax

```

**Por qué es mejor usar `test` en lugar de `cmp`:**
Mientras que `cmp rdi, 0` realiza una resta aritmética implícita (`rdi - 0`), `test rdi, rdi` realiza una operación lógica AND a nivel de bits (`rdi & rdi`). Ambas configuran el *Zero Flag* (ZF) si el registro es nulo, pero `test` codifica en menos bytes de instrucción, no necesita alojar el número literal `0` en la memoria del programa, y los procesadores modernos lo ejecutan ligeramente más rápido.