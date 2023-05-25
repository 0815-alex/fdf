/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:14 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 12:58:59 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	    ini_net_details(t_model *model)
{
	model->center_point.x = INT_MIN;
	model->center_point.y = INT_MIN;
	model->center_point.z = INT_MIN;
}

void	print_net(t_model *model)
{
	t_node	*cur_node;

	dbg_printf(model, start_block, "print_net");
	cur_node = model->net;
	while (cur_node)
	{
		print_node(model, cur_node);
		(cur_node) = (cur_node)->next;
	}
	dbg_printf(model, end_block, "print_net");
}

void	ini_max_values(t_model *model)
{
	model->net_dim.x = INT_MIN;
	model->net_dim.y = INT_MIN;
	model->z_min = INT_MAX;
	model->z_max = INT_MIN;
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
