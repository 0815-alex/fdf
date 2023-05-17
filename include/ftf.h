/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:51:18 by astein            #+#    #+#             */
/*   Updated: 2023/05/17 22:15:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTF_H
# define FTF_H

# include "../lib/libft_printf/libft_printf.h"
# include "../lib/minilibx/mlx.h"

//LINUX KEYS
# define K_ARROW_LEFT 65361
# define K_ARROW_UP 65362
# define K_ARROW_RIGHT 65363
# define K_ARROW_DOWN 65364

typedef struct s_win
{
	void	*mlx;
	void	*win;
}			t_win;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

#endif