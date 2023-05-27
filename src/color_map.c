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

void	ini_color_maps(t_model *mod)
{
	mod->color_map = NULL;
	add_m(mod, (t_clr){0, 0, 255}, (t_clr){255, 255, 255}, (t_clr){255, 0, 0});
	add_m(mod, (t_clr){0, 0, 255}, (t_clr){0, 255, 0}, (t_clr){255, 0, 0});
	add_m(mod, (t_clr){0, 0, 255}, (t_clr){255, 255, 255}, (t_clr){255, 0,
			0});
	add_m(mod, (t_clr){255, 0, 0}, (t_clr){255, 255, 0}, (t_clr){0, 255, 0});
	add_m(mod, (t_clr){0, 0, 0}, (t_clr){255, 0, 0}, (t_clr){255, 255, 0});
	add_m(mod, (t_clr){0, 0, 255}, (t_clr){0, 255, 255}, (t_clr){0, 128,
			255});
	add_m(mod, (t_clr){68, 1, 84}, (t_clr){40, 115, 147}, (t_clr){18, 135,
			58});
	add_m(mod, (t_clr){0, 255, 255}, (t_clr){0, 128, 255}, (t_clr){0, 0,
			255});
	add_m(mod, (t_clr){255, 0, 0}, (t_clr){255, 128, 0}, (t_clr){255, 255,
			0});
	add_m(mod, (t_clr){0, 0, 0}, (t_clr){128, 128, 128}, (t_clr){255, 255,
			255});
	add_m(mod, (t_clr){255, 204, 204}, (t_clr){204, 255, 204}, (t_clr){204,
			204, 255});
	add_m(mod, (t_clr){51, 25, 0}, (t_clr){102, 51, 0}, (t_clr){153, 76, 0});
	add_m(mod, (t_clr){255, 204, 0}, (t_clr){255, 102, 0}, (t_clr){204, 0,
			0});
	add_m(mod, (t_clr){255, 102, 255}, (t_clr){204, 255, 204}, (t_clr){255,
			255, 102});
	add_m(mod, (t_clr){255, 255, 255}, (t_clr){128, 128, 128}, (t_clr){0, 0,
			0});
	add_m(mod, (t_clr){0, 255, 0}, (t_clr){255, 255, 0}, (t_clr){255, 0, 0});
}

t_color_map	*add_m(t_model *mod, t_clr min, t_clr zero, t_clr max)
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
	if (!mod->color_map)
	{
		mod->color_map = new_map;
		new_map->next = new_map;
		new_map->previous = new_map;
	}
	else
	{
		mod->color_map->previous->next = new_map;
		new_map->next = mod->color_map;
		new_map->previous = mod->color_map->previous;
		mod->color_map->previous = new_map;
	}
	return (new_map);
}

void	free_color_maps(t_model *mod)
{
	mod->color_map->previous->next = NULL;
	while (mod->color_map->next)
	{
		mod->color_map = mod->color_map->next;
		free(mod->color_map->previous);
	}
}
