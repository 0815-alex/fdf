/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:22 by astein            #+#    #+#             */
/*   Updated: 2023/05/24 12:16:27 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	translate_model(t_model *model, t_bool overwrite, t_point_2d *trans)
{
	if (overwrite)
	{
		model->dof.x_trans = trans->x;
		model->dof.y_trans = trans->y;
	}
	else
	{
		model->dof.x_trans += trans->x;
		model->dof.y_trans += trans->y;
	}
	free_whatever(model, "p", trans);
	create_next_img(model);
}

void	rotate_model(t_model *model, t_bool overwrite, t_point_3d *rot_degrees)
{
	if (overwrite == ft_true)
	{
		model->dof.x_rot_rad = degree2radian(rot_degrees->x);
		model->dof.y_rot_rad = degree2radian(rot_degrees->y);
		model->dof.z_rot_rad = degree2radian(rot_degrees->z);
	}
	else
	{
		model->dof.x_rot_rad += degree2radian(rot_degrees->x);
		model->dof.y_rot_rad += degree2radian(rot_degrees->y);
		model->dof.z_rot_rad += degree2radian(rot_degrees->z);
	}
	free_whatever(model, "p", rot_degrees);
	create_next_img(model);
}

void	scale_model(t_model *model, t_bool overwrite, double zoom,
		double z_factor)
{
	if (overwrite)
	{
		model->dof.zoom = zoom;
		model->dof.z_factor = z_factor;
	}
	else
	{
		model->dof.zoom += zoom;
		model->dof.z_factor += z_factor;
	}
	create_next_img(model);
}

int	auto_rotate(t_model *model)
{
	static double	random_value;
	static int		random_axis;
	static int		step;

	if (model->dof.auto_rotate)
	{
		if (random_axis == 0 || step >= 20)
		{
			random_value = drand48();
			random_axis = 1 + round(random_value * 2);
			step = 0;
		}
		step++;
		if (random_axis == 1)
			rotate_model(model, ft_false, new_point(pnt_dim_3, 1, 0, 0));
		else if (random_axis == 2)
			rotate_model(model, ft_false, new_point(pnt_dim_3, 0, 1, 0));
		else if (random_axis == 3)
			rotate_model(model, ft_false, new_point(pnt_dim_3, 0, 0, 1));
	}
	else
		sleep(1);
	return (0);
}

void	zoom_to_start(t_model *model)
{
	double		zoom_end;
	double		increment;
	t_point_3d	*rot;
	int			frames;
	int			i;

	rot = new_point(pnt_dim_3, 0, 0, 0);
	zoom_end = model->dof.zoom;
	frames = 50;
	i = 0;
	increment = model->dof.zoom / frames;
	scale_model(model, ft_true, 0.1, model->dof.z_factor);
	sleep(1);
	while (model->dof.zoom < zoom_end)
	{
		if (i < 10)
			scale_model(model, ft_false, (0.5 * increment), 0);
		else if (i < 20)
			scale_model(model, ft_false, increment, 0);
		else if (i < 30)
			scale_model(model, ft_false, (2 * increment), 0);
		else if (i < 40)
			scale_model(model, ft_false, increment, 0);
		else
		{
			if (model->dof.zoom + (increment * 0.5) <= zoom_end)
				scale_model(model, ft_false, (increment * 0.5), 0);
			else
				scale_model(model, ft_true, zoom_end, model->dof.z_factor);
		}
		i++;
	}
	free(rot);
	sleep(1);
}
