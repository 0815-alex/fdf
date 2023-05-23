/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:22 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 20:11:36 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	translate_model(t_model *model, t_bool overwrite, t_point_2d *trans)
{
	if (overwrite)
	{
		model->x_trans = trans->x;
		model->y_trans = trans->y;
	}
	else
	{
		model->x_trans += trans->x;
		model->y_trans += trans->y;
	}
	free_ptr(trans);
	create_next_img(model);
}

void	rotate_model(t_model *model, t_bool overwrite, t_point_3d *rot_degrees)
{
	if (overwrite)
	{
		model->x_rot_rad = rot_degrees->x;
		model->y_rot_rad = rot_degrees->y;
		model->z_rot_rad = rot_degrees->z;
	}
	else
	{
		model->x_rot_rad += rot_degrees->x;
		model->y_rot_rad += rot_degrees->y;
		model->z_rot_rad += rot_degrees->z;
	}
	free_ptr(rot_degrees);
	create_next_img(model);
}

void	scale_model(t_model *model, t_bool overwrite, int zoom, int z_factor)
{
	if (overwrite)
	{
		model->zoom = zoom;
		model->z_factor = z_factor;
	}
	else
	{
		model->zoom += zoom;
		model->z_factor += z_factor;
	}
	create_next_img(model);
}

int	auto_rotate(void *void_model)
{
	t_model			*model;
	static double	random_value;
	static int		random_axis;
	static int		step;

	model = (t_model *)void_model;
	if (model->auto_rotate)
	{
		if (random_axis == 0 || step >= 45)
		{
			random_value = drand48();
			random_axis = 1 + round(random_value * 2);
		}
		if (step >= 45)
			step = 0;
		step++;
		if (random_axis == 1)
			model->x_rot_rad += (M_PI / 180.0);
		else if (random_axis == 2)
			model->y_rot_rad += (M_PI / 180.0);
		else if (random_axis == 3)
			model->z_rot_rad += (M_PI / 180.0);
		create_next_img(model);
		update_image(model);
	}
	else
	{
		step = 0;
		sleep(1);
	}
	dbg_printf(model, no_block, "Auto Rotate...");
	return (0);
}
