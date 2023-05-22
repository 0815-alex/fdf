/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/22 17:12:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_win(t_model *model)
{
	int	screen_width;
	int	screen_height;

	screen_width = 0;
	screen_height = 0;
	dbg_printf(model, start_block, "ini_win");
	model->mlx = mlx_init();
	mlx_get_screen_size(model->mlx, &screen_width, &screen_height);
	model->win_width = screen_width - 700;
	model->win_height = screen_height - 300;
	model->win = mlx_new_window(model->mlx, model->win_width, model->win_height,
			"astein | fdf");
	dbg_printf(model, end_block, "ini_win");
}

int	auto_rotate(void *void_model)
{
	t_model			*model;
	static double	randomValue;
	static int		random_axis;
	static int		step;

	model = (t_model *)void_model;
	if (model->auto_rotate)
	{
		if (random_axis == 0 || step >= 45)
		{
			randomValue = drand48();
			random_axis = 1 + round(randomValue * 2);
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
		// mlx_clear_window(model->mlx, model->win);
		display_next_image(model);
	}
	else
		sleep(1);
	dbg_printf(model, no_block, "Auto Rotate...");
	return (0);
}

void	center_model(t_model *model)
{
	int	possbile_zoom_x;
	int	possbile_zoom_y;

	//trans soll gesetzt werden
	// so dass die mitte des netz auf die mitte der fensterbreite faellt
	model->x_trans = ((model->win_width / 2) - (model->center_point.x
				* model->zoom) / model->zoom);
	model->y_trans = ((model->win_height / 2) - (model->center_point.y
				* model->zoom) / model->zoom);
	possbile_zoom_x = (model->win_width - 100) / model->net_dim.x;
	possbile_zoom_y = (model->win_height - 100) / model->net_dim.y;
	if (possbile_zoom_x > possbile_zoom_y)
		model->zoom = possbile_zoom_y;
	else
		model->zoom = possbile_zoom_x;
	//aktuelle koordinate der mitte des netz
	// model->center_point.x * model->zoom;
	// model->center_point.y * model->zoom;
	//aktuelle fenster mitte
	// model->width / 2
	// model->height / 2
	//differenz zur fenstermitte
	// (model->width / 2) - (model->center_point.x * model->zoom)
	// (model->height / 2) - (model->center_point.y * model->zoom)
	//verschieben um die differenz geteilt durch den zoom
	// ((model->width / 2) - (model->center_point.x * model->zoom))
	// / model->zoom
	// ((model->height / 2) - (model->center_point.y * model->zoom))
	// /model->zoom
}

void	display_next_image(t_model *model)
{
	create_next_img(model);
	mlx_put_image_to_window(model->mlx, model->win, model->img.mlx_img, 0, 0);
}
