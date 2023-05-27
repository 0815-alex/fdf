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

void	trans_mod(t_model *mod, t_bool ovr, t_point_2d *trans)
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
	free_whatever(mod, "p", trans);
	create_next_img(mod);
}

void	rot_mod(t_model *mod, t_bool ovr, t_point_3d *deg)
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
	}
	free_whatever(mod, "p", deg);
	create_next_img(mod);
}

void	scale_mod(t_model *mod, t_bool ovr, double zoom, double z_factor)
{
	if (ovr == ft_true)
	{
		if (zoom < 1)
			dbg_printf(mod, no_block, "zoom must be >= 1 | is: %i", zoom);
		else
			mod->dof.zoom = zoom;
		if (z_factor < 0)
		{
			mod->dof.z_factor = 0;
			dbg_printf(mod, no_block, "z factor must be >= 0! | is: %i", zoom);
		}
		else
			mod->dof.z_factor = z_factor;
	}
	else
	{
		mod->dof.zoom += zoom;
		mod->dof.z_factor += z_factor;
		if (mod->dof.zoom < 0)
		{
			dbg_printf(mod, no_block, "Zoom must be >= 0! | is: %i",
				mod->dof.zoom);
			mod->dof.zoom -= zoom;
		}
		if (mod->dof.z_factor < 0)
		{
			dbg_printf(mod, no_block, "z factor must be >= 0! | is: %i", zoom);
			mod->dof.z_factor = 0;
		}
	}
	dbg_printf(mod, no_block, "new values: zoom: %d4 | z_factor %d4",
		mod->dof.zoom, mod->dof.z_factor);
	create_next_img(mod);
	dbg_printf(mod, end_block, "scale_mod");
}

int	auto_movements(t_model *mod)
{
	static double	random_value;
	static int		random_axis;
	static int		step_move;

	if (mod->dof.auto_zoom == 1)
	{
		dbg_printf(mod, no_block, "zoom in ist ongoing...");
		if (static_auto_zoom(mod, ft_true) == ft_true)
			mod->dof.auto_zoom = 0;
	}
	else if (mod->dof.auto_zoom == -1)
	{
		dbg_printf(mod, no_block, "zoom out ist ongoing...");
		if (static_auto_zoom(mod, ft_false) == ft_true)
			mod->dof.auto_zoom = 0;
	}
	else if (mod->close_pending)
		close_model(mod);
	else if (!mod->dof.auto_rotate && !mod->dof.auto_color_change)
		usleep(500);
	if (mod->dof.auto_rotate)
	{
		if (random_axis == 0 || step_move >= AUTO_MOVE_FRAMES)
		{
			random_value = drand48();
			random_axis = 1 + round(random_value * 2);
			step_move = 0;
		}
		if (mod->dof.auto_color_change && step_move == 0)
			next_color_map(mod);
		if (random_axis == 1)
			rot_mod(mod, ft_false, new_point(pnt_dim_3, 1, 0, 0));
		else if (random_axis == 2)
			rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, 1, 0));
		else if (random_axis == 3)
			rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, 0, 1));
		step_move++;
	}
	return (0);
}

t_bool	static_auto_zoom(t_model *mod, t_bool zoom_in)
{
	static double	zoom_start;
	static double	zoom_end;
	static double	increment;
	static int		cur_step;
	static int		sign;
	t_dof_plus		*cur_dof;

	if (zoom_start == 0)
	{	
		if (zoom_in == ft_true)
		{
			sign = 1;
			zoom_start = mod->dof.zoom;
			cur_dof = malloc(sizeof(t_dof_plus));
			cpy_dof(&mod->dof, cur_dof);
			center_model(mod);
			zoom_end = mod->dof.zoom;
			cpy_dof(cur_dof, &mod->dof);
			free(cur_dof);
			dbg_printf(mod, no_block, "zoom in (%lf -> %lf)\n", mod->dof.zoom,
				zoom_end);
		}
		else
		{
			sign = -1;
			zoom_start = mod->dof.zoom;
			zoom_end = AUTO_ZOOM_INI_LEVEL;
			dbg_printf(mod, no_block, "zoom in (%lf -> %lf)\n", mod->dof.zoom,
				zoom_end);
		}
		increment = (zoom_end - zoom_start) / AUTO_ZOOM_FRAMES;
	}
	if (mod->dof.zoom != zoom_end)
	{
		if (cur_step < AUTO_ZOOM_FRAMES / 5)
			scale_mod(mod, ft_false, (0.5 * increment), 0);
		else if (cur_step < 2 * (AUTO_ZOOM_FRAMES / 5))
			scale_mod(mod, ft_false, (increment), 0);
		else if (cur_step < 3 * (AUTO_ZOOM_FRAMES / 5))
			scale_mod(mod, ft_false, (2 * increment), 0);
		else if (cur_step < 4 * (AUTO_ZOOM_FRAMES / 5))
			scale_mod(mod, ft_false, (increment), 0);
		else
		{
			if (sign == 1)
			{
				if (mod->dof.zoom + (increment * 0.5) <= zoom_end)
					scale_mod(mod, ft_false, (increment * 0.5), 0);
				else
					scale_mod(mod, ft_true, zoom_end, mod->dof.z_factor);
			}
			else
			{
				if (mod->dof.zoom + (increment * 0.5) >= zoom_end)
					scale_mod(mod, ft_false, (increment * 0.5), 0);
				else
					scale_mod(mod, ft_true, zoom_end, mod->dof.z_factor);
			}
		}
		cur_step++;
	}
	else
	{
		zoom_start = 0;
		zoom_end = 0;
		increment = 0;
		cur_step = 0;
		sign = 0;
		return (ft_true);
	}
	return (ft_false);
}
