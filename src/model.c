/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 20:08:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_model	*new_model(int argc, char **argv)
{
	t_model	*model;

	model = malloc(sizeof(t_model));
	init_debug(model, 1);
	init_net_details(model);
	init_max_values(model);
	load_file(argc, argv, model);
	determine_net_center(model);
	ini_win(model);
	mlx_key_hook(model->win, deal_key, model);
	mlx_mouse_hook(model->win, deal_mouse, model);
	mlx_loop_hook(model->mlx, auto_rotate, model);
	model->x_trans = 100;
	model->y_trans = 100;
	model->x_rot_rad = degree2radian(0);
	model->y_rot_rad = degree2radian(0);
	model->z_rot_rad = degree2radian(0);
	model->zoom = 10;
	model->z_factor = 1;
	model->color = COLOR_RED;
	model->img.mlx_img = NULL;
	model->img.addr = NULL;
	center_model(model);
	print_net(model);
	create_next_img(model);
	update_image(model);
	dbg_printf(model, end_block, "new_model");
	return (model);
}

void	free_model(t_model *model)
{
	dbg_printf(model, start_block, "free_model");
	mlx_destroy_window(model->mlx, model->win);
	free_list(model->net);
	mlx_destroy_image(model->mlx, model->img.mlx_img);
	free(model->dbg);
	free(model);
	exit(0);
}
