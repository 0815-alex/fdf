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

/**
 * @file	model_move.c
 * @author	astein
 * @brief	This file should manage all movments of the model such as
 * 				- translating			-> 'trans_mod'
 * 				- rotating				-> 'rot_mod'
 * 				- scaling (x,y and z)	-> 'scale_mod'
 * 
 * 			it can also autorotate the model via 'static_auto_rotate
 */
#include "../include/fdf.h"

/**
 * @brief	set the 'mod->dof.trans' parameters. after applying the changes a
 * 			new image will be rendered and showed via 'render_next_img'
 * 
 * 			the translation is set by the parameter 'trans' which is either the
 * 			new translation or a change to the current translation, depending
 * 			on the 't_bool' parameter 'ovr' (overwrite)
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 * @param	ovr 	defines if 'trans' contains absolute or incremental values
 * @param	trans 	new absolute or incremental values for TRANSLATION
 */
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

/**
 * @brief	set the 'mod->dof.rot_rad' parameters. after applying the changes a
 * 			new image will be rendered and showed via 'render_next_img'
 * 
 * 			the rotation is set by the parameter 'deg' which is either the
 * 			new rotation or a change to the current rotation, depending
 * 			on the 't_bool' parameter 'ovr' (overwrite). the given rotation is
 * 			in DEGREES and therfore will be converted into RADIAN using 
 * 			'degree2radian'
 * 			
 * 			to prevent overflow (higher than 360 degree or 2*Pi radian)
 * 				-> a modulo operation (2*PI) will be performed
 * 
 * @param	mod		pointer to the struct that contains all info about the model 
 * @param	ovr 	defines if 'deg' contains absolute or incremental values 
 * @param	deg 	new absolute or incremental values for ROTATION 
 */
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
	}
	mod->dof.rot_rad.y = fmod(mod->dof.rot_rad.y, 2 * M_PI);
	mod->dof.rot_rad.x = fmod(mod->dof.rot_rad.x, 2 * M_PI);
	mod->dof.rot_rad.z = fmod(mod->dof.rot_rad.z, 2 * M_PI);
	free_whatever("p", deg);
	render_next_img(mod);
}

/**
 * @brief	set the 'mod->dof.zoom' amd 'mod->dof.z_factor' parameters. after
 * 			applying the changes a new image will be rendered and showed via
 * 			'render_next_img'
 * 
 * 			the scaling is set by the parameters 'zoom' (for x and y values) and
 * 			'z_factor' (for z values). the params are either absolute or
 * 			incremental values depending on the 't_bool' parameter
 * 			'ovr' (overwrite).
 * 
 * 			if 'zoom' is smaller than 1 it will be set to 1
 * 			if 'z_factor' is smaller than 0 it will be set to 0
 * 
 * @param	mod			ptr to the struct that contains all info about the model 
 * @param	ovr			defines if 'zoom' and 'z_factor' contain abs/inc values
 * @param	zoom		new absolute or incremental values for SCALING x and y  
 * @param	z_factor	new absolute or incremental values for SCALING z
 */
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
