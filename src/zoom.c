/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:22 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 00:11:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

t_bool	static_auto_zoom(t_model *mod, t_bool zoom_in)
{
	static double	zoom_rng[2];
	t_dof_plus		*cur_dof;

	if (zoom_rng[0] == 0)
	{
		if (zoom_in == ft_true)
		{
			zoom_rng[0] = mod->dof.zoom;
			cur_dof = malloc(sizeof(t_dof_plus));
			cpy_dof(&mod->dof, cur_dof);
			center_model(mod);
			zoom_rng[1] = mod->dof.zoom;
			cpy_dof(cur_dof, &mod->dof);
			free(cur_dof);
			dbg_printf(no_block, "(%d2 -> %d2)\n", mod->dof.zoom, zoom_rng[1]);
		}
		else
		{
			zoom_rng[0] = mod->dof.zoom;
			zoom_rng[1] = AUTO_ZOOM_INI_LEVEL;
			dbg_printf(no_block, "(%d2 -> %d2)\n", mod->dof.zoom, zoom_rng[1]);
		}
	}
	return (do_zoom_step(mod, zoom_rng));
}
