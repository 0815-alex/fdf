# Makefile for ftf

# Variables
NAME = fdf

# Prints DEBUG Messages
DEBUG = 0
# Compiler options
CC = cc
CFLAGS = -D DEBUG=$(DEBUG) -g -Wall -Werror -Wextra -fsanitize=address -fsanitize-address-use-after-scope
CLIBS = -L$(LIB_FOLDER)libft_printf -L$(LIB_FOLDER)minilibx -lm
CINCLUDES  = -I$(INCLUDE_FOLDER) -I$(MLX_FOLDER)
RM = rm -f

# ->Folders
SRC_FOLDER = ./src/
OBJS_FOLDER = ./obj/
LIB_FOLDER = ./lib/
INCLUDE_FOLDER = ./include/
MLX_FOLDER = $(LIB_FOLDER)minilibx
MAPS_FOLDER = ./maps/

# ->Files
LIBFT_PRINTF = $(LIB_FOLDER)/libft_printf/libft_printf.a
SRCS = $(addprefix $(SRC_FOLDER), \
	color.c \
	color_map.c \
	controller_keys.c \
	controller_mouse.c \
	data.c \
	debug.c \
	dof_plus.c \
	img.c \
	list.c \
	main.c \
	map_creator.c \
	model.c \
	model_move.c \
	node.c \
	parser.c \
	point.c \
	utils.c \
	view.c)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJS_FOLDER)%.o)

# TARGETS
.PHONY: all clean fclean re r rr god

$(OBJS_FOLDER)%.o: $(SRC_FOLDER)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PRINTF)
	$(CC) $(OBJS) $(CFLAGS) -D DEBUG=$(DEBUG) $(CLIBS) $(CINCLUDES) -lft_printf -lmlx -lX11 -lXext -lm -o $(NAME)

$(LIBFT_PRINTF):
	@echo "\ncompiling libft_printf.a...\n"
	@make -C $(LIB_FOLDER)libft_printf
	@echo "\nlibft_printf.a compiled!\n"

clean:
	$(RM) $(OBJS)
	#make -C $(LIB_FOLDER)libft_printf clean

fclean: clean
	@$(RM) $(NAME)
	#make -C $(LIB_FOLDER)libft_printf fclean

re: fclean all

r: all
	./$(NAME) ./maps/easy.fdf
rr: re
	./$(NAME) ./maps/easy.fdf

42: all
	./$(NAME) ./maps/42.fdf
t: all
	./$(NAME) ./maps/til.fdf

a: re
	./$(NAME) ./maps/astein2.0.fdf

m: re
	./$(NAME) ./maps/mars.fdf

tm: re
	./$(NAME) abABc

p: all
	./$(NAME) ./maps/pylone.fdf

god:
	git status
	git add .
	git status
	git commit -m " -> Makefile Commit <- "
	git status
