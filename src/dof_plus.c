/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dof_plus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:32:46 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 21:25:38 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	only called from 'new_model' inizializing all 'mod->dof' values
 * 			dof = degrees of freedom
 * 
 * @param	mod	pointer to the struct that contains all info about the model 
 */
void	ini_dof_plus(t_model *mod)
{
	dbg_printf(start_block, "ini_dof_plus");
	mod->dof.trans.x = 100;
	mod->dof.trans.y = 100;
	mod->dof.rot_rad.x = degree2radian(0);
	mod->dof.rot_rad.y = degree2radian(0);
	mod->dof.rot_rad.z = degree2radian(0);
	mod->dof.zoom = AUTO_ZOOM_INI_LEVEL;
	mod->dof.z_factor = 1.1;
	mod->dof.auto_rot = ft_true;
	mod->dof.auto_zoom = ft_true;
	mod->dof.auto_color_change = ft_true;
	dbg_printf(end_block, "ini_dof_plus");
}

/**
 * @brief	only called from 'static_auto_zoom' to get a copy of the current
 * 			dof plus settings
 * 
 * @param	src		t_dof_plus to copy FROM
 * @param	dest	 t_dof_plus to copy TO
 */
void	cpy_dof(t_dof_plus *src, t_dof_plus *dest)
{
	dest->trans.x = src->trans.x;
	dest->trans.y = src->trans.y;
	dest->rot_rad.x = src->rot_rad.x;
	dest->rot_rad.y = src->rot_rad.y;
	dest->rot_rad.z = src->rot_rad.z;
	dest->zoom = src->zoom;
	dest->z_factor = src->z_factor;
	dest->auto_rot = src->auto_rot;
	dest->auto_zoom = src->auto_zoom;
}
