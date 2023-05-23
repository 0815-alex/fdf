/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:50:54 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 23:47:42 by astein           ###   ########.fr       */
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
		dbg_printf(model, no_block, "(%i|%i|%i)", node->pnt->x, node->pnt->y,
				node->pnt->z);
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
		str = ft_strjoin("(", ft_itoa(node->pnt->x));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(node->pnt->y));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(node->pnt->z));
		str = ft_strjoin(str, ")");
		dbg_printf(model, end_block, "node2str");
		return (str);
	}
}

void	node2point(t_model *model, t_node *node, t_point_2d *point)
{
	double	x;
	double	y;
	double	z;

	if (!node)
		dbg_printf(model, error_block, "no node exists");
	if (!point)
		dbg_printf(model, error_block, "no memmory for point exists");
	x = (node->pnt->x - model->center_point.x) * model->dof.zoom;
	y = (node->pnt->y - model->center_point.y) * model->dof.zoom;
	z = (node->pnt->z - model->center_point.z) * model->dof.z_factor;
	point->x = x * cos(model->dof.y_rot_rad) * cos(model->dof.z_rot_rad) + y
		* (cos(model->dof.z_rot_rad) * sin(model->dof.x_rot_rad)
			* sin(model->dof.y_rot_rad) - cos(model->dof.x_rot_rad)
			* sin(model->dof.z_rot_rad)) + z * (cos(model->dof.x_rot_rad)
			* cos(model->dof.z_rot_rad) * sin(model->dof.y_rot_rad)
			+ sin(model->dof.x_rot_rad) * sin(model->dof.z_rot_rad));
	point->y = x * (cos(model->dof.y_rot_rad) * sin(model->dof.z_rot_rad)) + y
		* (cos(model->dof.x_rot_rad) * cos(model->dof.z_rot_rad)
			+ sin(model->dof.x_rot_rad) * sin(model->dof.y_rot_rad)
			* sin(model->dof.z_rot_rad)) + z * (-cos(model->dof.z_rot_rad)
			* sin(model->dof.x_rot_rad) + cos(model->dof.x_rot_rad)
			* sin(model->dof.y_rot_rad) * sin(model->dof.z_rot_rad));
	point->x += model->center_point.x + model->dof.x_trans;
	point->y += model->center_point.y + model->dof.y_trans;
	update_max_values(model, x, y, 0);
}
