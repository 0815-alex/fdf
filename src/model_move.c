/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:22 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 22:21:56 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	trans_mod(t_model *model, t_bool ovr, t_point_2d *trans)
{
	if (ovr == ft_true)
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
	if (ovr == ft_true)
	{
		if (zoom < 1)
			dbg_printf(model, no_block, "zoom must be >= 1 | is: %i", zoom);
		else
			model->dof.zoom = zoom;
		if (z_factor < 0)
		{
			model->dof.z_factor = 0;
			dbg_printf(model, no_block, "z factor must be >= 0! | is: %i",
					zoom);
		}
		else
			model->dof.z_factor = z_factor;
	}
	else
	{
		model->dof.zoom += zoom;
		model->dof.z_factor += z_factor;
		if (model->dof.zoom < 0)
		{
			dbg_printf(model, no_block, "Zoom must be >= 0! | is: %i",
					model->dof.zoom);
			model->dof.zoom -= zoom;
		}
		if (model->dof.z_factor < 0)
		{
			dbg_printf(model, no_block, "z factor must be >= 0! | is: %i",
					zoom);
			model->dof.z_factor = 0;
		}
	}
	dbg_printf(model, no_block, "new values: zoom: %d4 | z_factor %d4",
			model->dof.zoom, model->dof.z_factor);
	create_next_img(model);
	dbg_printf(model, end_block, "scale_mod");
}

int	auto_movements(t_model *model)
{
	static double	random_value;
	static int		random_axis;
	static int		step;

	if (model->dof.auto_zoom == 1)
	{
		dbg_printf(model, no_block, "zoom in ist ongoing...");
		if (static_auto_zoom(model, ft_true) == ft_true)
			model->dof.auto_zoom = 0;
	}
	else if (model->dof.auto_zoom == -1)
	{
		dbg_printf(model, no_block, "zoom out ist ongoing...");
		if (static_auto_zoom(model, ft_false) == ft_true)
			model->dof.auto_zoom = 0;
	}
	else if (model->close_pending)
		close_model(model);
	else if (!model->dof.auto_rotate)
		sleep(1);
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
	return (0);
}

t_bool	static_auto_zoom(t_model *model, t_bool zoom_in)
{
	static double	zoom_start;
	static double	zoom_end;
	static double	increment;
	static int		cur_step;
	static int		sign;
	t_dof_plus		*cur_dof;

	// checken ob fertig mit altem zoom
	if (zoom_start == 0)
	{
		// neuen zoom initialisieren
		//      start end und increment festlegen
		if (zoom_in == ft_true)
		{
			sign = 1;
			zoom_start = model->dof.zoom;
			//aktuelle orientierung speichern
			cur_dof = malloc(sizeof(t_dof_plus));
			cpy_dof(&model->dof, cur_dof);
			center_model(model);
			zoom_end = model->dof.zoom;
			cpy_dof(cur_dof, &model->dof);
			free(cur_dof);
			printf("STARTED a new zoom in from %lf to %lf\n",model->dof.zoom,zoom_end);
		}
		else
		{
			sign = -1;
			zoom_start = model->dof.zoom;
			zoom_end = AUTO_ZOOM_INI_LEVEL;
            printf("STARTED a new zoom out from %lf to %lf\n",model->dof.zoom,zoom_end);
		}
		increment = (zoom_end - zoom_start) / AUTO_ZOOM_FRAMES;
	}
	// einen step incrementen
	printf("increment: %lf\n", increment);
	if (model->dof.zoom != zoom_end)
	{
		printf("zoom direction: %i\n", sign);
		if (cur_step < AUTO_ZOOM_FRAMES / 5)
			scale_mod(model, ft_false, (0.5 * increment), 0);
		else if (cur_step < 2 * (AUTO_ZOOM_FRAMES / 5))
			scale_mod(model, ft_false, (increment), 0);
		else if (cur_step < 3 * (AUTO_ZOOM_FRAMES / 5))
			scale_mod(model, ft_false, (2 * increment), 0);
		else if (cur_step < 4 * (AUTO_ZOOM_FRAMES / 5))
			scale_mod(model, ft_false, (increment), 0);
		else
		{
			if (sign == 1)
			{
				if (model->dof.zoom + (increment * 0.5) <= zoom_end)
					scale_mod(model, ft_false, (increment * 0.5), 0);
				else
				{
					scale_mod(model, ft_true, zoom_end, model->dof.z_factor);
					// // wenn es letzter step ist
					// //  start, end, increment, cur_step, sign nullen
					// zoom_start = 0;
					// zoom_end = 0;
					// increment = 0;
					// cur_step = 0;
					// sign = 0;
					// //zoom ist abgeschlossen
					// return (ft_true);
				}
			}
			else
			{
				if (model->dof.zoom + (increment * 0.5) >= zoom_end)
					scale_mod(model, ft_false, (increment * 0.5), 0);
				else
				{
					scale_mod(model, ft_true, zoom_end, model->dof.z_factor);
					// // wenn es letzter step ist
					// //  start, end, increment, cur_step, sign nullen
					// zoom_start = 0;
					// zoom_end = 0;
					// increment = 0;
					// cur_step = 0;
					// sign = 0;
					// //zoom ist abgeschlossen
					// return (ft_true);
				}
			}
		}
		cur_step++;
	}
	else
	{
		// wenn es letzter step ist
		//  start, end, increment, cur_step, sign nullen
		zoom_start = 0;
		zoom_end = 0;
		increment = 0;
		cur_step = 0;
		sign = 0;
		//zoom ist abgeschlossen
		return (ft_true);
	}
	//zoom ist noch nicht abgeschlossen
	return (ft_false);
}

