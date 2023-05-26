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

void	ini_colors(t_model *model)
{
	t_node	*cur_node;
	t_color	*step_neg;
	t_color	*step_pos;
	int		i;

	if (abs(model->z_min) != 0)
		step_neg = calculate_step_color(model->color_map->zero,
										model->color_map->min,
										abs(model->z_min));
	if (abs(model->z_max) != 0)
		step_pos = calculate_step_color(model->color_map->zero,
										model->color_map->max,
										abs(model->z_max));
	cur_node = model->net;
	if (cur_node)
	{
		while (cur_node)
		{
			// printf("set color to node:\n");
			i = 0;
			cur_node->color.red = model->color_map->zero.red;
			cur_node->color.green = model->color_map->zero.green;
			cur_node->color.blue = model->color_map->zero.blue;
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
	if (abs(model->z_min) != 0)
		free_whatever(model, "p", step_neg);
	if (abs(model->z_max) != 0)
		free_whatever(model, "p", step_pos);
}

t_color	*calculate_step_color(t_color start_color, t_color end_color,
		int n_steps)
{
	t_color	*step;

	step = malloc(sizeof(t_color));
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

int	color2int(t_color color)
{
	int	int_color;

	int_color = (255 << 24) | (color.red << 16) | (color.green << 8) | color.blue;
	return (int_color);
}
