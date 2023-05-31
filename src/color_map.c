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

static	t_color_map	*add_color_map(t_model *mod,
						t_clr min, t_clr zero, t_clr max);
static void			ini_color_maps_part2(t_model *mod);

void	ini_color_maps(t_model *mod)
{
	mod->clr_map = NULL;
	add_color_map(mod, (t_clr){255, 255, 255}, (t_clr){255, 255, 255},
		(t_clr){255, 255, 255});
	add_color_map(mod, (t_clr){0, 0, 255}, (t_clr){255, 255, 255},
		(t_clr){255, 0, 0});
	add_color_map(mod, (t_clr){0, 0, 255}, (t_clr){0, 255, 0},
		(t_clr){255, 0, 0});
	add_color_map(mod, (t_clr){0, 0, 255}, (t_clr){255, 255, 255},
		(t_clr){255, 0, 0});
	add_color_map(mod, (t_clr){255, 0, 0}, (t_clr){255, 255, 0},
		(t_clr){0, 255, 0});
	add_color_map(mod, (t_clr){0, 0, 0}, (t_clr){255, 0, 0},
		(t_clr){255, 255, 0});
	add_color_map(mod, (t_clr){0, 0, 255}, (t_clr){0, 255, 255},
		(t_clr){0, 128, 255});
	add_color_map(mod, (t_clr){68, 1, 84}, (t_clr){40, 115, 147},
		(t_clr){18, 135, 58});
	add_color_map(mod, (t_clr){0, 255, 255}, (t_clr){0, 128, 255},
		(t_clr){0, 0, 255});
	ini_color_maps_part2(mod);
}

static void	ini_color_maps_part2(t_model *mod)
{
	add_color_map(mod, (t_clr){255, 0, 0}, (t_clr){255, 128, 0},
		(t_clr){255, 255, 0});
	add_color_map(mod, (t_clr){0, 0, 0}, (t_clr){128, 128, 128},
		(t_clr){255, 255, 255});
	add_color_map(mod, (t_clr){255, 204, 204}, (t_clr){204, 255, 204},
		(t_clr){204, 204, 255});
	add_color_map(mod, (t_clr){51, 25, 0}, (t_clr){102, 51, 0},
		(t_clr){153, 76, 0});
	add_color_map(mod, (t_clr){255, 204, 0}, (t_clr){255, 102, 0},
		(t_clr){204, 0, 0});
	add_color_map(mod, (t_clr){255, 102, 255}, (t_clr){204, 255, 204},
		(t_clr){255, 255, 102});
	add_color_map(mod, (t_clr){255, 255, 255}, (t_clr){128, 128, 128},
		(t_clr){0, 0, 0});
	add_color_map(mod, (t_clr){0, 255, 0}, (t_clr){255, 255, 0},
		(t_clr){255, 0, 0});
}

void	next_color_map(t_model *mod)
{
	mod->clr_map = mod->clr_map->next;
	ini_colors(mod);
	create_next_img(mod);
}

static t_color_map	*add_color_map(t_model *mod, t_clr min, t_clr zero,
		t_clr max)
{
	t_color_map	*new_map;

	new_map = malloc(sizeof(t_color_map));
	cpy_color(&min, &new_map->min);
	cpy_color(&zero, &new_map->zero);
	cpy_color(&max, &new_map->max);
	if (!mod->clr_map)
	{
		mod->clr_map = new_map;
		new_map->next = new_map;
		new_map->previous = new_map;
	}
	else
	{
		mod->clr_map->previous->next = new_map;
		new_map->next = mod->clr_map;
		new_map->previous = mod->clr_map->previous;
		mod->clr_map->previous = new_map;
	}
	return (new_map);
}

void	free_color_maps(t_model *mod)
{
	mod->clr_map->previous->next = NULL;
	while (mod->clr_map->next)
	{
		mod->clr_map = mod->clr_map->next;
		free(mod->clr_map->previous);
	}
}
