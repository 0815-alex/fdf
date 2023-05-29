/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/29 13:58:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_img(t_model *mod)
{
	size_t	img_size;

	mod->img.mlx_img = mlx_new_image(mod->mlx, mod->win_width,
			mod->win_height);
	mod->img.addr = mlx_get_data_addr(mod->img.mlx_img, &(mod->img.bpp),
			&(mod->img.line_len), &(mod->img.endian));
	img_size = mod->win_height * mod->win_width * sizeof(mod->img.bpp);
	ft_bzero(mod->img.addr, img_size);
}

static void	img_pix_put(t_model *mod, t_point_2d *point, int color)
{
	char	*pixel;
	int		i;

	if (point->x < 1 || point->x >= mod->win_width)
		dbg_printf(no_block, "pixel x coordinate out of window");
	else if (point->y < 1 || point->y > mod->win_height)
		dbg_printf(no_block, "pixel y coordinate out of window");
	else
	{
		i = mod->img.bpp - 8;
		pixel = mod->img.addr + (point->y * mod->img.line_len + point->x
				* (mod->img.bpp / 8));
		while (i >= 0)
		{
			if (mod->img.endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (mod->img.bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

static void	img_line_put(t_model *mod, t_point_3d_colored *pnt_a,
						t_point_3d_colored *pnt_b)
{
	t_point_2d	*curr_point;
	t_point_2d	*delta;
	t_point_2d	*sign;
	t_clr		*cur_clr;
	t_clr		*clr_step;
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
	delta_sum = sqrt(pow((delta->x), 2) + pow((delta->y), 2));
	if (curr_point->x < pnt_b->x)
		sign->x = 1;
	else
		sign->x = -1;
	if (curr_point->y < pnt_b->y)
		sign->y = 1;
	else
		sign->y = -1;
	err = delta->x + delta->y;
	cur_clr = malloc(sizeof(t_clr));
	cpy_color(&pnt_a->color, cur_clr);
	clr_step = step_clr(pnt_a->color, pnt_b->color, delta_sum);
	while (1)
	{
		img_pix_put(mod, curr_point, color2int(*cur_clr));
		cpy_color(clr_step, cur_clr);
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
	free_whatever("ppppp", curr_point, delta, sign, cur_clr,
		clr_step);
}

static void	nodes2line(t_model *mod, t_node *node_1, t_node *node_2)
{
	t_point_3d_colored	*p1;
	t_point_3d_colored	*p2;

	p1 = malloc(sizeof(t_point_3d_colored));
	p2 = malloc(sizeof(t_point_3d_colored));
	node2point(mod, node_1, p1);
	node2point(mod, node_2, p2);
	img_line_put(mod, p1, p2);
	free_whatever("pp", p1, p2);
}

void	create_next_img(t_model *mod)
{
	t_node	*cur_node;

	ft_bzero(mod->img.addr, mod->win_height * mod->win_width
		* sizeof(mod->img.bpp));
	cur_node = mod->net;
	while (cur_node)
	{
		if (cur_node->west)
			nodes2line(mod, cur_node, cur_node->west);
		if (cur_node->north)
			nodes2line(mod, cur_node, cur_node->north);
		(cur_node) = (cur_node)->next;
	}
	free_whatever("p", cur_node);
	update_image(mod);
}
