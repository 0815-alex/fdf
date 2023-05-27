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

# Color codes
GREEN = \033[0;32m
RED = \033[0;31m
ORANGE = \033[0;33m
RESET = \033[0m

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
.PHONY: all clean fclean re 42 a m p god

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PRINTF)
	@$(CC) $(OBJS) $(CFLAGS) -D DEBUG=$(DEBUG) $(CLIBS) $(CINCLUDES) -lft_printf -lmlx -lX11 -lXext -lm -o $(NAME)
	@echo "$(GREEN)\n$(NAME): created\n$(RESET)"

$(OBJS_FOLDER)%.o: $(SRC_FOLDER)%.c
	@mkdir -p $(@D)
	@echo -n "."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_PRINTF):
	@echo "$(ORANGE)\ncompiling $(LIBFT_PRINTF)\n$(RESET)"
	@make --no-print-directory -C $(LIB_FOLDER)libft_printf

clean:
	#@make --no-print-directory -C $(LIB_FOLDER)libft_printf clean
	@$(RM) $(OBJS)
	@echo "$(RED)$(NAME): cleaned object files$(RESET)"


fclean: clean
	#@make --no-print-directory -C $(LIB_FOLDER)libft_printf fclean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME): cleaned program$(RESET)"

re: fclean all

42: re
	./$(NAME) ./maps/42.fdf

a: re
	./$(NAME) ./maps/astein2.0.fdf

m: re
	./$(NAME) ./maps/mars.fdf

p: re
	./$(NAME) ./maps/pylone.fdf

god:
	git status
	git add .
	git status
	git commit -m " -> Makefile Commit <- "
	git status
