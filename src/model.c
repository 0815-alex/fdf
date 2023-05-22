/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/22 16:20:43 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_model	*new_model(int argc, char **argv)
{
	t_model	*model;

	model = malloc(sizeof(t_model));
	init_debug(model, 1);
	init_net_details(model);
	load_file(argc, argv, model);
	determine_net_center(model);
	ini_win(model);
	dbg_printf(model, start_block, "hooking keys and mouse to model...");
	mlx_key_hook(model->win, deal_key, model);
	mlx_mouse_hook(model->win, deal_mouse, model);
	mlx_loop_hook(model->mlx, auto_rotate, model);
	dbg_printf(model, end_block, "hooking keys and mouse to model...");
	model->x_trans = 100;
	model->y_trans = 100;
	model->x_rot_rad = degree2radian(0);
	model->y_rot_rad = degree2radian(0);
	model->z_rot_rad = degree2radian(0);
	model->zoom = 10;
	model->z_factor = 1;
	model->color = COLOR_GREEN;
	model->img.mlx_img = NULL;
	model->img.addr = NULL;
	center_model(model);
	print_net(model);
	display_next_image(model);
	dbg_printf(model, end_block, "new_model");
	return (model);
}

void	init_net_details(t_model *model)
{
	model->net_dim.x = INT_MIN;
	model->net_dim.y = INT_MIN;
	model->z_min = INT_MAX;
	model->z_max = INT_MIN;
	model->center_point.x = INT_MIN;
	model->center_point.y = INT_MIN;
	model->center_point.z = INT_MIN;
	model->auto_rotate = ft_false;
}

void	update_max_values(t_model *model, int x, int y, int z)
{
	if (model->net_dim.x == INT_MIN)
		model->net_dim.x = x;
	else
	{
		if (x > model->net_dim.x)
			model->net_dim.x = x;
	}
	if (model->net_dim.y == INT_MIN)
		model->net_dim.y = y;
	else
	{
		if (y > model->net_dim.y)
			model->net_dim.y = y;
	}
	if (z < model->z_min)
		model->z_min = z;
	if (z > model->z_max)
		model->z_max = z;
}

void	determine_net_center(t_model *model)
{
	dbg_printf(model, no_block, "net dimension (%i|%i)", model->net_dim.x,
			model->net_dim.y);
	model->center_point.x = ((model->net_dim.x + 1) / 2);
	model->center_point.y = ((model->net_dim.y + 1) / 2);
	model->center_point.z = ((model->z_max - model->z_min) / 2);
	dbg_printf(model, no_block, "net center (%i|%i|%i)", model->center_point.x,
			model->center_point.y, model->center_point.z);
}

void	node2point(t_model *model, t_node *node, t_point *point)
{
	double	x;
	double	y;
	double	z;
	int		x_new;
	int		y_new;
	double	a;
	double	b;
	double	c;

	// dbg_printf(model, start_block, "START node2point");
	if (!node)
		dbg_printf(model, error_block, "no node exists");
	if (!point)
		dbg_printf(model, error_block, "no memmory for point exists");
	x = node->x;
	y = node->y;
	z = node->z;
	a = model->x_rot_rad;
	b = model->y_rot_rad;
	c = model->z_rot_rad;
	x -= model->center_point.x;
	y -= model->center_point.y;
	z -= model->center_point.z;
	x *= model->zoom;
	y *= model->zoom;
	z *= model->z_factor;
	x_new = x * cos(b) * cos(c) + y * (cos(c) * sin(a) * sin(b) - cos(a)
			* sin(c)) + z * (cos(a) * cos(c) * sin(b) + sin(a) * sin(c));
	y_new = x * (cos(b) * sin(c)) + y * (cos(a) * cos(c) + sin(a) * sin(b)
			* sin(c)) + z * (-cos(c) * sin(a) + cos(a) * sin(b) * sin(c));
	// z_new = -x * sin(b) + y * cos(b) * sin(a) + z * (cos(a) * cos(b));
	x_new += (model->center_point.x);
	y_new += (model->center_point.y);
	y_new += model->y_trans;
	x_new += model->x_trans;
	point->x = x_new;
	point->y = y_new;
	update_max_values(model, x, y, 0);
	// dbg_printf(model, no_block, ft_strjoin(ft_strjoin(node2str(model, node),
	// 				"-> "), point2str(model, point)));
	// dbg_printf(model, end_block, "DONE node2point");
}

void	free_model(t_model *model)
{
	dbg_printf(model, start_block, "free_model");
	mlx_destroy_window(model->mlx, model->win);
	free(model->dbg);
	free_list(model->net);
	free(model->img.mlx_img);
	free(model);
}