// void	auto_zoom(t_model *model, t_bool zoom_in)
// {
// 	double	zoom_end;
// 	double	increment;
// 	int		frames;
// 	int		i;
// 	int		sign;

// 	frames = 5;
// 	if (zoom_in)
// 	{
// 		printf("in\n");
// 		sign = 1;
// 		center_model(model);
// 		zoom_end = model->dof.zoom;
// 		increment = zoom_end / frames;
// 		scale_mod(model, ft_true, AUTO_ZOOM_INI_LEVEL, 0);
// 	}
// 	else
// 	{
// 		printf("out\n");
// 		sign = -1;
// 		zoom_end = AUTO_ZOOM_INI_LEVEL;
// 		increment = model->dof.zoom / frames;
// 	}
// 	printf("increment: %lf\n", increment);
// 	i = 0;
// 	while ((sign == 1 && (model->dof.zoom < zoom_end)) || (sign == -1
// 			&& (model->dof.zoom > zoom_end)))
// 	{
// 		sleep(1);
// 		printf("zoom direction: %i\n", sign);
// 		if (i < frames / 5)
// 			scale_mod(model, ft_false, (sign * 0.5 * increment), 0);
// 		else if (i < 2 * (frames / 5))
// 			scale_mod(model, ft_false, (sign * increment), 0);
// 		else if (i < 3 * (frames / 5))
// 			scale_mod(model, ft_false, (sign * 2 * increment), 0);
// 		else if (i < 4 * (frames / 5))
// 			scale_mod(model, ft_false, (sign * increment), 0);
// 		else
// 		{
// 			if (sign == 1)
// 			{
// 				if (model->dof.zoom + (sign * increment * 0.5) <= zoom_end)
// 					scale_mod(model, ft_false, (sign * increment * 0.5), 0);
// 				else
// 					scale_mod(model, ft_true, zoom_end, model->dof.z_factor);
// 			}
// 			else
// 			{
// 				if (model->dof.zoom + (sign * increment * 0.5) >= zoom_end)
// 					scale_mod(model, ft_false, (sign * increment * 0.5), 0);
// 				else
// 					scale_mod(model, ft_true, zoom_end, model->dof.z_factor);
// 			}
// 		}
// 		i++;
// 	}
// }
