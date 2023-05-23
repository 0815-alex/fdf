/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 18:48:56 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	img_pix_put(t_model *model, t_point *point, int color)
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
			/* big endian, MSB is the leftmost bit */
			if (model->img.endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			/* little endian, LSB is the leftmost bit */
			else
				*pixel++ = (color >> (model->img.bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

static void	draw_line(t_model *model, t_point *pnt_a, t_point *pnt_b)
{
	t_point	*curr_point;
	t_point	*delta;
	t_point	*sign;
	int		err;
	int		e2;

	// dbg_printf(model, start_block, "draw_line");
	// dbg_printf(model, no_block, ft_strjoin(ft_strjoin(point2str(model,
	// pnt_a),
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
	free(curr_point);
	free(delta);
	free(sign);
	// dbg_printf(model, end_block, "draw_line");
}

void	create_next_img(t_model *model)
{
	t_node	*cur_node;
	t_point	*cur_point;
	t_point	*cur_conn_point;
	int		i;
	int		j;

	dbg_printf(model, start_block, "create_next_img");
	dbg_printf(model, no_block, "new image size: %i, %i", model->win_width,
			model->win_height);
	i = 0;
	j = 0;
	if (!model->img.mlx_img)
	{
		model->img.mlx_img = mlx_new_image(model->mlx, model->win_width,
				model->win_height);
		model->img.addr = mlx_get_data_addr(model->img.mlx_img,
											&(model->img.bpp),
											&(model->img.line_len),
											&(model->img.endian));
	}
	else
	{
		dbg_printf(model, start_block, "blacked picture");
		ft_bzero(model->img.addr, model->win_height * model->win_width
				* sizeof(model->img.bpp));
		dbg_printf(model, end_block, "blacked picture");
	}
	dbg_printf(model, no_block, "new img adress: %s", model->img.addr);
	cur_node = model->net;
	cur_point = malloc(sizeof(t_point));
	cur_conn_point = malloc(sizeof(t_point));
	while (cur_node)
	{
		node2point(model, cur_node, cur_point);
		img_pix_put(model, cur_point, model->color);
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
	dbg_printf(model, end_block, "create_next_img");
}
