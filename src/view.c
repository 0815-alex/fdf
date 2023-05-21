/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/21 01:52:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_win(t_model *model)
{
	int	screen_width;
	int	screen_height;

	screen_width = 0;
	screen_height = 0;
	dbg_printf(model, start_block, "ini_win");
	model->mlx = mlx_init();
	mlx_get_screen_size(model->mlx, &screen_width, &screen_height);
	model->width = screen_width - 700;
	model->height = screen_height - 300;
	model->win = mlx_new_window(model->mlx, model->width, model->height,
			"astein | fdf");
	dbg_printf(model, end_block, "ini_win");
}

void	draw_point(t_model *model, t_point *point)
{
	mlx_pixel_put(model->mlx, model->win, point->x, point->y, model->color);
}

void	draw_line(t_model *model, t_point *pnt_a, t_point *pnt_b)
{
	t_point	*curr_point;
	t_point	*delta;
	t_point	*sign;
	int		err;
	int		e2;

	// dbg_printf(model, start_block, "draw_line");
	// dbg_printf(model, no_block, ft_strjoin(ft_strjoin(point2str(model, pnt_a),
					// "-> "), point2str(model, pnt_b)));
	curr_point = malloc(sizeof(t_point));
	delta = malloc(sizeof(t_point));
	sign = malloc(sizeof(t_point));
	curr_point->x = pnt_a->x;
	curr_point->y = pnt_a->y;
	delta->x = abs(pnt_b->x - curr_point->x);
	delta->y = -abs(pnt_b->y - curr_point->y);
	if (curr_point->x < pnt_b->x)
		sign->x = 1;
	else
		sign->x = -1;
	if (curr_point->y < pnt_b->y)
		sign->y = 1;
	else
		sign->y = -1;
	err = delta->x + delta->y;
	while (1)
	{
		draw_point(model, curr_point);
		if (curr_point->x == pnt_b->x && curr_point->y == pnt_b->y)
			break ;
		e2 = 2 * err;
		if (e2 > delta->y)
		{
			err += delta->y;
			curr_point->x += sign->x;
		}
		if (e2 < delta->x)
		{
			err += delta->x;
			curr_point->y += sign->y;
		}
	}
	free(curr_point);
	free(delta);
	free(sign);
	// dbg_printf(model, end_block, "draw_line");
}

void	draw_test_line(t_model *model)
{
	t_point	*point_a;
	t_point	*point_b;

	dbg_printf(model, start_block, "draw_test_line");
	point_a = malloc(sizeof(t_point));
	point_b = malloc(sizeof(t_point));
	point_a->x = 15;
	point_a->y = 15;
	point_b->x = 25;
	point_b->y = 25;
	draw_line(model, point_a, point_b);
	dbg_printf(model, end_block, "draw_test_line");
	free(point_a);
	free(point_b);
}

void	draw_net(t_model *model)
{
	t_node	*cur_node;
	t_point	*cur_point;
	t_point	*cur_conn_point;

	dbg_printf(model, start_block, "draw_net");
	cur_node = model->net;
	cur_point = malloc(sizeof(t_point));
	cur_conn_point = malloc(sizeof(t_point));
	while (cur_node)
	{
		node2point(model, cur_node, cur_point);
		draw_point(model, cur_point);
		if (cur_node->west)
		{
			node2point(model, cur_node->west, cur_conn_point);
			draw_line(model, cur_point, cur_conn_point);
		}
		if (cur_node->north)
		{
			node2point(model, cur_node->north, cur_conn_point);
			draw_line(model, cur_point, cur_conn_point);
		}
		(cur_node) = (cur_node)->next;
	}
	free(cur_node);
	free(cur_point);
	free(cur_conn_point);
	dbg_printf(model, end_block, "draw_net");
}
