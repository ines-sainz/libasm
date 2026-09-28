# Name of the library file to create
NAME	= libasm.a

# Compiler to use
CC		= gcc -c

# Archive tool to create static libraries
AR		= ar

# Archive flags:
# -r inserts/updates files
# -c creates the archive if it doesn't exist
# -s creates an index (for faster linking)
ARFLAGS	= -rcs

# List of source files for the mandatory part
SRCS =	ft_strlen/ft_strlen.s \
		ft_strcpy/ft_strcpy.s \
		ft_strcmp/ft_strcmp.s \
		ft_write/ft_write.s \
		ft_read/ft_read.s \
		ft_strdup/ft_strdup.s

# List of source files for the bonus part (linked list functions)
SRCSBONUS	=	ft_atoi_base/ft_atoi_base.s \
				ft_list_push_front/ft_list_push_front.s \
				ft_list_size/ft_list_size.s \
				ft_list_sort/ft_list_sort.s \
				ft_list_remove_if/ft_list_remove_if.s

# Corresponding object files for the bonus source files
OBJSBONUS = $(SRCSBONUS:.s=.o)

# Corresponding object files for the mandatory source files
OBJS = $(SRCS:.s=.o)

# Default target: build the library
all: $(NAME)

# Create the library by archiving the compiled object files
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# Target to build the library using bonus files
bonus: $(OBJSBONUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJSBONUS)

# Remove all compiled object files
clean:
	rm -f $(OBJS) $(OBJSBONUS)

# Clean everything, including the library file
fclean: clean
	rm -f $(NAME) test.txt

# Rebuild everything from scratch
re: fclean all

# Test
# -L.   busca librerías en el directorio actual.
# -lasm enlaza libasm.a.
test: re bonus
	@rm -f test.txt .temp_test
	@echo "Ejecutando tests... (los resultados se guardarán en test.txt)"
	
	@echo "===== ft_strlen ====="
	@echo "===== ft_strlen =====" >> test.txt
	@gcc ft_strlen/main_strlen.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_strcpy ====="
	@echo "===== ft_strcpy =====" >> test.txt
	@gcc ft_strcpy/main_strcpy.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_strcmp ====="
	@echo "===== ft_strcmp =====" >> test.txt
	@gcc ft_strcmp/main_strcmp.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_write ====="
	@echo "===== ft_write =====" >> test.txt
	@gcc ft_write/main_write.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_read ====="
	@echo "===== ft_read =====" >> test.txt
	@gcc ft_read/main_read.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_strdup ====="
	@echo "===== ft_strdup =====" >> test.txt
	@gcc ft_strdup/main_strdup.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_atoi_base ====="
	@echo "===== ft_atoi_base =====" >> test.txt
	@gcc ft_atoi_base/main_atoi_base.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_list_push_front ====="
	@echo "===== ft_list_push_front =====" >> test.txt
	@gcc ft_list_push_front/main_list_push_front.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_list_size ====="
	@echo "===== ft_list_size =====" >> test.txt
	@gcc ft_list_size/main_list_size.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_list_sort ====="
	@echo "===== ft_list_sort =====" >> test.txt
	@gcc ft_list_sort/main_list_sort.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@echo "===== ft_list_remove_if ====="
	@echo "===== ft_list_remove_if =====" >> test.txt
	@gcc ft_list_remove_if/main_list_remove_if.c -L. -lasm -o .temp_test && ./.temp_test >> test.txt
	
	@rm -f .temp_test
	@echo "¡Tests completados con éxito!"

# Declare these targets as phony to avoid conflicts with files of the same name
.PHONY: clean fclean re all bonus test