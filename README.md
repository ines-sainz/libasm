# libasm

## Ensamblador (Assembly)
Lenguaje de programación de bajo nivel. Forma legible de escribir instrucciones CPU. Se usa porque tiene un rendimiento máximo, permite acceder directamente a registros, stack y llamadas del sistema.

## Arquitectura
x86 con arquitectura de 64 bits

## Sintaxis
Son notaciones, la CPU ejecuta el mismo binario.
### Intel -> la que vamos a usar
- Más legible, natural y común.
- Recomendada para C, Ensamblador y aprender.
- Se escribe primero el destino y luego la fuente.
- Los registros se escriben directamente.
- Los valores inmediatos se escriben directamente.
- EL tamaño de la memoria se deduce implícitamente.
- Accesos a memoria con `[rbp-8]`.
### AT&T
- GNU por defecto.
- Recomendada para Kernel Linux y leer output de objdump.
- Se escribe la fuente y luego el destino.
- Los registros se escriben con `%` delante.
- Los valores inmediatos se escriben con `$` delante.
- El tamaño de la memoria se escribe después del registro:
	- b: 8 bits
	- w: 16 bits
	- l: 32 bits
	- q: 64 bits
- Accesos a memoria con `-8(%rbp)`.
- Sitaxis por defecto en Linux.

## Ejecutar
El código se lee de arriba a abajo. Las instrucciones se agrupan en etiquetas usadas para marcar un punto específico en el código. Seguido por una coma. Las etiquetas no son funciones, se ejecutan una detrás de otra sin necesidad de llamarse.
### AS
Ensamblador de GNU para GNU/Linux. Usa la sintaxis Intel explícitamente con `.intel_syntax noprefix`.
Comentarios: `#`
### NASM (Netwide Assembler)
Ensamblador y desensamblador para la arquitectura Intel x86. Usa la sintaxis Intel pura sin `.`.
Comentarios: `;`

## Registros
Pueden ser usados en cualquier momento por el sistema para leer o escribir
- rax: valores de retorno, syscalls
- rcx: contador para los bucles
- rbx: 
- rdi: primer argumento
- rsi: segundo argumento
- rdx: tercer argumento
- rsp: puntero de stack
- rbp: base del stack
- r8 - r15: para pasar argumentos
- rip: 

## Instrucciones
Las líneas están compuestas por una instrucción seguida por sus operadores.
### Movimiento de datos:
- mov: mover un valor a un registro
- push: añadir un valor a un stack
- pop: saca un valor de un stack a un destino
### Operaciones aritméticas:
#### Operaciones unarias
- inc: incrementa uno un valor
- dec: decrementa uno un valor
- neg: negación aritmética
- not: operación de bits
#### Operaciones binarias
- leaq: guarda la dirección de un valor a un registro
- add: añadir un valor al valor de un registro
- sub: restar un valor al valor de un registro
- imul: multiplica un valor al valor de un registro
- xor: xor de 2 bits, se guarda en un registro
- or: or de 2 bits, se guarda en un registro
- and: and de 2 bits, se guarda en un registro
#### Operaciones de mover bits
- sal / shl: mueve los bits a la izquierda una cantidad de posiciones
- sar: mueve los bits a la derecha aritméticamente una cantidad de posiciones
- shr: mueve los bits a la derecha lógicamente una cantidad de posiciones
### Comparación e instrucciones de test
- cmp: comparar el valor del registro con un valor (v1 - v2)
- test: compara el valor del registro con un valor (v1 & v2)
### Acceso a códigos de condición
#### Instrucciones condicionales de seteo
- sete / setz: se setea si es igual o cero
- setne / setnz: se setea si no es igual o no es cero
- sets: se setea si es negativo.
- setns: se setea si no es negativo
- setg / setnle: se setea si es mayor que (con signo)
- setge / setnl: se setea si es mayor o igual (con signo)
- setl / setnge: se setea si es menor que (con signo)
- setle / setng: se setea si es menor o igual (con signo)
- seta / setnbe: se setea si es superior (sin signo)
- setae / setnb: se setea si es superior o igual (sin signo)
- setb / setnae: se setea si es inferior (sin signo)
- setbe / setna: se setea si es inferior o igual (sin signo)
#### Instrucciones de salto
- jmp: saltar a una etiqueta o a una localización específica
- je / jz: saltar si es igual o cero
- jne / jnz: saltar si no es igual o no es cero
- js: saltar si es negativo
- jns: saltar si no es negativo
- jg / jnle: saltar si es mayor que (con signo)
- jge / jnl: saltar si es mayor o igual (con signo)
- 

[dirección de memoria] para acceder a una dirección de memoria específica
[dirección + posición] para acceder a una dirección de memoria específica

## Llamar desde C
Podemos exportar las funciones escritas en ensamblador a un programa en C con `global nombre_de_la_función`
- `gcc -c programa.s`
- `gcc -c main.c`
- `gcc sum.o main.o -o ejecutable`
- `./ejecutable`

## Compilar
### Programas .s
(se puede usar `as programa.s` o `gcc -c programa.s`)
- `as programa.s -o programa.o`
- `ld programa.o -o ejecutable`
- `./ejecutable`
### Programas .asm
- `nasm -f elf64 programa.asm`
- `gcc main.c programa.o -o ejecutable`

## Librería
- `gcc -c programa.s`
- `ar -rcs libasm.a programas.o`
- `gcc main.c -L. libasm.a -lmath`