# Makefile for FDF

# Variables
NAME = fdf

# Compiler options
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
CLIBS = -L$(LIBFT_FOLDER) -L$(MLX_FOLDER) -lft -lm -lmlx -lX11 -lXext
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
LIBFT_FOLDER = $(LIB_FOLDER)libft/
MLX_FOLDER = $(LIB_FOLDER)minilibx-linux/
MAPS_FOLDER = ./maps/nice_maps/

# ->Files
LIBFT = $(LIBFT_FOLDER)libft.a
MLX = $(MLX_FOLDER)libmlx.a
BANNER = $(LIBFT_FOLDER)make_banner.sh
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
.PHONY: all $(NAME) $(LIBFT) $(MLX) clean fclean re 42 a m p

all: MSG_START $(NAME) MSG_DONE

$(NAME): $(OBJS) $(LIBFT) $(MLX) 
	@$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)

$(OBJS_FOLDER)%.o: $(SRC_FOLDER)%.c
	@mkdir -p $(@D)
	@echo -n "$(BLUE).$(RESET)"
	@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_FOLDER)

$(MLX):
	@$(BANNER) MLX compiling "$(ORANGE)"
	@make --no-print-directory -C > /dev/null 2>&1 $(MLX_FOLDER)
	@$(BANNER) MLX compiled "$(GREEN)"

clean:
	@make --no-print-directory -C $(LIBFT_FOLDER) clean
	@$(RM) $(OBJS)
	@$(BANNER) $(NAME) "removed object files" "$(RED)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_FOLDER) fclean
	@$(RM) $(NAME)
	@$(BANNER) $(NAME) "removed program" "$(RED)"

re: fclean all

42: all
	@./$(NAME) $(MAPS_FOLDER)42.fdf

a: all
	@./$(NAME) $(MAPS_FOLDER)astein.fdf

m: all
	@./$(NAME) $(MAPS_FOLDER)mars.fdf

p: all
	@./$(NAME) $(MAPS_FOLDER)pylone.fdf

MSG_START:
	@$(BANNER) $(NAME) compiling "$(ORANGE)"

MSG_DONE:
	@$(BANNER) $(NAME) compiled "$(GREEN)"