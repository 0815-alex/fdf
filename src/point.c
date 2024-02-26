/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:58:19 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 00:08:38 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	mallocs and returns a new struct of type 't_pnt_2d' or 't_pnt_3d' 
 * 			depending on the parameter 'dim'
 * 
 * 			the parameters x and y (and z for 3d point) will be used to set the
 * 			values of the new created point
 * 
 * @param dim		't_pnt_dim' representing the dimensions of the point
 * @param x			value for the points x coordinate
 * @param y			value for the points y coordinate
 * @param z			value for the points z coordinate (ignored for 2s points)
 * @return void*	the new created point
 */
void	*new_point(t_pnt_dim dim, int x, int y, int z)
{
	t_pnt_2d	*new_pnt_2d;
	t_pnt_3d	*new_pnt_3d;

	if (dim == pnt_dim_2)
	{
		new_pnt_2d = malloc(sizeof(t_pnt_2d));
		new_pnt_2d->x = x;
		new_pnt_2d->y = y;
		return (new_pnt_2d);
	}
	else if (dim == pnt_dim_3)
	{
		new_pnt_3d = malloc(sizeof(t_pnt_3d));
		new_pnt_3d->x = x;
		new_pnt_3d->y = y;
		new_pnt_3d->z = z;
		return (new_pnt_3d);
	}
	else
		return (NULL);
}

/**
 * @brief	prints the x and y coordinates of a 2d point using 'dbg_printf'
 * 			
 * 			NOTE: 	'dbg_printf' only prints if 'DEBUG' param in fdf.h is 1
 * 			
 * @param	pnt point to print
 */
void	print_pnt_2d(t_pnt_2d *pnt)
{
	if (pnt == NULL)
		dbg_printf(no_block, "(no point)");
	else
	{
		dbg_printf(0, "(%i|%i)", pnt->x, pnt->y);
	}
}

/**
 * @brief	prints the x, y and z coordinates of a 3d point using 'dbg_printf'
 * 			
 * 			NOTE: 	'dbg_printf' only prints if 'DEBUG' param in fdf.h is 1
 * 			
 * @param	pnt point to print
 * 
 * @param pnt 
 */
void	print_pnt_3d(t_pnt_3d *pnt)
{
	if (pnt == NULL)
		dbg_printf(no_block, "(no point)");
	else
	{
		dbg_printf(0, "(%i|%i|%i)", pnt->x, pnt->y, pnt->z);
	}
}
