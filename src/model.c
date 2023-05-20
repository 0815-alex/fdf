/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 14:47:15 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

t_model	*new_model(int argc, char **argv)
{
	t_model	*new_model;

	new_model = malloc(sizeof(t_model));
	init_debug(new_model, 1);
	// 1. load File
	load_file(argc, argv, new_model);
	// 2. create Window
	ini_win(new_model, 1800, 1000, "Hi");
	// 3. hook keys
	dbg_printf(new_model, start_block, "hooking keys and mouse to model...");
	mlx_key_hook(new_model->win, deal_key, new_model);
	mlx_mouse_hook(new_model->win, deal_mouse, new_model);
	dbg_printf(new_model, end_block, "hooking keys and mouse to model...");
	print_net(new_model);
	dbg_printf(new_model, end_block, "new_model");
	return (new_model);
}

// void	node2pointtopview(t_node *node, t_point *point)
// {
// 	int	offset;

// 	offset = 20;
// 	point->x = node->x * 10 + offset * node->z;
// 	point->y = node->y * 10 + offset * node->z;
// }

// void	node2pointsideview(t_node *node, t_point *point)
// {
// 	int	zoom;

// 	zoom = 10;
// 	point->x = node->x * 10;
// 	point->y = 500 - (node->z * zoom);
// }

// /*
//     Converts x y z into a printable x y
//     x_rotate = rotation around x axis
//     y_rotate = rotation around y axis
//     0,  0 = top view
//     90, 0 = front view
//     180, 0 = bottom view
//     270, 0 = back view (upside down?)

//     scale   =   distance between points
// */

void	node2point(t_model *model, t_node *node, t_point *point, int x_rotate,
		int y_rotate)
{
	int		zoom;
	float	x_rotate_percentage;
	int		scale;

	dbg_printf(model, start_block, "START node2point");
	if (!node)
		dbg_printf(model, error_block, "no node exists");
	if (!point)
		dbg_printf(model, error_block, "no memmory for point exists");
	scale = 40;
	zoom = 10;
	x_rotate_percentage = x_rotate / 90;
	point->x = node->x * scale;
	point->y = node->y * scale;
	dbg_printf(model, no_block, ft_strjoin(ft_strjoin(node2str(model, node),
					"-> "), point2str(model, point)));
	dbg_printf(model, end_block, "DONE node2point");
}
