/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:51:18 by astein            #+#    #+#             */
/*   Updated: 2023/05/29 14:04:45 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft_printf/libft_printf.h"
# include "../lib/minilibx/mlx.h"
# include <limits.h>
# include <stdint.h>
# include <sys/stat.h>
# include <unistd.h>

//______PATHS___________________________________________________________________
# define P_CHARS "./maps/letters/"
# define P_NAMES "./maps/names/"
# define P_RESOURCES "./resources/"
# define P_HELP "./resources/help_on_screen.txt"

//______AUTO ZOOM_______________________________________________________________
# define AUTO_ZOOM_INI_LEVEL 1
# define AUTO_ZOOM_FRAMES 15

//______AUTO ROATET & COLOR_SHIFT_______________________________________________
# define AUTO_MOVE_FRAMES 10

//______SCREEN RESOLUTION_______________________________________________________
# define SZ 15

//______DEFINE KEYS_____________________________________________________________
# define K_ARROW_LEFT 65361
# define K_ARROW_UP 65362
# define K_ARROW_RIGHT 65363
# define K_ARROW_DOWN 65364
# define K_F1 65470
# define K_F2 65471
# define K_F3 65472
# define K_F4 65473
# define K_F5 65474
# define K_F6 65475
# define K_F7 65476
# define K_F8 65477
# define K_F9 65478
# define K_F10 65479
# define K_F11 65480
# define K_F12 65481
# define K_TAB 65289
# define K_ESC 65307
# define K_SEMICOLON 246

//______DEFINE MOUSE CODES LINUX________________________________________________
# define M_LEFT 1
# define M_MIDDLE 2
# define M_RIGHT 3
# define M_SCROLL_DOWN 4
# define M_SCROLL_UP 5
# define M_SCROLL_RIGHT 6
# define M_SCROLL_LEFT 7

//______DEFINE BUTTONS__________________________________________________________
# define B_MIN_WIN 15
# define B_CLS_WIN 17

//______DEFINE COLOR____________________________________________________________
# define CLR_WHITE 0xFFFFFFFF
# define CLR_BLACK 0xFF000000
# define CLR_R 0xFFFF0000
# define CLR_G 0xFF00FF00
# define CLR_B 0xFF0000FF

//______STRUCTS ________________________________________________________________
typedef struct s_clr
{
	double			red;
	double			green;
	double			blue;
}						t_clr;

typedef struct s_pnt_2d
{
	int					x;
	int					y;
}						t_pnt_2d;

typedef struct s_pnt_2d_clr
{
	int					x;
	int					y;
	t_clr				clr;
}						t_pnt_2d_clr;

typedef struct s_pnt_3d
{
	int					x;
	int					y;
	int					z;
}						t_pnt_3d;

typedef struct s_pnt_3d_dbl
{
	double				x;
	double				y;
	double				z;
}						t_pnt_3d_dbl;

typedef enum e_pnt_dim
{
	pnt_dim_error = -1,
	pnt_dim_2 = 2,
	pnt_dim_3 = 3
}						t_pnt_dim;

typedef struct s_node
{
	t_pnt_3d			*pnt;
	t_clr				clr;
	struct s_node		*next;
	struct s_node		*west;
	struct s_node		*north;
}						t_node;

/* dof = degrees of fredoom */
typedef struct s_dof_plus
{
	t_pnt_2d			trans;
	t_pnt_3d_dbl		rot_rad;
	double				zoom;
	double				z_factor;
	t_bool				auto_rot;
	t_bool				auto_color_change;
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

typedef struct s_clr_map
{
	t_clr				min;
	t_clr				zero;
	t_clr				max;
	struct s_clr_map	*previous;
	struct s_clr_map	*next;
}						t_clr_map;

typedef struct s_model
{
	void				*mlx;
	void				*win;
	int					win_width;
	int					win_height;
	t_bool				close_pending;
	t_node				*net;
	t_pnt_2d			net_dim;
	t_pnt_3d			center_pnt;
	int					z_min;
	int					z_max;
	t_dof_plus			dof;
	t_clr_map			*clr_map;
	t_img				img;
	t_list				**help;
	t_bool				show_help;
	t_bool				show_stats;
}						t_model;

//      ALL FILES AND THEIR NON STATIC FUNCTIONS LISTED ALPHABETICALLY
//==============================================================================

//______COLOR_MAP.C_____________________________________________________________
void					ini_clr_maps(t_model *model);
void					next_clr_map(t_model *mod);
void					free_clr_maps(t_model *model);

//______COLOR.C_________________________________________________________________
t_clr					*step_clr(t_clr start_clr, t_clr end_clr,
							double n_steps);
void					cpy_color(t_clr *src, t_clr *dest);
t_clr					*sum_clr(t_clr *a, t_clr *b, int b_factor);
int						color2int(t_model *mod, t_clr *clr);

//______CONTROLLER_KEYS.C_______________________________________________________
int						deal_key(int key, t_model *model);

//______CONTROLLER_MOUSE.C______________________________________________________
int						deal_mouse(int btn, int x, int y, t_model *mod);

//______DATA.C__________________________________________________________________
void					ini_net_details(t_model *model);
void					update_max_values(t_model *model, int x, int y, int z);
void					determine_net_center(t_model *model);

//______DOF_PLUS.C______________________________________________________________
void					ini_dof_plus(t_model *model);
void					cpy_dof(t_dof_plus *src, t_dof_plus *dest);

//______IMG.C___________________________________________________________________
void					ini_img(t_model *model);
void					img_pix_put(t_model *mod, t_pnt_2d *point, int clr);
void					render_next_img(t_model *model);

//______LINE.C__________________________________________________________________
void					draw_line(t_model *mod,
							t_pnt_2d_clr *pnt_a, t_pnt_2d_clr *pnt_b);

//______MAIN.C__________________________________________________________________
int						main(int argc, char **argv);

//______MAP_CREATOR.C___________________________________________________________
char					*create_map(char *str);

//______MAP_CREATOR_UTILS.C_____________________________________________________
void					insert_empty_char(t_list **fds);
char					*create_new_file(char *str, int *new_fd);
char					*create_filename(char *str);
t_list					**create_fd_list(char *str);
void					free_fd_list(t_list **fds, int new_fd);

//______MODEL_MOVE.C____________________________________________________________
void					trans_mod(t_model *model, t_bool ovr,
							t_pnt_2d *trans);
void					rot_mod(t_model *model, t_bool ovr, t_pnt_3d *deg);
void					scale_mod(t_model *model, t_bool ovr, double zoom,
							double z_factor);
void					static_auto_rotate(t_model *mod);

//______MODEL.C_________________________________________________________________
t_model					*new_model(int argc, char **argv);
int						auto_changes(t_model *mod);
void					ini_colors(t_model *model);
void					shedule_close(t_model *model);
int						close_model(t_model *model);

//______NODE.C__________________________________________________________________
t_node					*new_node(t_pnt_3d *point);
void					print_node(t_node *node);
void					node2point(t_model *model, t_node *node,
							t_pnt_2d_clr *point);
void					nodes2line(t_model *mod, t_node *n_a, t_node *n_b);

//______NODE_LST.C______________________________________________________________
void					node_add_front(t_node **lst, t_node *new);
void					node_add_back(t_node **lst, t_node *new);
void					free_node_lst(t_node *head);

//______PARSER.C________________________________________________________________
void					load_file(int argc, char **argv, t_model *model);

//______POINT.C_________________________________________________________________
void					*new_point(t_pnt_dim dim, int x, int y, int z);
void					print_pnt_2d(t_pnt_2d *point);
void					print_pnt_3d(t_pnt_3d *point);

//______UTILS.C_________________________________________________________________
double					degree2radian(int degree);
int						radian2degree(double radian);

//______VIEW.C__________________________________________________________________
void					ini_win(t_model *model);
void					center_model(t_model *model);
void					update_view(t_model *model);

//______VIEW_TXT.C______________________________________________________________
void					ini_help(t_model *mod);
void					free_help(t_model *mod);
void					put_help_to_view(t_model *mod);
void					put_stats_to_view(t_model *mod);

//______ZOOM.C__________________________________________________________________
t_bool					static_auto_zoom(t_model *model, t_bool zoom_in);

#endif
