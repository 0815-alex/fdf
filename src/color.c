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
	t_node		*cur_node;
	t_point_3d	*step_neg;
	t_point_3d	*step_pos;
	int			i;

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
				cur_node->color.red += step_pos->x;
				cur_node->color.green += step_pos->y;
				cur_node->color.blue += step_pos->z;
				i++;
			}
			i = 0;
			while (cur_node->pnt->z < i)
			{
				cur_node->color.red += step_neg->x;
				cur_node->color.green += step_neg->y;
				cur_node->color.blue += step_neg->z;
				i--;
			}
			cur_node = cur_node->next;
		}
	}
	if (abs(mod->z_min) != 0)
		free_whatever("p", step_neg);
	if (abs(mod->z_max) != 0)
		free_whatever("p", step_pos);
}

/*
    HIer muss ich ein 3d punkt nehmen, da t_clr keine negativen
    farb steps speichern kann da unsigned
*/
t_point_3d	*calculate_step_color(t_clr start_color, t_clr end_color,
				int n_steps)
{
	t_point_3d	*step;

	step = malloc(sizeof(t_point_3d));
	if (n_steps < 1)
	{
		step->x = end_color.red;
		step->y = end_color.green;
		step->z = end_color.blue;
	}
	else
	{
		step->x = (int)(end_color.red - start_color.red) / n_steps;
		step->y = (int)(end_color.green - start_color.green) / n_steps;
		step->z = (int)(end_color.blue - start_color.blue) / n_steps;
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
