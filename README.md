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
Pueden ser usados en cualquier momento por el sistema para leer o escribir. Son una memoria pequeña muy rápida de la CPU por la que pasan todos los cálculos, comparaciones, llamadas a funciones o al sistema...
- rax: acumulador, valores de retorno, syscalls (64 bits)
- rcx: contador para los bucles
- rbx: para preservar registros, no se destruye al llamar funciones se debe restaurar antes de usar
- rdi: primer argumento
- rsi: segundo argumento
- rdx: tercer argumento
- r8 - r15: para pasar los argumentos siguientes
- rsp: puntero de stack
- rbp: base del stack
- rip: 

```
rax is a 64-bit register.
But parts of it have smaller names:

Name	Size	What it is
rax	64-bit	full register
eax	32-bit	lower 32 bits of rax
ax	16-bit	lower 16 bits
al	8-bit	lowest byte
ah	8-bit	second lowest byte
rax = [B7][B6][B5][B4][B3][B2][B1][B0]
                                   ↑
                                  al

Same idea for rdx:

Name	Size
rdx	64-bit
edx	32-bit
dx	16-bit
dl	low 8 bits

👉 al is literally the lowest 8 bits of rax.
👉 dl is the lowest 8 bits of rdx.
```

## Instrucciones
Las líneas están compuestas por una instrucción seguida por sus operadores. Intrucción destino, fuente.
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
- jl / jnge: saltar si es menor que (con signo)
- jle / jng: saltar si es menor o igual (con signo)
- ja / jnbe: saltar si es superior (sin signo)
- jae / jnb: saltar si es superior o igual (sin signo)
- jb / jnae: saltar si es inferior (sin signo)
- jbe / jna: saltar si es inferior o igual (sin signo)
#### Instrucciones condicionales de movimiento
- cmove / cmovz: mover si es igual o es cero
- cmovene / cmovnz: mover si no es igual o no es cero
- cmovs: mover si es negativo
- cmovns: mover si no es negativo
- cmovg / cmovnle: mover si es mayor (con signo)
- cmovge / cmovnl: mover si es mayor o igual (con signo)
- cmovl / cmovnge: mover si es menor (con signo)
- cmovle / cmovng: mover si es menor o igual (con signo)
- cmova / cmovnbe: mover si es superior (sin signo)
- cmovae / cmovnb: mover si es superior o igual (sin signo)
- cmovb / cmovnae: mover si es inferior (sin signo)
- cmovbe / cmovna: mover si es inferior o igual (sin signo)
### Instrucciones de llamada a un procedimiento
- call: guarda la dirección siguiente y salta a la función
- call *operador: guarda el retorno y salta a la dirección indicada
- ret: saca la dirección de retorno de el stack y salta a esa dirección
- leave: restaura la pila al estado de antes de la llamada

[dirección de memoria] para acceder a una dirección de memoria específica

[dirección + posición] para acceder a una dirección de memoria específica

mov [rax], [rdi]: No se permiten hacer movimientos de memoria a memoria

## Llamadas a kernel
Una system call (syscall) es la forma en la que un programa en modo usuario le pide al kernel que haga algo privilegiado porque tu programa normal no puede tocar directamente el sistema operativo ni el hardware. tu programa → syscall → kernel → hardware / recursos
- leer/escribir archivos
- abrir sockets
- reservar memoria
- crear procesos
- hablar con hardware

### En Linux moderno (x86-64), el flujo típico es:

1️⃣ Pones el número de syscall en RAX

Cada syscall tiene un número.
- write = 1
- read = 0
- exit = 60

2️⃣ Pones los argumentos en registros

Convención estándar Linux x86-64:
- RDI: arg1
- RSI: arg2
- RDX: arg3
- R10: arg4
- R8: arg5
- R9: arg6

3️⃣ Ejecutas la instrucción syscall

Esto cambia de modo usuario → modo kernel.

4️⃣ El resultado vuelve en RAX

- valor positivo = OK
- negativo = error

### 🔢 Número de syscalls

🐧 Linux x86-64: ~450–550 syscalls según kernel
- 0 → read
- 1 → write
- 2 → open
- 3 → close
- 9 → mmap
- 39 → getpid
- 57 → fork
- 59 → execve
- 60 → exit

## Flags
- ZF: resultado = 0
- SF: negativo
- CF: carry sin signo
- OF: overflow con signo

## Llamar desde C
Podemos exportar las funciones escritas en ensamblador a un programa en C con `global nombre_de_la_función`
- `gcc -g main.c programa.s - o ejecutable`
- `./ejecutable`

## Compilar
C y ASM generan el mismo binario ELF
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

## FT_STRLEN
```
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
```

### xor rcx, rcx
- no necesita memoria
- no depende de valores anteriores
- rompe dependencias internas usando el dependency breaking
- la CPU lo reconoce como poner a 0
- tiene solo un ciclo
- óptimo y optimizable
- 3 bytes
- Modifica flags
- ZF = 1
- SF = 0
### mov rcx, 0
- carga un inmediato
- ocupa más espacio
- menos óptimo
- 7 bytes
- no modifica flags

## FT_STRCPY
```
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

```
mov byte ptr al, [rsi]

no usas byte ptr con registros, solo con memoria.

mov al, [rsi]


.section .note.GNU-stack,"",@progbits
|->
“This object file does not need an executable stack.”

## FT_STRCMP
```
int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
```

## FT_WRITE

ssize_t write(int fd, const void *buf, size_t count);

🖥️ Linux x86-64 — write to terminal using write syscall

```
section .data
msg db "Hello, world!", 10
len equ $ - msg

section .text
global _start

_start:
    mov rax, 1      ; syscall number for write
    mov rdi, 1      ; file descriptor (1 = stdout)
    mov rsi, msg    ; pointer to text
    mov rdx, len    ; length of text
    syscall

    mov rax, 60     ; syscall number for exit
    xor rdi, rdi
    syscall
```

🧠 What each register means (this is the key part)

When you call write(fd, buffer, length) in assembly:

Register	Meaning
rax	syscall number (1 = write)
rdi	where to write (1 = terminal)
rsi	address of text
rdx	number of bytes

Then:

syscall: tells the OS → “do the thing”.

📦 Conceptual translation to C

This assembly is basically:

write(1, "Hello, world!\n", 14);

So if you understand function calls — syscalls are just OS functions with registers instead of arguments.

## FT_READ

ssize_t read(int fd, void buf[.count], size_t count);

```
.intel_syntax noprefix
.global ft_read

ft_read:

	mov rax, 0
	syscall

	cmp rax, 0 ; si hay un error tienes q hacer cosas
	jl error
	
	ret

error:
    neg rax
; rax tiene el errno, lo tienes q poner a positivo porque kernel lo devuelve negativo pero lo necesitas positivo
    mov rdi, rax
; guardas el valor de errno en rdi
    call __errno_location
; guarda el puntero a errno en rax
    mov [rax], rdi
; le das a errno el valor de rax al acceder a su dirección *errno = valor
    mov rax, -1
; devolver -1 por read
    ret
```

## FT_STRDUP
```
char	*ft_strdup(const char *s1)
{
	int		len;
	char	*new_string;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	new_string = malloc(len + 1);
	if (!new_string)
		return (NULL);
	new_string[len] = 0;
	while (i < len)
	{
		new_string[i] = s1[i];
		i++;
	}
	return (new_string);
}
```