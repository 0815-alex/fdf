/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:35 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 21:15:21 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	only called from 'new_model' inizializing all 'mod->img' values
 * 			by creating a new image
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 */
void	ini_img(t_model *mod)
{
	size_t	img_size;

	mod->img.mlx_img = mlx_new_image(mod->mlx, mod->win_width, mod->win_height);
	mod->img.addr = mlx_get_data_addr(mod->img.mlx_img, &(mod->img.bpp),
			&(mod->img.line_len), &(mod->img.endian));
	img_size = mod->win_height * mod->win_width * sizeof(mod->img.bpp);
	ft_bzero(mod->img.addr, img_size);
}

/**
 * @brief	drawing a point to the image in 'mod->img'. the cordinates and color
 * 			are set via the paramters.
 * 			first there is a check if the coordinates are within the range of 
 * 			the window using 'mod->win_width' and 'mod->win_height'
 * 
 * @param	mod		pointer to the struct that contains all info about the model
 * @param	point	a 't_pnt_2d' sruct containing the coordinates of the point
 * @param	clr		the color of the point
 */
void	img_pix_put(t_model *mod, t_pnt_2d *point, int clr)
{
	char	*pixel;
	int		i;

	if (point->x < 1 || point->x >= mod->win_width)
		; // pixel x coordinate out of window
	else if (point->y < 1 || point->y > mod->win_height)
		; // pixel y coordinate out of window
	else
	{
		i = mod->img.bpp - 8;
		pixel = mod->img.addr + (point->y * mod->img.line_len + point->x
				* (mod->img.bpp / 8));
		while (i >= 0)
		{
			if (mod->img.endian != 0)
				*pixel++ = (clr >> i) & 0xFF;
			else
				*pixel++ = (clr >> (mod->img.bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

/**
 * @brief	whenever the 'mod->dof' is changed this function must be called to
 * 			display the changes!
 * 
 * 			erases all pixels of the current img 'mod->img' using 'ft_bzero'
 * 			then looping through all nodes of the net ('mod->net') to create all
 * 			lines. therefore if a WEST and / or a NORTH connection exists the
 * 			corresponding lines(s) will be created using 'nodes2line'
 * 
 * 			after the img was generated it will be displayed via 'update_view'
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 */
void	render_next_img(t_model *mod)
{
	t_node	*cur_node;

	ft_bzero(mod->img.addr, mod->win_height * mod->win_width
		* sizeof(mod->img.bpp));
	cur_node = mod->net;
	while (cur_node)
	{
		if (cur_node->west)
			nodes2line(mod, cur_node, cur_node->west);
		if (cur_node->north)
			nodes2line(mod, cur_node, cur_node->north);
		(cur_node) = (cur_node)->next;
	}
	free_whatever("p", cur_node);
	update_view(mod);
}
