/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:21:14 by astein            #+#    #+#             */
/*   Updated: 2023/05/29 14:00:18 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_colors(t_model *mod)
{
	t_node		*cur_node;
	t_clr		*step[2];
	int			i;

	step[0] = step_clr(mod->clr_map->zero, mod->clr_map->min, abs(mod->z_min));
	step[1] = step_clr(mod->clr_map->zero, mod->clr_map->max, abs(mod->z_max));
	cur_node = mod->net;
	if (cur_node)
	{
		while (cur_node)
		{
			i = -1;
			cpy_color(&mod->clr_map->zero, &cur_node->color);
			while (cur_node->pnt->z > ++i)
				cpy_color(step[1], &cur_node->color);
			i = -1;
			while (cur_node->pnt->z < --i)
				cpy_color(step[0], &cur_node->color);
			cur_node = cur_node->next;
		}
	}
	free_whatever("pp", step[0], step[1]);
}

t_clr	*step_clr(t_clr start_clr, t_clr end_clr, int n_steps)
{
	t_clr	*step;

	step = malloc(sizeof(t_point_3d));
	if (abs(n_steps) < 1)
		cpy_color(&end_clr, step);
	else
	{
		step->red = (int)(end_clr.red - start_clr.red) / n_steps;
		step->green = (int)(end_clr.green - start_clr.green) / n_steps;
		step->blue = (int)(end_clr.blue - start_clr.blue) / n_steps;
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
