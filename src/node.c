/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:50:54 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 19:55:19 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_node	*new_node(t_pnt_3d *point)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->pnt = point;
	new_node->clr.red = 255;
	new_node->clr.green = 255;
	new_node->clr.blue = 255;
	new_node->next = NULL;
	new_node->west = NULL;
	new_node->north = NULL;
	return (new_node);
}

//I should change it to call 3dpoint to string instead!
void	print_node(t_node *node)
{
	if (node == NULL)
		dbg_printf(no_block, "(no node)");
	else
		dbg_printf(no_block, "(%i|%i|%i)", node->pnt->x, node->pnt->y,
			node->pnt->z);
}

//I should change it to call 3dpoint to string instead!
char	*node2str(t_node *node)
{
	char	*str;

	dbg_printf(start_block, "node2str");
	if (node == NULL)
	{
		dbg_printf(end_block, "node2str");
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
		dbg_printf(end_block, "node2str");
		return (str);
	}
}

/**
 * @brief	only called by 'nodes2line' in the line drawing process. 
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 * @param node 
 * @param point 
 */
void	node2point(t_model *mod, t_node *node, t_pnt_2d_clr *point)
{
	double	x;
	double	y;
	double	z;

	if (!node || !point)
		dbg_printf(err_block, "no node or point exists");
	x = (node->pnt->x - mod->center_pnt.x) * mod->dof.zoom;
	y = (node->pnt->y - mod->center_pnt.y) * mod->dof.zoom;
	z = (node->pnt->z - mod->center_pnt.z) * mod->dof.z_factor
		* mod->dof.zoom;
	point->x = x * cos(mod->dof.rot_rad.y) * cos(mod->dof.rot_rad.z) + y
		* (cos(mod->dof.rot_rad.z) * sin(mod->dof.rot_rad.x)
			* sin(mod->dof.rot_rad.y) - cos(mod->dof.rot_rad.x)
			* sin(mod->dof.rot_rad.z)) + z * (cos(mod->dof.rot_rad.x)
			* cos(mod->dof.rot_rad.z) * sin(mod->dof.rot_rad.y)
			+ sin(mod->dof.rot_rad.x) * sin(mod->dof.rot_rad.z));
	point->y = x * (cos(mod->dof.rot_rad.y) * sin(mod->dof.rot_rad.z)) + y
		* (cos(mod->dof.rot_rad.x) * cos(mod->dof.rot_rad.z)
			+ sin(mod->dof.rot_rad.x) * sin(mod->dof.rot_rad.y)
			* sin(mod->dof.rot_rad.z)) + z * (-cos(mod->dof.rot_rad.z)
			* sin(mod->dof.rot_rad.x) + cos(mod->dof.rot_rad.x)
			* sin(mod->dof.rot_rad.y) * sin(mod->dof.rot_rad.z));
	point->x += mod->center_pnt.x + mod->dof.trans.x;
	point->y += mod->center_pnt.y + mod->dof.trans.y;
	point->clr = node->clr;
}

/**
 * @brief	only called by 'render_next_img' it prepares a line drawing between
 * 			the nodes 'n_a' and n_b'. 
 *				1. converts the nodes into 't_pnt_2d_clr' using 'node2point'
 *				2. draws the line using 'draw_line'
 *
 * @param	mod	pointer to the struct that contains all info about the model
 * @param	n_a	node representing the line START
 * @param	n_b node representing the line END
 */
void	nodes2line(t_model *mod, t_node *n_a, t_node *n_b)
{
	t_pnt_2d_clr	*p1;
	t_pnt_2d_clr	*p2;

	p1 = malloc(sizeof(t_pnt_2d_clr));
	p2 = malloc(sizeof(t_pnt_2d_clr));
	node2point(mod, n_a, p1);
	node2point(mod, n_b, p2);
	draw_line(mod, p1, p2);
	free_whatever("pp", p1, p2);
}
