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

void	ini_dof_plus(t_model *model)
{
	dbg_printf(model, start_block, "ini_dof_plus");
	model->dof.trans.x = 100;
	model->dof.trans.y = 100;
	model->dof.rot_rad.x = degree2radian(0);
	model->dof.rot_rad.y = degree2radian(0);
	model->dof.rot_rad.z = degree2radian(0);
	model->dof.zoom = AUTO_ZOOM_INI_LEVEL;
	model->dof.z_factor = 1;
	model->dof.auto_rotate = ft_true;
	model->dof.auto_zoom = 1;
	dbg_printf(model, end_block, "ini_dof_plus");
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
