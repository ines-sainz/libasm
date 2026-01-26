# Name of the library file to create
NAME	= libasm.a

# Compiler to use
CC		= nasm

# Compiler flags: 
# -Wall enables all warnings
# -Werror turns warnings into errors
# -Wextra enables extra warnings
# CFLAGS	= -Wall -Werror -Wextra

# Archive tool to create static libraries
AR		= ar

# Archive flags:
# -r inserts/updates files
# -c creates the archive if it doesn't exist
# -s creates an index (for faster linking)
ARFLAGS	= -rcs

# List of source files for the mandatory part
SRCS =	ft_strlen.c \
		ft_strcpy.c \
		ft_strcmp.c \
		ft_write.c \
		ft_read.c \
		ft_strdup.c

# List of source files for the bonus part (linked list functions)
SRCSBONUS	=	ft_atoi_base.c \
				ft_list_push_front.c \
				ft_list_size.c \
				ft_list_sort.c \
				ft_list_remove_if.c

# Corresponding object files for the bonus source files
OBJSBONUS = $(SRCSBONUS:.c=.o)

# Corresponding object files for the mandatory source files
OBJS = $(SRCS:.c=.o)

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
	@rm -f $(OBJS) $(OBJSBONUS)

# Clean everything, including the library file
fclean: clean
	@rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all

# Declare these targets as phony to avoid conflicts with files of the same name
.PHONY: clean fclean re all bonus