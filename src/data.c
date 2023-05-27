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

void	    ini_net_details(t_model *mod)
{
	mod->center_point.x = INT_MIN;
	mod->center_point.y = INT_MIN;
	mod->center_point.z = INT_MIN;
}

void	print_net(t_model *mod)
{
	t_node	*cur_node;

	dbg_printf(mod, start_block, "print_net");
	cur_node = mod->net;
	while (cur_node)
	{
		print_node(mod, cur_node);
		(cur_node) = (cur_node)->next;
	}
	dbg_printf(mod, end_block, "print_net");
}

void	ini_max_values(t_model *mod)
{
	mod->net_dim.x = INT_MIN;
	mod->net_dim.y = INT_MIN;
	mod->z_min = INT_MAX;
	mod->z_max = INT_MIN;
}

void	update_max_values(t_model *mod, int x, int y, int z)
{
	if (mod->net_dim.x == INT_MIN)
		mod->net_dim.x = x;
	else
	{
		if (x > mod->net_dim.x)
			mod->net_dim.x = x;
	}
	if (mod->net_dim.y == INT_MIN)
		mod->net_dim.y = y;
	else
	{
		if (y > mod->net_dim.y)
			mod->net_dim.y = y;
	}
	if (z < mod->z_min)
		mod->z_min = z;
	if (z > mod->z_max)
		mod->z_max = z;
}

void	determine_net_center(t_model *mod)
{
	dbg_printf(mod, no_block, "net dimension (%i|%i)", mod->net_dim.x,
			mod->net_dim.y);
	mod->center_point.x = ((mod->net_dim.x + 1) / 2);
	mod->center_point.y = ((mod->net_dim.y + 1) / 2);
	mod->center_point.z = ((mod->z_max - mod->z_min) / 2);
	dbg_printf(mod, no_block, "net center (%i|%i|%i)", mod->center_point.x,
			mod->center_point.y, mod->center_point.z);
}
