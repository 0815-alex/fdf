/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 22:32:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_model	*new_model(int argc, char **argv)
{
	t_model	*new_model;

	new_model = malloc(sizeof(t_model));
	init_debug(new_model, 1);
	load_file(argc, argv, new_model);
	ini_win(new_model);
	dbg_printf(new_model, start_block, "hooking keys and mouse to model...");
	mlx_key_hook(new_model->win, deal_key, new_model);
	mlx_mouse_hook(new_model->win, deal_mouse, new_model);
	dbg_printf(new_model, end_block, "hooking keys and mouse to model...");
	new_model->x_trans = 500;
	new_model->y_trans = 500;
	new_model->x_rot_rad = degree2radian(45);
	new_model->y_rot_rad = degree2radian(45);
	new_model->z_rot_rad = degree2radian(0);
	new_model->zoom = 10;
	new_model->z_factor = 1;
	new_model->color = COLOR_RED;
	print_net(new_model);
	dbg_printf(new_model, end_block, "new_model");
	return (new_model);
}

void	node2point(t_model *model, t_node *node, t_point *point)
{
	int		x;
	int		y;
	int		z;
	int		x_new;
	int		y_new;
	int		z_new;
	double	a;
	double	b;
	double	c;

	dbg_printf(model, start_block, "START node2point");
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
	x *= model->zoom;
	y *= model->zoom;
	z *= model->z_factor;
	x_new = x * cos(b) * cos(c) + y * (cos(c) * sin(a) * sin(b) - cos(a)
			* sin(c)) + z * (cos(a) * cos(c) * sin(b) + sin(a) * sin(c));
	y_new = x * (cos(b) * sin(c)) + y * (cos(a) * cos(c) + sin(a) * sin(b)
			* sin(c)) + z * (-cos(c) * sin(a) + cos(a) * sin(b) * sin(c));
	z_new = -x * sin(b) + y * cos(b) * sin(a) + z * (cos(a) * cos(b));
	x_new += model->x_trans;
	y_new += model->y_trans;
	point->x = x_new;
	point->y = y_new;
	dbg_printf(model, no_block, ft_strjoin(ft_strjoin(node2str(model, node),
					"-> "), point2str(model, point)));
	dbg_printf(model, end_block, "DONE node2point");
}
