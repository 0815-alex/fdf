/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:51:18 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 02:41:22 by astein           ###   ########.fr       */
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
# include <stdint.h>
# include <sys/stat.h>
# include <unistd.h>

//______MAP CREATOR))___________________________________________________________
# define PATH_2_CHARS "./maps/letters/"
# define PATH_2_NAMES "./maps/names/"

//______AUTO ZOOM_______________________________________________________________
# define AUTO_ZOOM_INI_LEVEL 1
# define AUTO_ZOOM_FRAMES 15

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

//______DEFINE BUTTONS__________________________________________________________
# define B_MIN_WIN 15
# define B_CLS_WIN 17

//______DEFINE COLOR____________________________________________________________

// #define COLOR_WHITE ((uint8_t)255)
// #define COLOR_RED ((uint8_t)255)
// #define COLOR_GREEN ((uint8_t)0)
// #define COLOR_BLACK ((uint8_t)0)
// #define COLOR_BLUE ((uint8_t)255)
// # define COLOR_BLACK 0x000000u
// # define COLOR_RED 0xFF0000u
// # define COLOR_GREEN 0x00FF00u
// # define COLOR_BLUE 0x0000FFu

//______DEFINE TEMINAL COLOR____________________________________________________

# define WRITE_COLOR_DEFAULT "\033[0m"
# define WRITE_COLOR_RED "\033[31m"
# define WRITE_COLOR_GREEN "\033[32m"
# define WRITE_COLOR_ORANGE "\033[33m"

//______STRUCTS ________________________________________________________________

typedef struct s_dbg
{
	int					count_stack_depth;
}						t_dbg;

typedef struct s_color
{
	uint8_t				red;
	uint8_t				green;
	uint8_t				blue;
}						t_color;

typedef struct s_point_2d
{
	int					x;
	int					y;
}						t_point_2d;

typedef struct s_point_3d_colored
{
	int					x;
	int					y;
	int					z;
	t_color				color;
}						t_point_3d_colored;

typedef struct s_point_3d
{
	int					x;
	int					y;
	int					z;
}						t_point_3d;

typedef struct s_point_dbl_3d
{
	double				x;
	double				y;
	double				z;
}						t_point_dbl_3d;

typedef struct s_node
{
	t_point_3d			*pnt;
	t_color				color;
	struct s_node		*next;
	struct s_node		*west;
	struct s_node		*north;
}						t_node;

/**
 * @brief dof degrees of fredoom
 * 
 */
typedef struct s_dof_plus
{
	t_point_2d			trans;
	t_point_dbl_3d		rot_rad;
	double				zoom;
	double				z_factor;
	enum e_bool			auto_rotate;
	int					auto_zoom;
}						t_dof_plus;

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

/*
True Color bla bla
*/
typedef struct s_color_map
{
	t_color				min;
	t_color				zero;
	t_color				max;
	struct s_color_map	*previous;
	struct s_color_map	*next;
}						t_color_map;

typedef struct s_model
{
	void				*mlx;
	void				*win;
	int					win_width;
	int					win_height;
	t_bool				close_pending;
	t_node				*net;
	t_color_map			*color_map;
	t_dbg				dbg;
	t_dof_plus			dof;
	t_point_2d			net_dim;
	int					z_max;
	int					z_min;
	t_point_3d			center_point;
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
//==============================================================================

//______COLOR_MAP.C_____________________________________________________________
void					ini_color_maps(t_model *model);
t_color_map				*add_color_map(t_model *model, t_color min,
							t_color zero, t_color max);
void					free_color_maps(t_model *model);

//______COLOR.C_________________________________________________________________

void					ini_colors(t_model *model);
t_color	*calculate_step_color(t_color start_color,
								t_color end_color,
								int n_steps);
int						color2int(t_color color);

//______CONTROLLER_KEYS.C_______________________________________________________
int						deal_key(int key, t_model *model);

//______CONTROLLER_MOUSE.C______________________________________________________
int						deal_mouse(int code, t_model *model);

//______DATA.C__________________________________________________________________
void					ini_net_details(t_model *model);
void					print_net(t_model *model);
void					ini_max_values(t_model *model);
void					update_max_values(t_model *model, int x, int y, int z);
void					determine_net_center(t_model *model);

//______DEBUG.C_________________________________________________________________
void					ini_debug(t_model *model, int curr_stack_depth);
void					dbg_printf(t_model *model, t_dbg_flag dbg_flg,
							char *str, ...);
//______DOF_PLUS.C______________________________________________________________
void					ini_dof_plus(t_model *model);
void					cpy_dof(t_dof_plus *src, t_dof_plus *dest);

//______IMG.C___________________________________________________________________
void					ini_img(t_model *model);
void					create_next_img(t_model *model);

//______LIST.C__________________________________________________________________
void					node_add_front(t_node **lst, t_node *new);
void					node_add_back(t_node **lst, t_node *new);
void					free_list(t_node *head);

//______MAIN.C__________________________________________________________________
int						main(int argc, char **argv);

//______MAP_CREATOR.C__________________________________________________________________
char					*create_map(t_model *model, char *str);

//______MODEL_MOVE.C____________________________________________________________
void					trans_mod(t_model *model, t_bool ovr,
							t_point_2d *trans);
void					rot_mod(t_model *model, t_bool ovr, t_point_3d *deg);
void					scale_mod(t_model *model, t_bool ovr, double zoom,
							double z_factor);
int						auto_movements(t_model *model);
void					auto_zoom(t_model *model, t_bool zoomIn);
t_bool					static_auto_zoom(t_model *model, t_bool zoom_in);

//______MODEL.C_________________________________________________________________
t_model					*new_model(int argc, char **argv);
void					shedule_close(t_model *model);
int						close_model(t_model *model);

//______NODE.C__________________________________________________________________
t_node					*new_node(t_point_3d *point);
void					print_node(t_model *model, t_node *node);
char					*node2str(t_model *model, t_node *node);
void					node2point(t_model *model, t_node *node,
							t_point_3d_colored *point);

//______PARSER.C________________________________________________________________
void					load_file(int argc, char **argv, t_model *model);

//______POINT.C_________________________________________________________________
void					*new_point(t_pnt_dim dim, int x, int y, int z);
void					print_point(t_model *model, t_point_2d *point);
char					*point2str(t_model *model, t_point_2d *point);

//______UTILS.C_________________________________________________________________
double					degree2radian(int degree);
int						radian2degree2(double radian);
void					*free_whatever(t_model *model, char *str, ...);

//______VIEW.C__________________________________________________________________
void					ini_win(t_model *model);
void					center_model(t_model *model);
void					update_image(t_model *model);

#endif
