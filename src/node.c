/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:50:54 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 20:04:42 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_node	*new_node(t_point_3d *point, int color)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->pnt = point;
	new_node->color = color;
	new_node->next = NULL;
	new_node->west = NULL;
	new_node->north = NULL;
	return (new_node);
}

//I should change it to call 3dpoint to string instead!
void	print_node(t_model *model, t_node *node)
{
	if (node == NULL)
		dbg_printf(model, no_block, "(no node)");
	else
	{
		dbg_printf(model, no_block, "(%i|%i|%i)", node->x, node->y, node->z);
	}
}

//I should change it to call 3dpoint to string instead!
char	*node2str(t_model *model, t_node *node)
{
	char	*str;

	dbg_printf(model, start_block, "node2str");
	if (node == NULL)
	{
		dbg_printf(model, end_block, "node2str");
		return ("(no node)");
	}
	else
	{
		str = ft_strjoin("(", ft_itoa(node->x));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(node->y));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(node->z));
		str = ft_strjoin(str, ")");
		dbg_printf(model, end_block, "node2str");
		return (str);
	}
}

void	node2point(t_model *model, t_node *node, t_point *point)
{
	double x;
	double y;
	double z;
	int x_new;
	int y_new;
	double a;
	double b;
	double c;

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