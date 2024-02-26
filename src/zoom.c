/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:22 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 21:15:36 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	performs a smooth zoom between two different zoom values
 * 
 *			the amount of frames can be set in the fdf.h file 'AUTO_ZOOM_FRAMES'
			it will return ft_true when the zoom is completed
				(aka after 'AUTO_ZOOM_FRAMES' calls)
			
			to make it smooth i'm using the following cos function 
			zoom = start + (((1 + cos(x)) / 2) * (end - start))
			(x is between PI and 2PI)

			to avoid potential rounding errors, for the last frame the zoom end
			value is used (instead of an increment using the formula)
 * 
 * @param	mod			ptr to the struct that contains all info about the model
 * @param	zoom_rng	see function 'static_auto_zoom'
 * @return	t_bool		see function 'static_auto_zoom'
 */
static t_bool	do_zoom_step(t_model *mod, double *zoom_rng)
{
	static int	cur_step;
	double		cur_zoom;
	double		cur_step_pi;

	if (cur_step < AUTO_ZOOM_FRAMES)
	{
		if (zoom_rng[1] != zoom_rng[0])
		{
			cur_step_pi = M_PI
				+ ((double)(cur_step + 1) / AUTO_ZOOM_FRAMES) * M_PI;
			cur_zoom = zoom_rng[0] + ((1 + (cos(cur_step_pi))) / 2)
				* (zoom_rng[1] - zoom_rng[0]);
			scale_mod(mod, ft_true, cur_zoom, mod->dof.z_factor);
		}
		cur_step++;
		return (ft_false);
	}
	else
	{
		scale_mod(mod, ft_true, zoom_rng[1], mod->dof.z_factor);
		zoom_rng[0] = 0;
		cur_step = 0;
		return (ft_true);
	}
}

/**
 * @brief	only called by 'auto_changes'
 * 			NOTE:	if you want to initialize a zoom u need to set the
 *		 			'mod->dof.auto_zoom' value to 1 / -1 for a zoom out /in
 * 
 * 			'auto_changes' will call this function until it returns ft_true to
 * 			to signal that the zoom is completed. each time this function is
 * 			called a new frame will be generated via 'do_zoom_step'.
 * 
 * 			on the first call the static var 'zoom_rng[0]' will be 0 and
 * 			therfore the zoom wil be initialized by defining the start and end
 * 			zoom value in 'zoom_rng'
 
 * 			the variable zoom_rng holds:
 * 				[0] =	START 	value for the zoom
 * 				[1] =	END		value for the zoom
 * 
 * 			the zoom range is set like:
 * 				big:	set via 'center_model' aka the biggest possible zoom
 * 				small:	set via fdf.h parameter 'AUTO_ZOOM_INI_LEVEL'
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 * @param	zoom_in defining the zoom direction (in or out)
 * @return	t_bool
 * 				ft_true		if zoom is finished
 * 				ft_false	if zoom isn't finished yet
 */
t_bool	static_auto_zoom(t_model *mod, t_bool zoom_in)
{
	static double	zoom_rng[2];
	t_dof_plus		*cur_dof;

	if (zoom_rng[0] == 0)
	{
		if (zoom_in)
		{
			zoom_rng[0] = mod->dof.zoom;
			cur_dof = malloc(sizeof(t_dof_plus));
			cpy_dof(&mod->dof, cur_dof);
			center_model(mod);
			zoom_rng[1] = mod->dof.zoom;
			cpy_dof(cur_dof, &mod->dof);
			free(cur_dof);
		}
		else
		{
			zoom_rng[0] = mod->dof.zoom;
			zoom_rng[1] = AUTO_ZOOM_INI_LEVEL;
		}
	}
	return (do_zoom_step(mod, zoom_rng));
}
