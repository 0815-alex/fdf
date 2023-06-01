/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:22 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 00:11:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	trans_mod(t_model *mod, t_bool ovr, t_pnt_2d *trans)
{
	if (ovr == ft_true)
	{
		mod->dof.trans.x = trans->x;
		mod->dof.trans.y = trans->y;
	}
	else
	{
		mod->dof.trans.x += trans->x;
		mod->dof.trans.y += trans->y;
	}
	free_whatever("p", trans);
	render_next_img(mod);
}

void	rot_mod(t_model *mod, t_bool ovr, t_pnt_3d *deg)
{
	if (ovr == ft_true)
	{
		mod->dof.rot_rad.x = degree2radian(deg->x);
		mod->dof.rot_rad.y = degree2radian(deg->y);
		mod->dof.rot_rad.z = degree2radian(deg->z);
	}
	else
	{
		mod->dof.rot_rad.x += degree2radian(deg->x);
		mod->dof.rot_rad.y += degree2radian(deg->y);
		mod->dof.rot_rad.z += degree2radian(deg->z);
		mod->dof.rot_rad.x = fmod(mod->dof.rot_rad.x, 2 * M_PI);
		mod->dof.rot_rad.y = fmod(mod->dof.rot_rad.y, 2 * M_PI);
		mod->dof.rot_rad.z = fmod(mod->dof.rot_rad.z, 2 * M_PI);
	}
	free_whatever("p", deg);
	render_next_img(mod);
}

void	scale_mod(t_model *mod, t_bool ovr, double zoom, double z_factor)
{
	if (ovr == ft_true)
	{
		if (zoom >= 1)
			mod->dof.zoom = zoom;
		else
			mod->dof.zoom = 1;
		if (z_factor >= 0)
			mod->dof.z_factor = z_factor;
		else
		mod->dof.z_factor = 0;
	}
	else
	{
		mod->dof.zoom += zoom;
		if (mod->dof.zoom < 1)
			mod->dof.zoom = 1;
		mod->dof.z_factor += z_factor;
		if (mod->dof.z_factor < 0)
			mod->dof.z_factor = 0;
	}
	render_next_img(mod);
}

void	static_auto_rotate(t_model *mod)
{
	static double	random_value;
	static double	random_sign;
	static int		random_axis;
	static int		step_move;

	if (random_axis == 0 || step_move >= AUTO_MOVE_FRAMES)
	{
		random_value = drand48();
		random_axis = 1 + round(random_value * 2);
		if (random_value < 0.5)
			random_sign = -1;
		else
			random_sign = 1;
		step_move = 0;
	}
	if (mod->dof.auto_color_change && step_move == 0)
		next_clr_map(mod);
	if (random_axis == 1)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, random_sign * 1, 0, 0));
	else if (random_axis == 2)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, random_sign * 1, 0));
	else if (random_axis == 3)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, 0, random_sign * 1));
	step_move++;
}
