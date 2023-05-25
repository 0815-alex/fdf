/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:22 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 13:24:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	trans_mod(t_model *model, t_bool ovr, t_point_2d *trans)
{
	if (ovr)
	{
		model->dof.trans.x = trans->x;
		model->dof.trans.y = trans->y;
	}
	else
	{
		model->dof.trans.x += trans->x;
		model->dof.trans.y += trans->y;
	}
	free_whatever(model, "p", trans);
	create_next_img(model);
}

void	rot_mod(t_model *model, t_bool ovr, t_point_3d *deg)
{
	if (ovr == ft_true)
	{
		model->dof.rot_rad.x = degree2radian(deg->x);
		model->dof.rot_rad.y = degree2radian(deg->y);
		model->dof.rot_rad.z = degree2radian(deg->z);
	}
	else
	{
		model->dof.rot_rad.x += degree2radian(deg->x);
		model->dof.rot_rad.y += degree2radian(deg->y);
		model->dof.rot_rad.z += degree2radian(deg->z);
	}
	free_whatever(model, "p", deg);
	create_next_img(model);
}

void	scale_mod(t_model *model, t_bool ovr, double zoom, double z_factor)
{
    dbg_printf(model,start_block,"scale_mod");
	if (ovr)
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
    dbg_printf(model,end_block,"scale_mod");
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
			rot_mod(model, ft_false, new_point(pnt_dim_3, 1, 0, 0));
		else if (random_axis == 2)
			rot_mod(model, ft_false, new_point(pnt_dim_3, 0, 1, 0));
		else if (random_axis == 3)
			rot_mod(model, ft_false, new_point(pnt_dim_3, 0, 0, 1));
	}
	else
		sleep(1);
	return (0);
}

void	auto_zoom(t_model *model, t_bool zoom_in)
{
	double	zoom_end;
	double	increment;
	int		frames;
	int		i;
	int		sign;

	frames = 50;
	if (zoom_in)
	{
		printf("in\n");
		sign = 1;
		zoom_end = model->dof.zoom;
		increment = zoom_end / frames;
		scale_mod(model, ft_true, AUTO_ZOOM_INI_LEVEL, model->dof.z_factor);
	}
	else
	{
		printf("out\n");
		sign = -1;
		zoom_end = AUTO_ZOOM_INI_LEVEL;
		increment = model->dof.zoom / frames;
	}
    printf("increment: %lf\n",increment);
	i = 0;
	sleep(1);
	while ((sign == 1 && (model->dof.zoom < zoom_end)) || (sign == -1
		&& (model->dof.zoom > zoom_end)))
	{
		printf("zoooooom direction: %d\n",sign);
		if (i < 10)
			scale_mod(model, ft_false, (sign * 0.5 * increment), 0);
		else if (i < 20)
			scale_mod(model, ft_false, (sign * increment), 0);
		else if (i < 30)
			scale_mod(model, ft_false, (sign * 2 * increment), 0);
		else if (i < 40)
			scale_mod(model, ft_false, (sign * increment), 0);
		else
		{
			if (model->dof.zoom + (sign * increment * 0.5) <= zoom_end)
				scale_mod(model, ft_false, (sign * increment * 0.5), 0);
			else
				scale_mod(model, ft_true, zoom_end, model->dof.z_factor);
		}
		i++;
	}
	sleep(1);
}
