/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:51:18 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 14:55:29 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# ifndef DEBUG
#  define DEBUG 0
# endif

# include "../lib/libft_printf/libft_printf.h"
# include "../lib/minilibx/mlx.h"
# include <limits.h>
# include <math.h>

//______DEFINE KEYS_____________________________________________________________

# define K_ARROW_LEFT 65361
# define K_ARROW_UP 65362
# define K_ARROW_RIGHT 65363
# define K_ARROW_DOWN 65364
# define K_ESC 65307

//______DEFINE MOUSE CODES______________________________________________________

# define M_SCROLL_DOWN 4
# define M_SCROLL_UP 5
# define M_SCROLL_RIGHT 6
# define M_SCROLL_LEFT 7

//______DEFINE COLOR____________________________________________________________

# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF

//______DEFINE TEMINAL COLOR____________________________________________________

# define WRITE_COLOR_DEFAULT "\033[0m"
# define WRITE_COLOR_RED "\033[31m"
# define WRITE_COLOR_GREEN "\033[32m"
# define WRITE_COLOR_ORANGE "\033[33m"

//______STRUCTS FOR HANDLING LISTS______________________________________________

typedef struct s_dbg
{
	int					count_stack_depth;
}						t_dbg;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_point_3d
{
	float				x;
	float				y;
	float				z;
}						t_point_3d;

typedef struct s_node
{
	int					x;
	int					y;
	int					z;
	struct s_node		*next;
	struct s_node		*west;
	struct s_node		*north;
	int color;
}						t_node;

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

typedef struct s_model
{
	void				*mlx;
	void				*win;
	struct s_node		*net;
	int					win_width;
	int					win_height;
	int					x_trans;
	int					y_trans;
	double				x_rot_rad;
	double				y_rot_rad;
	double				z_rot_rad;
	double				zoom;
	float				z_factor;
	int					color;
	struct s_dbg		*dbg;
	struct s_point net_dim; //
	int					z_max;
	int					z_min;
	struct s_point_3d	center_point;
	t_img				img;
	enum e_bool			auto_rotate;
}						t_model;

typedef enum e_dbg_flag
{
	error_block = -1,
	no_block = 0,
	start_block = 1,
	end_block = 2
}						t_dbg_flag;

//      ALL FILES AND THEIR NON STATIC FUNCTIONS LISTED ALPHABETICALLY

//______CONTROLLER_KEYS.C_______________________________________________________
int						deal_key(int key, t_model *model);

//______CONTROLLER_MOUSE.C______________________________________________________

int						deal_mouse(int button, t_model *model);

//______DEBUG.C_________________________________________________________________
void					init_debug(t_model *model, int curr_stack_depth);
void					dbg_printf(t_model *model, t_dbg_flag dbg_flg,
							char *str, ...);

//______FDF_UTILS.C_____________________________________________________________

double					degree2radian(int degree);
int						radian2degree2(double radian);

//______IMG.C___________________________________________________________________

void					create_next_img(t_model *model);

//______MAIN.C__________________________________________________________________

int						main(int argc, char **argv);

//______MODEL.C_________________________________________________________________

void					init_net_details(t_model *model);
t_model					*new_model(int argc, char **argv);
void					determine_net_center(t_model *model);
void					node2point(t_model *model, t_node *node,
							t_point *point);
void					free_model(t_model *model);
void					update_max_values(t_model *model, int x, int y, int z);
void					center_model(t_model *model);
void					init_max_values(t_model *model);

//______NODE.C__________________________________________________________________

void					print_node(t_model *model, t_node *node);
char					*node2str(t_model *model, t_node *node);
void					print_net(t_model *model);
t_node					*node_last(t_node *lst);
void					node_add_front(t_node **lst, t_node *new);
void					node_add_back(t_node **lst, t_node *new);
void					free_list(t_node *head);

//______PARSER.C________________________________________________________________

void					load_file(int argc, char **argv, t_model *model);

//______POINT.C_________________________________________________________________

void					print_point(t_model *model, t_point *point);
char					*point2str(t_model *model, t_point *point);

//______VIEW.C__________________________________________________________________

void					ini_win(t_model *model);
void					draw_test_line(t_model *model);
int						auto_rotate(void *void_model);
void					create_new_img(t_model *model);
void					display_next_image(t_model *model);

#endif