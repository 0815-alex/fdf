/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 21:34:16 by astein           ###   ########.fr       */
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
	// model->win_width = screen_width - 10;
	// model->win_height = screen_height - 80;
	model->win_width = screen_width - 650;
	model->win_height = screen_height - 300;
	model->win = mlx_new_window(model->mlx, model->win_width, model->win_height,
			"astein | fdf");
	model->close_pending = ft_false;
	dbg_printf(model, end_block, "ini_win");
}

/*
trans soll gesetzt werden
so dass die mitte des netz auf die mitte der fensterbreite faellt

aktuelle koordinate der mitte des netz
model->center_point.x * model->dof.zoom;
model->center_point.y * model->dof.zoom;
aktuelle fenster mitte
model->width / 2
model->height / 2
differenz zur fenstermitte
(model->width / 2) - (model->center_point.x * model->dof.zoom)
(model->height / 2) - (model->center_point.y * model->dof.zoom)
verschieben um die differenz geteilt durch den zoom
((model->width / 2) - (model->center_point.x * model->dof.zoom))
/ model->dof.zoom
((model->height / 2) - (model->center_point.y * model->dof.zoom))
/model->dof.zoom
*/
void	center_model(t_model *model)
{
	int	smaller_win_size;
	int	possbile_zoom_x;
	int	possbile_zoom_y;

	model->dof.trans.x = ((model->win_width / 2) - (model->center_point.x
				* model->dof.zoom) / model->dof.zoom);
	model->dof.trans.y = ((model->win_height / 2) - (model->center_point.y
				* model->dof.zoom) / model->dof.zoom);
	smaller_win_size = model->win_width;
	if ((model->win_height) < smaller_win_size)
		smaller_win_size = model->win_height;
	possbile_zoom_x = (smaller_win_size - 100) / model->net_dim.x;
	possbile_zoom_y = (smaller_win_size - 100) / model->net_dim.y;
	if (possbile_zoom_x > possbile_zoom_y)
		model->dof.zoom = possbile_zoom_y;
	else
		model->dof.zoom = possbile_zoom_x;
	if (model->z_max - model->z_min == 0)
		dbg_printf(model, err_block, "model is only 2d!");
	model->dof.z_factor = (double)2 / (model->z_max - model->z_min);
}

void	update_image(t_model *model)
{
	char	*zoom;
	char	*rot_x;

	mlx_put_image_to_window(model->mlx, model->win, model->img.mlx_img, 0, 0);
	zoom = ft_itoa(model->dof.zoom);
	rot_x = ft_itoa(model->dof.rot_rad.x);
	// mlx_string_put(model->mlx, model->win, 100, 100, COLOR_GREEN, zoom);
	// mlx_string_put(model->mlx, model->win, 300, 100, COLOR_GREEN, rot_x);
	free_whatever(model, "pp", zoom, rot_x);
}
