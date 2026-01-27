# libasm

## Ensamblador (Assembly)
Lenguaje de programación de bajo nivel. Forma legible de escribir instrucciones CPU. Se usa porque tiene un rendimiento máximo, permite acceder directamente a registros, stack y llamadas del sistema.

## Arquitectura
x86 con arquitectura de 64 bits

## Sintaxis
Son notaciones, la CPU ejecuta el mismo binario.
### Intel -> la que vamos a usar
- Más legible y natural.
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
### AS
Ensamblador de GNU para GNU/Linux. Usa la sintaxis Intel explícitamente con `.intel_syntax noprefix`.
Comentarios: `#`

### NASM (Netwide Assembler)
Ensamblador y desensamblador para la arquitectura Intel x86. Usa la sintaxis Intel pura sin `.`.
Comentarios: `;`

## Registros
- rax: valores de retorno, syscalls
- rdi: primer argumento
- rsi: segundo argumento
- rdx: tercer argumento
- rsp: puntero de stack
- rbp: base del stack

## Llamar desde C
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