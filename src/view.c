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

/**
 * @brief	only called from 'new_model' inizializing all window related values
 * 			'mod->mlx'				(via 'mlx_init')
 * 			'mod->win'				(via 'mlx_new_window')
 * 			'mod->win_width'		(via 'mlx_get_screen_size')	
 * 			'mod->win_height'		(via 'mlx_get_screen_size')
 * 			'mod->close_pending'	-> false
 * 
 * @param	mod	pointer to the struct that contains all info about the model 
 */
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

/**
 * @brief	calculates and sets the maximal possible 'mod->dof.zoom' and a
 * 			matching 'mod->dof.z_factor'. then the model is translated to the
 * 			middle of the screen via 'mod->dof.trans'
 * 
 * 			NOTE: the changes won't be visible before calling 'render_next_img'
 * 					(This is due to the 'static_auto_zoom' function, which has
 * 					to calculate the middle position without displaying it)
 * 
 * @param mod pointer to the struct that contains all info about the model 
 */
void	center_model(t_model *mod)
{
	int	smaller_win_size;
	int	possbile_zoom_x;
	int	possbile_zoom_y;

	mod->dof.trans.x = ((mod->win_width / 2) - (mod->center_pnt.x
				* mod->dof.zoom) / mod->dof.zoom);
	mod->dof.trans.y = ((mod->win_height / 2) - (mod->center_pnt.y
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
		dbg_printf(err_block, "map is only 2d!");
	mod->dof.z_factor = (double)2 / (mod->z_max - mod->z_min);
}

/**
 * @brief	displays the current img via 'mlx_put_image_to_window'
 * 			in addition (if activated) the
 * 				help		(via 'put_help_to_view')
 * 				and stats	(via 'put_stats_to_view')
 * 			are generated and displayed.
 * 
 * 			NOTE: this function should only be called when 'mod->show_help' or
 * 					'mod->show_stats' changes. If changes are made to 'mod->dof'
 * 					'render_next_img' must be executed!
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 */
void	update_view(t_model *mod)
{
	mlx_put_image_to_window(mod->mlx, mod->win, mod->img.mlx_img, 0, 0);
	if (mod->show_help && mod->dof.auto_zoom == 0)
		put_help_to_view(mod);
	if (mod->show_stats && mod->dof.auto_zoom == 0)
		put_stats_to_view(mod);
}
