/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/24 12:32:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_img(t_model *model)
{
	size_t	img_size;

	model->img.mlx_img = mlx_new_image(model->mlx, model->win_width,
			model->win_height);
	model->img.addr = mlx_get_data_addr(model->img.mlx_img, &(model->img.bpp),
			&(model->img.line_len), &(model->img.endian));
	img_size = model->win_height * model->win_width * sizeof(model->img.bpp);
	ft_bzero(model->img.addr, img_size);
}

static void	img_pix_put(t_model *model, t_point_2d *point, int color)
{
	char	*pixel;
	int		i;

	if (point->x < 1 || point->x >= model->win_width)
		dbg_printf(model, no_block, "pixel x coordinate inst printable");
	else if (point->y < 1 || point->y > model->win_height)
		dbg_printf(model, no_block, "pixel y coordinate inst printable");
	else
	{
		i = model->img.bpp - 8;
		pixel = model->img.addr + (point->y * model->img.line_len + point->x
				* (model->img.bpp / 8));
		while (i >= 0)
		{
			if (model->img.endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (model->img.bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

static void	img_line_put(t_model *model, t_point_2d *pnt_a, t_point_2d *pnt_b)
{
	t_point_2d	*curr_point;
	t_point_2d	*delta;
	t_point_2d	*sign;
	int			err;
	int			e2;

	curr_point = malloc(sizeof(t_point_2d));
	delta = malloc(sizeof(t_point_2d));
	sign = malloc(sizeof(t_point_2d));
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
		img_pix_put(model, curr_point, model->color);
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
	free_whatever(model, "ppp", curr_point, delta, sign);
}

void	create_next_img(t_model *model)
{
	t_node		*cur_node;
	t_point_2d	*cur_point;
	t_point_2d	*cur_conn_point;

	ft_bzero(model->img.addr, model->win_height * model->win_width
			* sizeof(model->img.bpp));
	cur_node = model->net;
	cur_point = malloc(sizeof(t_point_2d));
	cur_conn_point = malloc(sizeof(t_point_2d));
	while (cur_node)
	{
		node2point(model, cur_node, cur_point);
		if (cur_node->west)
		{
			node2point(model, cur_node->west, cur_conn_point);
			img_line_put(model, cur_point, cur_conn_point);
		}
		if (cur_node->north)
		{
			node2point(model, cur_node->north, cur_conn_point);
			img_line_put(model, cur_point, cur_conn_point);
		}
		(cur_node) = (cur_node)->next;
	}
	free_whatever(model, "ppp", cur_node, cur_point, cur_conn_point);
	update_image(model);
}