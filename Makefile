# Makefile for ftf

# Variables
NAME = fdf

# Prints DEBUG Messages
DEBUG = 1

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
LIBFT_PRINTF_FOLDER = $(LIB_FOLDER)libft_printf/
MLX_FOLDER = $(LIB_FOLDER)minilibx/
MAPS_FOLDER = ./maps/

# ->Files
LIBFT_PRINTF = $(LIBFT_PRINTF_FOLDER)libft_printf.a
MINILIBX = $(MLX_FOLDER)libmlx.a
SRCS = $(addprefix $(SRC_FOLDER), \
	color.c \
	color_map.c \
	controller_keys.c \
	controller_mouse.c \
	data.c \
	dof_plus.c \
	img.c \
	line.c \
	main.c \
	map_creator_utils.c \
	map_creator.c \
	model.c \
	model_move.c \
	node.c \
	node_lst.c \
	parser.c \
	point.c \
	utils.c \
	view.c \
	view_txt.c \
	zoom.c)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJS_FOLDER)%.o)

# TARGETS
.PHONY: all $(NAME) $(LIBFT_PRINTF) $(MINILIBX) clean fclean re 42 a m p god norm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PRINTF) $(MINILIBX)
	@$(CC) $(OBJS) $(CFLAGS) -D DEBUG=$(DEBUG) $(CLIBS) $(CINCLUDES) -lft_printf -lmlx -lX11 -lXext -lm -o $(NAME)
	@echo "$(GREEN)\n$(NAME): created\n$(RESET)"

$(OBJS_FOLDER)%.o: $(SRC_FOLDER)%.c
	@mkdir -p $(@D)
	@echo -n "."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_PRINTF):
	@echo "$(ORANGE)\ncompiling: $(LIBFT_PRINTF)\n$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_PRINTF_FOLDER) DEBUG=$(DEBUG)

$(MINILIBX):
	@echo "$(ORANGE)\ncompiling: $(MINILIBX)\n$(RESET)"
	@make --no-print-directory -C > /dev/null 2>&1 $(MLX_FOLDER)


clean:
	@$(RM) $(OBJS)
	@echo "$(RED)$(NAME): cleaned object files$(RESET)"


fclean: clean
	@make --no-print-directory -C $(LIBFT_PRINTF_FOLDER) fclean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME): cleaned program$(RESET)"

re: fclean all

42: all
	@./$(NAME) ./maps/42.fdf

a: all
	@./$(NAME) ./maps/astein2.0.fdf

m: all
	@./$(NAME) ./maps/mars.fdf

p: all
	@./$(NAME) ./maps/pylone.fdf

god:
	git status
	git add .
	git status
	git commit -m " -> Makefile Commit <- "
	git status

norm:
	@echo "$(ORANGE)\nCHECK SOURCE FILES$(RESET)"
	@echo "$(ORANGE)-------------------------------\
	---------------------------------$(RESET)"
	@norminette $(SRC_FOLDER) && norminette $(LIBFT_PRINTF_FOLDER)src
	@echo "$(ORANGE)\nCHECK HEADER FILE$(RESET)"
	@echo "$(ORANGE)-------------------------------\
	---------------------------------$(RESET)"
	@norminette $(INCLUDE_FOLDER) && norminette $(LIBFT_PRINTF_FOLDER)libft_printf.h
	@echo "$(GREEN)\n------------------------------\
	----------------------------------$(RESET)"
	@echo "$(GREEN)DONE - ALL GOOD :)\n$(RESET)"