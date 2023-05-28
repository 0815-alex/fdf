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

void	ini_win(t_model *mod)
{
	int	screen_width;
	int	screen_height;

	screen_width = 0;
	screen_height = 0;
	dbg_printf(start_block, "ini_win");
	mod->mlx = mlx_init();
	mlx_get_screen_size(mod->mlx, &screen_width, &screen_height);
	mod->win_width = screen_width;
	mod->win_height = screen_height - 60;
	mod->win = mlx_new_window(mod->mlx, mod->win_width, mod->win_height,
			"astein | fdf");
	mod->close_pending = ft_false;
	ini_help(mod);
	dbg_printf(end_block, "ini_win");
}

/*
trans soll gesetzt werden
so dass die mitte des netz auf die mitte der fensterbreite faellt

aktuelle koordinate der mitte des netz
mod->center_point.x * mod->dof.zoom;
mod->center_point.y * mod->dof.zoom;
aktuelle fenster mitte
mod->width / 2
mod->height / 2
differenz zur fenstermitte
(mod->width / 2) - (mod->center_point.x * mod->dof.zoom)
(mod->height / 2) - (mod->center_point.y * mod->dof.zoom)
verschieben um die differenz geteilt durch den zoom
((mod->width / 2) - (mod->center_point.x * mod->dof.zoom))
/ mod->dof.zoom
((mod->height / 2) - (mod->center_point.y * mod->dof.zoom))
/mod->dof.zoom
*/
void	center_model(t_model *mod)
{
	int	smaller_win_size;
	int	possbile_zoom_x;
	int	possbile_zoom_y;

	mod->dof.trans.x = ((mod->win_width / 2) - (mod->center_point.x
				* mod->dof.zoom) / mod->dof.zoom);
	mod->dof.trans.y = ((mod->win_height / 2) - (mod->center_point.y
				* mod->dof.zoom) / mod->dof.zoom);
	smaller_win_size = mod->win_width;
	if ((mod->win_height) < smaller_win_size)
		smaller_win_size = mod->win_height;
	possbile_zoom_x = (smaller_win_size - 100) / mod->net_dim.x;
	possbile_zoom_y = (smaller_win_size - 100) / mod->net_dim.y;
	if (possbile_zoom_x > possbile_zoom_y)
		mod->dof.zoom = possbile_zoom_y;
	else
		mod->dof.zoom = possbile_zoom_x;
	if (mod->z_max - mod->z_min == 0)
		dbg_printf(err_block, "mod is only 2d!");
	mod->dof.z_factor = (double)2 / (mod->z_max - mod->z_min);
}

void	update_image(t_model *mod)
{
	mlx_put_image_to_window(mod->mlx, mod->win, mod->img.mlx_img, 0, 0);
	if (mod->show_help && mod->dof.auto_zoom == 0)
		put_help_to_view(mod);
	if (mod->show_stats && mod->dof.auto_zoom == 0)
		put_stats_to_view(mod);
}
