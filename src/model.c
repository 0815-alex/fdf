/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 13:19:46 by astein           ###   ########.fr       */
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
	ini_dof_plus(model);
	center_model(model);
	ini_img(model);
	auto_zoom(model,ft_true);
	mlx_key_hook(model->win, deal_key, model);
	mlx_hook(model->win, B_CLS_WIN, 0, close_model, model);
	mlx_mouse_hook(model->win, deal_mouse, model);
	mlx_loop_hook(model->mlx, auto_rotate, model);
	dbg_printf(model, end_block, "new_model");
	return (model);
}

int	close_model(t_model *model)
{
	dbg_printf(model, start_block, "close_model");
    auto_zoom(model,ft_false);
	mlx_destroy_window(model->mlx, model->win);
	free_list(model->net);
    free(model->color_map);
	mlx_destroy_image(model->mlx, model->img.mlx_img);
	free(model);
	exit(0);
	return (0);
}
