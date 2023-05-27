# Makefile for libft.a

# Compiler options
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -fsanitize-address-use-after-scope
RM = rm -f

# Library name and source files
NAME = libft_printf.a
SRC_FOLDER = ./src/
OBJS_FOLDER = ./obj/
SRCS = $(addprefix $(SRC_FOLDER), \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_printf.c \
	print_char.c \
	print_str.c \
	print_dez_to_hexa.c \
	print_ptr.c \
	print_nbr.c \
	print_double.c \
	get_next_line.c)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJS_FOLDER)%.o)

# Targets
.PHONY:	all clean fclean re

$(OBJS_FOLDER)%.o: $(SRC_FOLDER)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) 

$(NAME): $(OBJS)
	@ar -crs $@ $^

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
