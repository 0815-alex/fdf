/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 00:59:07 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_model	*new_model(int argc, char **argv)
{
	t_model	*mod;

	mod = malloc(sizeof(t_model));
	ini_debug(mod, 1);
	ini_net_details(mod);
	ini_max_values(mod);
	load_file(argc, argv, mod);
	determine_net_center(mod);
	ini_color_maps(mod);
	ini_colors(mod);
	ini_win(mod);
	ini_dof_plus(mod);
	center_model(mod);
	mod->dof.zoom = AUTO_ZOOM_INI_LEVEL;
	mod->show_help = ft_true;
	ini_img(mod);
	mlx_key_hook(mod->win, deal_key, mod);
	mlx_hook(mod->win, B_CLS_WIN, 0, close_model, mod);
	mlx_mouse_hook(mod->win, deal_mouse, mod);
	mlx_loop_hook(mod->mlx, auto_movements, mod);
	dbg_printf(mod, end_block, "new_model");
	return (mod);
}

void	shedule_close(t_model *mod)
{
	mod->dof.auto_zoom = -1;
	mod->close_pending = ft_true;
}

int	close_model(t_model *mod)
{
	dbg_printf(mod, start_block, "close_model");
	mlx_destroy_window(mod->mlx, mod->win);
	free_list(mod->net);
	free_color_maps(mod);
	free_help(mod);
	mlx_destroy_image(mod->mlx, mod->img.mlx_img);
	free_whatever(mod, "pp", mod->help, mod->color_map);
	free(mod);
	exit(0);
	return (0);
}
