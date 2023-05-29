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
	t_point_3d	*step[2];
	int			i;

	step[0] = step_clr(mod->clr_map->zero, mod->clr_map->min, abs(mod->z_min));
	step[1] = step_clr(mod->clr_map->zero, mod->clr_map->max, abs(mod->z_max));
	cur_node = mod->net;
	if (cur_node)
	{
		while (cur_node)
		{
			i = 0;
			cpy_color(&mod->clr_map->zero, &cur_node->color);
			while (cur_node->pnt->z > i)
			{
				cur_node->color.red += step[1]->x;
				cur_node->color.green += step[1]->y;
				cur_node->color.blue += step[1]->z;
				i++;
			}
			i = 0;
			while (cur_node->pnt->z < i)
			{
				cur_node->color.red += step[0]->x;
				cur_node->color.green += step[0]->y;
				cur_node->color.blue += step[0]->z;
				i--;
			}
			cur_node = cur_node->next;
		}
	}
	free_whatever("pp", step[0], step[1]);
}

/*
    HIer muss ich ein 3d punkt nehmen, da t_clr keine negativen
    farb steps speichern kann da unsigned
*/
t_point_3d	*step_clr(t_clr start_color, t_clr end_color, int n_steps)
{
	t_point_3d	*step;

	step = malloc(sizeof(t_point_3d));
	if (abs(n_steps) < 1)
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

/**
 * @brief   copies the RGB values frome src to the ones of dest
 * 
 * @param   src     the t_clr objet to GET the colors FROM
 * @param   dest    the t_clr objet to SET the colors TO
 */
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
