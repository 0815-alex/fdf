/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:21:14 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 00:54:02 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_colors(t_model *mod)
{
	t_node	*cur_node;
	t_clr	*step_neg;
	t_clr	*step_pos;
	int		i;

	if (abs(mod->z_min) != 0)
		step_neg = calculate_step_color(mod->color_map->zero,
				mod->color_map->min, abs(mod->z_min));
	if (abs(mod->z_max) != 0)
		step_pos = calculate_step_color(mod->color_map->zero,
				mod->color_map->max, abs(mod->z_max));
	cur_node = mod->net;
	if (cur_node)
	{
		while (cur_node)
		{
			i = 0;
			cur_node->color.red = mod->color_map->zero.red;
			cur_node->color.green = mod->color_map->zero.green;
			cur_node->color.blue = mod->color_map->zero.blue;
			while (cur_node->pnt->z > i)
			{
				cur_node->color.red += step_pos->red;
				cur_node->color.green += step_pos->green;
				cur_node->color.blue += step_pos->blue;
				i++;
			}
			i = 0;
			while (cur_node->pnt->z < i)
			{
				cur_node->color.red += step_neg->red;
				cur_node->color.green += step_neg->green;
				cur_node->color.blue += step_neg->blue;
				i--;
			}
			cur_node = cur_node->next;
		}
	}
	if (abs(mod->z_min) != 0)
		free_whatever(mod, "p", step_neg);
	if (abs(mod->z_max) != 0)
		free_whatever(mod, "p", step_pos);
}

t_clr	*calculate_step_color(t_clr start_color, t_clr end_color, int n_steps)
{
	t_clr	*step;

	step = malloc(sizeof(t_clr));
	if (n_steps < 1)
	{
		step->red = end_color.red;
		step->green = end_color.green;
		step->blue = end_color.blue;
	}
	else
	{
		step->red = (end_color.red - start_color.red) / n_steps;
		step->green = (end_color.green - start_color.green) / n_steps;
		step->blue = (end_color.blue - start_color.blue) / n_steps;
	}
	return (step);
}

void	cpy_color(t_clr *src, t_clr *dest)
{
	dest->red = src->red;
	dest->green = src->green;
	dest->blue = src->blue;
}

int	color2int(t_clr clr)
{
	int	i_clr;

	i_clr = (255 << 24) | (clr.red << 16) | (clr.green << 8) | clr.blue;
	return (i_clr);
}
