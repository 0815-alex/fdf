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

/**
 * @brief	mallocs a new 't_node' element and returns it. initializing the
 * 			coordinates via the parameter 'pnt' and initializing everything
 * 			else to NULL
 * 
 * @param	pnt		coordinates of the new node
 * @return	t_node*		new malloced 't_node' instance
 */
t_node	*new_node(t_pnt_3d *pnt)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->pnt = pnt;
	new_node->clr.red = 255;
	new_node->clr.green = 255;
	new_node->clr.blue = 255;
	new_node->next = NULL;
	new_node->west = NULL;
	new_node->north = NULL;
	return (new_node);
}

/**
 * @brief	is used to print details about the node.
 * 			atm it only prints its coordinates using 'print_pnt_3d'
 * 
 * @param	node	node to print
 */
void	print_node(t_node *node)
{
	if (node == NULL)
		dbg_printf(no_block, "(no node)");
	else
	{
		print_pnt_3d(node->pnt);
	}
}

/**
 * @brief	only called by 'nodes2line' in the line drawing process.
 * 			this is where the math magic happens!
 * 
 *		1. the coordinates are translated by the mid of the model and
		2. multiplied by the zom factors 'mod->dof.zoom' and 'mod->dof.z_factor'
 * 			(thats why the rotation will happen around the mid of he model)
 * 		3. then the x and y coordinates are calculated using 
 * 			"rotation matrix"(https://en.wikipedia.org/wiki/Rotation_matrix)
 * 			because the x, y and z rotation influences each other all have to be
 * 			calculated in one step
 * 		4. the translation of 1. will be undone and the real translation
 * 			'mod->dof.trans' will be performed'
 * 		5. the color of the pnt will be set to the color of the node
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 * @param	node 	to be converted
 * @param	pnt	result of the node to pnt conversion
 */
void	node2point(t_model *mod, t_node *node, t_pnt_2d_clr *pnt)
{
	double	x;
	double	y;
	double	z;

	if (!node || !pnt)
		dbg_printf(err_block, "no node or point exists");
	x = (node->pnt->x - mod->center_pnt.x) * mod->dof.zoom;
	y = (node->pnt->y - mod->center_pnt.y) * mod->dof.zoom;
	z = (node->pnt->z - mod->center_pnt.z) * mod->dof.z_factor
		* mod->dof.zoom;
	pnt->x = x * cos(mod->dof.rot_rad.y) * cos(mod->dof.rot_rad.z) + y
		* (cos(mod->dof.rot_rad.z) * sin(mod->dof.rot_rad.x)
			* sin(mod->dof.rot_rad.y) - cos(mod->dof.rot_rad.x)
			* sin(mod->dof.rot_rad.z)) + z * (cos(mod->dof.rot_rad.x)
			* cos(mod->dof.rot_rad.z) * sin(mod->dof.rot_rad.y)
			+ sin(mod->dof.rot_rad.x) * sin(mod->dof.rot_rad.z));
	pnt->y = x * (cos(mod->dof.rot_rad.y) * sin(mod->dof.rot_rad.z)) + y
		* (cos(mod->dof.rot_rad.x) * cos(mod->dof.rot_rad.z)
			+ sin(mod->dof.rot_rad.x) * sin(mod->dof.rot_rad.y)
			* sin(mod->dof.rot_rad.z)) + z * (-cos(mod->dof.rot_rad.z)
			* sin(mod->dof.rot_rad.x) + cos(mod->dof.rot_rad.x)
			* sin(mod->dof.rot_rad.y) * sin(mod->dof.rot_rad.z));
	pnt->x += mod->center_pnt.x + mod->dof.trans.x;
	pnt->y += mod->center_pnt.y + mod->dof.trans.y;
	pnt->clr = node->clr;
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
