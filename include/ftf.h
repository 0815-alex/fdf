/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:51:18 by astein            #+#    #+#             */
/*   Updated: 2023/05/18 18:54:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTF_H
# define FTF_H

# include "../lib/libft_printf/libft_printf.h"
# include "../lib/minilibx/mlx.h"

//******************************************************************************
//		DEFINE KEYS
//******************************************************************************
# define K_ARROW_LEFT 65361
# define K_ARROW_UP 65362
# define K_ARROW_RIGHT 65363
# define K_ARROW_DOWN 65364

//******************************************************************************
//		STRUCTS FOR HANDLING LISTS
//******************************************************************************

typedef struct s_win
{
	void			*mlx;
	void			*win;
}					t_win;

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

//******************************************************************************
//		PARSER.C
//******************************************************************************
void				load_file(int argc, char **argv, t_node **net);

//******************************************************************************
//		NODE.C
//******************************************************************************
t_node				*node_last(t_node *lst);
void				node_add_front(t_node **lst, t_node *new);
void				node_add_back(t_node **lst, t_node *new);
#endif