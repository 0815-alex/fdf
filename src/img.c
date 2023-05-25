/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 12:45:30 by astein           ###   ########.fr       */
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
		dbg_printf(model, no_block, "pixel x coordinate out of window");
	else if (point->y < 1 || point->y > model->win_height)
		dbg_printf(model, no_block, "pixel y coordinate out of window");
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

static void	img_line_put(t_model *model, t_point_3d_colored *pnt_a,
		t_point_3d_colored *pnt_b)
{
	t_point_2d	*curr_point;
	t_point_2d	*delta;
	t_point_2d	*sign;
	t_color		*cur_color;
	t_color		*color_step;
	int			err;
	int			e2;
	int			delta_sum;

	curr_point = malloc(sizeof(t_point_2d));
	delta = malloc(sizeof(t_point_2d));
	sign = malloc(sizeof(t_point_2d));
	curr_point->x = pnt_a->x;
	curr_point->y = pnt_a->y;
	delta->x = abs(pnt_b->x - curr_point->x);
	delta->y = -abs(pnt_b->y - curr_point->y);
	delta_sum = sqrt(pow((pnt_b->x - curr_point->x),2) + pow((pnt_b->y - curr_point->y),2));
	if (curr_point->x < pnt_b->x)
		sign->x = 1;
	else
		sign->x = -1;
	if (curr_point->y < pnt_b->y)
		sign->y = 1;
	else
		sign->y = -1;
	err = delta->x + delta->y;
	cur_color = malloc(sizeof(t_color));
	cur_color->red = pnt_a->color.red;
	cur_color->green = pnt_a->color.green;
	cur_color->blue = pnt_a->color.blue;
	color_step = calculate_step_color(pnt_a->color, pnt_b->color, delta_sum);
	while (1)
	{
		img_pix_put(model, curr_point, color2int(*cur_color));
		cur_color->red += color_step->red;
		cur_color->green += color_step->green;
		cur_color->blue += color_step->blue;
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
	free_whatever(model, "ppppp", curr_point, delta, sign, cur_color,
			color_step);
}

static void	nodes2line(t_model *model, t_node *node_1, t_node *node_2)
{
	t_point_3d_colored	*p1;
	t_point_3d_colored	*p2;

	p1 = malloc(sizeof(t_point_3d_colored));
	p2 = malloc(sizeof(t_point_3d_colored));
	node2point(model, node_1, p1);
	node2point(model, node_2, p2);
	img_line_put(model, p1, p2);
	free_whatever(model, "pp", p1, p2);
}

void	create_next_img(t_model *model)
{
	t_node	*cur_node;

	ft_bzero(model->img.addr, model->win_height * model->win_width
			* sizeof(model->img.bpp));
	cur_node = model->net;
	while (cur_node)
	{
		if (cur_node->west)
			nodes2line(model, cur_node, cur_node->west);
		if (cur_node->north)
			nodes2line(model, cur_node, cur_node->north);
		(cur_node) = (cur_node)->next;
	}
	free_whatever(model, "p", cur_node);
	update_image(model);
}
