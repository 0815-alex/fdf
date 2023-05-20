/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:51:18 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 22:22:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# ifndef DEBUG
#  define DEBUG 0
# endif

# include "../lib/libft_printf/libft_printf.h"
# include "../lib/minilibx/mlx.h"
# include <math.h>

//******************************************************************************
//		DEFINE KEYS
//******************************************************************************
# define K_ARROW_LEFT 65361
# define K_ARROW_UP 65362
# define K_ARROW_RIGHT 65363
# define K_ARROW_DOWN 65364
# define K_ESC 65307

//******************************************************************************
//		DEFINE COLOR
//******************************************************************************
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF

//******************************************************************************
//		DEFINE TEMINAL COLOR
//******************************************************************************
# define WRITE_COLOR_DEFAULT "\033[0m"
# define WRITE_COLOR_RED "\033[31m"
# define WRITE_COLOR_GREEN "\033[32m"
# define WRITE_COLOR_ORANGE "\033[33m"

//******************************************************************************
//		STRUCTS FOR HANDLING LISTS
//******************************************************************************
typedef struct s_dbg
{
	int				count_stack_depth;
}					t_dbg;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_node
{
	int				x;
	int				y;
	int				z;
	struct s_node	*next;
	struct s_node	*west;
	struct s_node	*north;
}					t_node;

typedef struct s_model
{
	void			*mlx;
	void			*win;
	struct s_node	*net;
	int				width;
	int				height;
	int				x_trans;
	int				y_trans;
	double			x_rot_rad;
	double			y_rot_rad;
	double			z_rot_rad;
	double				zoom;
	float			z_factor;
	int				color;
	struct s_dbg	*dbg;
}					t_model;

typedef enum e_dbg_flag
{
	error_block = -1,
	no_block = 0,
	start_block = 1,
	end_block = 2
}					t_dbg_flag;

//******************************************************************************
//		VIEW.C
//******************************************************************************
void				ini_win(t_model *model);
void				draw_test_line(t_model *model);
void				draw_net(t_model *model);

//******************************************************************************
//		CONTROLLER_KEYS.C
//******************************************************************************
int					deal_key(int key, t_model *model);

//******************************************************************************
//		CONTROLLER_MOUSE.C
//******************************************************************************
int					deal_mouse(int button, t_model *model);

//******************************************************************************
//		MODEL.C
//******************************************************************************
t_model				*new_model(int argc, char **argv);
void				node2point(t_model *model, t_node *node, t_point *point);

//******************************************************************************
//		PARSER.C
//******************************************************************************
void				load_file(int argc, char **argv, t_model *model);

//******************************************************************************
//		NODE.C
//******************************************************************************
void				print_node(t_model *model, t_node *node);
char				*node2str(t_model *model, t_node *node);
void				print_net(t_model *model);
t_node				*node_last(t_node *lst);
void				node_add_front(t_node **lst, t_node *new);
void				node_add_back(t_node **lst, t_node *new);

//******************************************************************************
//		POINT.C
//******************************************************************************
void				print_point(t_model *model, t_point *point);
char				*point2str(t_model *model, t_point *point);

//******************************************************************************
//		DEBUG.C
//******************************************************************************
void				init_debug(t_model *model, int curr_stack_depth);
void				dbg_printf(t_model *model, t_dbg_flag dbg_flg, char *str,
						...);

//******************************************************************************
//		FDF_UTILS.C
//******************************************************************************
double				degree2radian(int degree);
int					radian2degree2(double radian);

#endif