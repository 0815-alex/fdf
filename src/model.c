/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/24 17:38:21 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_model	*new_model(int argc, char **argv)
{
	t_model	*model;

	model = malloc(sizeof(t_model));
	ini_debug(model, 1);
	ini_net_details(model);
	ini_max_values(model);
	load_file(argc, argv, model);
	determine_net_center(model);
	ini_color_map(model);
	ini_colors(model);
	ini_win(model);
	mlx_key_hook(model->win, deal_key, model);
	mlx_hook(model->win, B_CLS_WIN, 0, close_model, model);
	mlx_mouse_hook(model->win, deal_mouse, model);
	ini_dof_plus(model);
	ini_img(model);
	center_model(model);
	zoom_to_start(model);
	mlx_loop_hook(model->mlx, auto_rotate, model);
	dbg_printf(model, end_block, "new_model");
	return (model);
}

int	close_model(t_model *model)
{
	dbg_printf(model, start_block, "close_model");
	mlx_destroy_window(model->mlx, model->win);
	free_list(model->net);
	mlx_destroy_image(model->mlx, model->img.mlx_img);
	free(model);
	exit(0);
	return (0);
}
