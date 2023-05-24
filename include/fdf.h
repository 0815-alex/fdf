/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:51:18 by astein            #+#    #+#             */
/*   Updated: 2023/05/24 12:25:07 by astein           ###   ########.fr       */
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

typedef struct s_point_2d
{
	int					x;
	int					y;
}						t_point_2d;

typedef struct s_point_3d
{
	int					x;
	int					y;
	int					z;
}						t_point_3d;

typedef struct s_node
{
	// int					x;
	// int					y;
	// int					z;
	t_point_3d			*pnt;
	int					color;
	struct s_node		*next;
	struct s_node		*west;
	struct s_node		*north;
}						t_node;

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

/**
 * @brief dof degrees of fredoom
 * 
 */
typedef struct s_dof_plus
{
	int					x_trans;
	int					y_trans;
	double				x_rot_rad;
	double				y_rot_rad;
	double				z_rot_rad;
	double				zoom;
	double				z_factor;
	enum e_bool			auto_rotate;
}						t_dof_plus;

typedef struct s_model
{
	void				*mlx;
	void				*win;
	int					win_width;
	int					win_height;
	//DATA
	struct s_node		*net;
	//DEBUG
	struct s_dbg		*dbg;
	t_dof_plus			dof;
	//WHEN I IMPLEMENT THE COLOR SHIFT THIS WILL BE OBSOLETE
	int					color;
	t_point_2d net_dim; //The x and y max of the file
	int					z_max;
	int					z_min;
	struct s_point_3d	center_point;

	t_img				img;
}						t_model;

typedef enum e_dbg_flag
{
	err_block = -1,
	no_block = 0,
	start_block = 1,
	end_block = 2
}						t_dbg_flag;

typedef enum e_pnt_dim
{
	pnt_dim_error = -1,
	pnt_dim_2 = 2,
	pnt_dim_3 = 3
}						t_pnt_dim;

//      ALL FILES AND THEIR NON STATIC FUNCTIONS LISTED ALPHABETICALLY

//______CONTROLLER_KEYS.C_______________________________________________________
int						deal_key(int key, t_model *model);

//______CONTROLLER_MOUSE.C______________________________________________________

int						deal_mouse(int button, t_model *model);

//______DEBUG.C_________________________________________________________________
void					ini_debug(t_model *model, int curr_stack_depth);
void					dbg_printf(t_model *model, t_dbg_flag dbg_flg,
							char *str, ...);

//______UTILS.C_________________________________________________________________

double					degree2radian(int degree);
int						radian2degree2(double radian);
void	*free_whatever(t_model *model, char *str, ...);

//______IMG.C___________________________________________________________________
void					ini_img(t_model *model);
void					create_next_img(t_model *model);

//______MAIN.C__________________________________________________________________

int						main(int argc, char **argv);

//______MODEL.C_________________________________________________________________

void					ini_net_details(t_model *model);
t_model					*new_model(int argc, char **argv);
void					determine_net_center(t_model *model);
void					node2point(t_model *model, t_node *node,
							t_point_2d *point);
void					free_model(t_model *model);
void					update_max_values(t_model *model, int x, int y, int z);
void					center_model(t_model *model);
void					ini_max_values(t_model *model);

//______NODE.C__________________________________________________________________

t_node					*new_node(t_point_3d *point, int color);
void					print_node(t_model *model, t_node *node);
char					*node2str(t_model *model, t_node *node);
void					print_net(t_model *model);
void					node_add_front(t_node **lst, t_node *new);
void					node_add_back(t_node **lst, t_node *new);
void					free_list(t_node *head);

//______PARSER.C________________________________________________________________

void					load_file(int argc, char **argv, t_model *model);

//______POINT.C_________________________________________________________________

void					*new_point(t_pnt_dim dim, int x, int y, int z);
void					print_point(t_model *model, t_point_2d *point);
char					*point2str(t_model *model, t_point_2d *point);

//______VIEW.C__________________________________________________________________

void					ini_win(t_model *model);
void					ini_dof_plus(t_model *model);
void					create_new_img(t_model *model);
void					update_image(t_model *model);

#endif

//______MODEL_MOVE.C
void					translate_model(t_model *model, t_bool overwrite,
							t_point_2d *trans);
void					rotate_model(t_model *model, t_bool overwrite,
							t_point_3d *rot_degrees);
void					scale_model(t_model *model, t_bool overwrite,
							double zoom, double z_factor);
int						auto_rotate(t_model *model);
void					zoom_to_start(t_model *model);
//______DATA.C
//______LIST.C
//______
//______
