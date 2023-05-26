/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 00:53:44 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 00:58:52 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_color_maps(t_model *model)
{
	model->color_map = NULL;
	add_color_map(model, (t_color){0, 0, 255}, (t_color){255, 255, 255},
			(t_color){255, 0, 0});
	add_color_map(model, (t_color){0, 0, 255}, (t_color){0, 255, 0},
			(t_color){255, 0, 0});
	add_color_map(model, (t_color){0, 0, 255}, (t_color){255, 255, 255},
			(t_color){255, 0, 0});
	add_color_map(model, (t_color){255, 0, 0}, (t_color){255, 255, 0},
			(t_color){0, 255, 0});
	add_color_map(model, (t_color){0, 0, 0}, (t_color){255, 0, 0},
			(t_color){255, 255, 0});
	add_color_map(model, (t_color){0, 0, 255}, (t_color){0, 255, 255},
			(t_color){0, 128, 255});
	add_color_map(model, (t_color){68, 1, 84}, (t_color){40, 115, 147},
			(t_color){18, 135, 58});
	add_color_map(model, (t_color){0, 255, 255}, (t_color){0, 128, 255},
			(t_color){0, 0, 255});
	add_color_map(model, (t_color){255, 0, 0}, (t_color){255, 128, 0},
			(t_color){255, 255, 0});
	add_color_map(model, (t_color){0, 0, 0}, (t_color){128, 128, 128},
			(t_color){255, 255, 255});
	add_color_map(model, (t_color){255, 204, 204}, (t_color){204, 255, 204},
			(t_color){204, 204, 255});
	add_color_map(model, (t_color){51, 25, 0}, (t_color){102, 51, 0},
			(t_color){153, 76, 0});
	add_color_map(model, (t_color){255, 204, 0}, (t_color){255, 102, 0},
			(t_color){204, 0, 0});
	add_color_map(model, (t_color){255, 102, 255}, (t_color){204, 255, 204},
			(t_color){255, 255, 102});
	add_color_map(model, (t_color){255, 255, 255}, (t_color){128, 128, 128},
			(t_color){0, 0, 0});
	add_color_map(model, (t_color){0, 255, 0}, (t_color){255, 255, 0},
			(t_color){255, 0, 0});
}

t_color_map	*add_color_map(t_model *model, t_color min, t_color zero,
		t_color max)
{
	t_color_map	*new_map;

	new_map = malloc(sizeof(t_color_map));
	new_map->min.red = min.red;
	new_map->min.green = min.green;
	new_map->min.blue = min.blue;
	new_map->zero.red = zero.red;
	new_map->zero.green = zero.green;
	new_map->zero.blue = zero.blue;
	new_map->max.red = max.red;
	new_map->max.green = max.green;
	new_map->max.blue = max.blue;
	if (!model->color_map)
	{
		model->color_map = new_map;
		new_map->next = new_map;
		new_map->previous = new_map;
	}
	else
	{
		model->color_map->previous->next = new_map;
		new_map->next = model->color_map;
		new_map->previous = model->color_map->previous;
		model->color_map->previous = new_map;
	}
	return (new_map);
}

void	free_color_maps(t_model *model)
{
	model->color_map->previous->next = NULL;
	while (model->color_map->next)
	{
		model->color_map = model->color_map->next;
		free(model->color_map->previous);
	}
}
