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

/**
 * @brief 	creates a new struct instance 'new_map' of the type 't_clr_map'
 * 			the 'min' 'max' and 'zero' colors are set via the parameters
 *          the 'new_map' is then inserted at the end of the    
 *          doubly linked list 'mod->clr_map'
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 * @param	min		defining the color of the LOWEST  z-value(s)
 * @param	zero 	defining the color of the z-value(s) that are equal to 0
 * @param	max		defining the color of the HIGHEST z-value(s)
 */
static void	add_clr_map(t_model *mod, t_clr min, t_clr zero, t_clr max)
{
	t_clr_map	*new_map;

	new_map = malloc(sizeof(t_clr_map));
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
}

/**
 * @brief	I need more funky colormaps!
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 */
static void	ini_clr_maps_part2(t_model *mod)
{
	add_clr_map(mod, (t_clr){255, 0, 0}, (t_clr){255, 128, 0},
		(t_clr){255, 255, 0});
	add_clr_map(mod, (t_clr){0, 0, 0}, (t_clr){128, 128, 128},
		(t_clr){255, 255, 255});
	add_clr_map(mod, (t_clr){255, 204, 204}, (t_clr){204, 255, 204},
		(t_clr){204, 204, 255});
	add_clr_map(mod, (t_clr){51, 25, 0}, (t_clr){102, 51, 0},
		(t_clr){153, 76, 0});
	add_clr_map(mod, (t_clr){255, 204, 0}, (t_clr){255, 102, 0},
		(t_clr){204, 0, 0});
	add_clr_map(mod, (t_clr){255, 102, 255}, (t_clr){204, 255, 204},
		(t_clr){255, 255, 102});
	add_clr_map(mod, (t_clr){255, 255, 255}, (t_clr){128, 128, 128},
		(t_clr){0, 0, 0});
	add_clr_map(mod, (t_clr){0, 255, 0}, (t_clr){255, 255, 0},
		(t_clr){255, 0, 0});
}

/**
 * @brief	creates a doubly linked list of color map structs with some
 * 			funky colors
 * 			the linked list will be stored in 'mod->clr_map'
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 */
void	ini_clr_maps(t_model *mod)
{
	mod->clr_map = NULL;
	add_clr_map(mod, (t_clr){0, 255, 0}, (t_clr){0, 255, 0},
		(t_clr){0, 255, 0});
	add_clr_map(mod, (t_clr){0, 0, 255}, (t_clr){255, 255, 255},
		(t_clr){255, 0, 0});
	add_clr_map(mod, (t_clr){0, 0, 255}, (t_clr){0, 255, 0},
		(t_clr){255, 0, 0});
	add_clr_map(mod, (t_clr){0, 0, 255}, (t_clr){255, 255, 255},
		(t_clr){255, 0, 0});
	add_clr_map(mod, (t_clr){255, 0, 0}, (t_clr){255, 255, 0},
		(t_clr){0, 255, 0});
	add_clr_map(mod, (t_clr){0, 0, 0}, (t_clr){255, 0, 0},
		(t_clr){255, 255, 0});
	add_clr_map(mod, (t_clr){0, 0, 255}, (t_clr){0, 255, 255},
		(t_clr){0, 128, 255});
	add_clr_map(mod, (t_clr){68, 1, 84}, (t_clr){40, 115, 147},
		(t_clr){18, 135, 58});
	add_clr_map(mod, (t_clr){0, 255, 255}, (t_clr){0, 128, 255},
		(t_clr){0, 0, 255});
	ini_clr_maps_part2(mod);
}

/**
 * @brief	rotates the linked list 'clr_map' of the model FORWARDS
 * 			to apply the change this follows:
 * 				- recaluclate the colors of all nodes with 'ini_colors()'
 * 				- update the view creating a new img with 'create_next_img()'
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 */
void	next_clr_map(t_model *mod)
{
	mod->clr_map = mod->clr_map->next;
	ini_colors(mod);
	create_next_img(mod);
}

/**
 * @brief	frees all nodes of the linked list 'clr_map' stored in 'mod'
 * @param 	mod		pointer to the struct that contains all info about the model
 */
void	free_clr_maps(t_model *mod)
{
	mod->clr_map->previous->next = NULL;
	while (mod->clr_map->next)
	{
		mod->clr_map = mod->clr_map->next;
		free(mod->clr_map->previous);
	}
}
