/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:14 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 12:58:59 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief   only called from 'new_model' inizializing all net related values
 * 			'mod->center_pnt' 'mod->net_dim' 'mod->z_min' 'mod->z_max' 
 * 
 * @param   mod pointer to the struct that contains all info about the model
 */
void	ini_net_details(t_model *mod)
{
	mod->center_pnt.x = INT_MIN;
	mod->center_pnt.y = INT_MIN;
	mod->center_pnt.z = INT_MIN;
	mod->net_dim.x = INT_MIN;
	mod->net_dim.y = INT_MIN;
	mod->z_min = INT_MAX;
	mod->z_max = INT_MIN;
}

/**
 * @brief	only called from parser.c each time a new node is loaded to update
 * 			the current net dimensions:
 *				'mod->net_dim'
 *				'mod->z_min'
 *				'mod->z_max'
 *
 * @param	mod	pointer to the struct that contains all info about the model
 * @param	x	new x value to be checked
 * @param	y	new y value to be checked
 * @param	z	new z value to be checked
 */
void	update_max_values(t_model *mod, int x, int y, int z)
{
	if (mod->net_dim.x == INT_MIN)
		mod->net_dim.x = x;
	else
	{
		if (x > mod->net_dim.x)
			mod->net_dim.x = x;
	}
	if (mod->net_dim.y == INT_MIN)
		mod->net_dim.y = y;
	else
	{
		if (y > mod->net_dim.y)
			mod->net_dim.y = y;
	}
	if (z < mod->z_min)
		mod->z_min = z;
	if (z > mod->z_max)
		mod->z_max = z;
}

/**
 * @brief	set the 'mod->center_pnt' coordinates to the center of the net
 * 			using the 'mod->net_dim', 'mod->z_min' and 'mod->z_max' values
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 */
void	determine_net_center(t_model *mod)
{
	dbg_printf(no_block, "net dimension (%i|%i)", mod->net_dim.x,
		mod->net_dim.y);
	mod->center_pnt.x = ((mod->net_dim.x + 1) / 2);
	mod->center_pnt.y = ((mod->net_dim.y + 1) / 2);
	mod->center_pnt.z = ((mod->z_max - mod->z_min) / 2);
	dbg_printf(no_block, "net center (%i|%i|%i)", mod->center_pnt.x,
		mod->center_pnt.y, mod->center_pnt.z);
}
