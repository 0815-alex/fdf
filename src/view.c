/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 14:43:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

void	ini_win(t_model *model, int width, int heigth, char *title)
{
	dbg_printf(model, start_block, "ini_win");
	model->mlx = mlx_init();
	model->win = mlx_new_window(model->mlx, width, heigth, title);
	dbg_printf(model, end_block, "ini_win");
}

void	put_point(t_model *model, t_point *point, int color)
{
	dbg_printf(model, start_block, "put_point");
	mlx_pixel_put(model->mlx, model->win, point->x, point->y, color);
	print_point(model, point);
	dbg_printf(model, end_block, "put_point");
}

void	put_line(t_model *model, t_point *pnt_a, t_point *pnt_b, int color)
{
	t_point	*curr_point;
	t_point	*delta;
	t_point	*sign;
	int		err;
	int		e2;

	dbg_printf(model, start_block, "put_line");
	// print_point(model, pnt_a);
	dbg_printf(model, no_block, ft_strjoin(ft_strjoin(point2str(model, pnt_a), "-> "), point2str(model, pnt_b)));
	// print_point(model, pnt_b);
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
		// ft_printf("got point and delta...");
		put_point(model, curr_point, color);
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
	dbg_printf(model, end_block, "put_line");
}

void	put_test_line(t_model *model)
{
	t_point	*point_a;
	t_point	*point_b;

	dbg_printf(model, start_block, "put_test_line");
	point_a = malloc(sizeof(t_point));
	point_b = malloc(sizeof(t_point));
	point_a->x = 15;
	point_a->y = 15;
	point_b->x = 25;
	point_b->y = 25;
	put_line(model, point_a, point_b, COLOR_GREEN);
	dbg_printf(model, end_block, "put_test_line");
}

void	put_net(t_model *model, int color, int x_rotate, int y_rotate)
{
	t_node	*cur_node;
	t_point	*cur_point;
	t_point	*cur_conn_point;

	dbg_printf(model, start_block, "put_net");
	cur_node = model->net;
	cur_point = malloc(sizeof(t_point));
	cur_conn_point = malloc(sizeof(t_point));
	while (cur_node)
	{
		node2point(model, cur_node, cur_point, x_rotate, y_rotate);
		//draw point
		put_point(model, cur_point, COLOR_GREEN);
		//draw line to west
		if (cur_node->west)
		{
			node2point(model, cur_node->west, cur_conn_point, x_rotate,
					y_rotate);
			put_line(model->win, cur_point, cur_conn_point, color);
		}
		// //draw line to north
		// if (cur_node->north)
		// {
		// 	node2point(model,cur_node->north, cur_conn_point, x_rotate,
					// y_rotate);
					// 	put_line(model->win, cur_point, cur_conn_point, color);
					// }
					(cur_node) = (cur_node)->next;
	}
	dbg_printf(model, end_block, "put_net");
	// free(cur_node);
	// free(cur_point);
	// free(cur_conn_point);
}
