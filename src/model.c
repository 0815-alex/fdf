/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 00:33:03 by astein           ###   ########.fr       */
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
	dbg_printf(new_model, no_block, "hooking keys and mouse to model...\n");
	mlx_key_hook(new_model->win, deal_key, new_model);
	mlx_mouse_hook(new_model->win, deal_mouse, new_model);
	dbg_printf(new_model, no_block, "hooking keys and mouse to model...done\n");
	dbg_printf(new_model, no_block, "creating a new model...done\n");
	print_net(new_model);
	dbg_printf(new_model, end_block, "DONE new_model\n");
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

	dbg_printf(model, start_block, "START node2point\n");
	if (!node)
		ft_printf("convert node->point FAIL: no node exists");
	if (!point)
		ft_printf("convert node->point FAIL: no memmory for point exists");
	scale = 40;
	zoom = 10;
	x_rotate_percentage = x_rotate / 90;
	point->x = node->x * scale;
	point->y = node->y * scale;
	ft_printf("converted node->point ");
	print_node(model, node);
	ft_printf(" -> ");
	print_point(model, point);
	ft_printf("\n");
	dbg_printf(model, end_block, "DONE node2point\n");
}
