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

void	ini_dof_plus(t_model *mod)
{
	dbg_printf(mod, start_block, "ini_dof_plus");
	mod->dof.trans.x = 100;
	mod->dof.trans.y = 100;
	mod->dof.rot_rad.x = degree2radian(0);
	mod->dof.rot_rad.y = degree2radian(0);
	mod->dof.rot_rad.z = degree2radian(0);
	mod->dof.zoom = AUTO_ZOOM_INI_LEVEL;
	mod->dof.z_factor = 1.1;
	mod->dof.auto_rotate = ft_false;
	mod->dof.auto_zoom = ft_true;
	mod->dof.auto_color_change = ft_false;
	dbg_printf(mod, end_block, "ini_dof_plus");
}

void	cpy_dof(t_dof_plus *src, t_dof_plus *dest)
{
	dest->trans.x = src->trans.x;
	dest->trans.y = src->trans.y;
	dest->rot_rad.x = src->rot_rad.x;
	dest->rot_rad.y = src->rot_rad.y;
	dest->rot_rad.z = src->rot_rad.z;
	dest->zoom = src->zoom;
	dest->z_factor = src->z_factor;
	dest->auto_rotate = src->auto_rotate;
	dest->auto_zoom = src->auto_zoom;
}
