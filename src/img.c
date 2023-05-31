/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/29 13:58:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_img(t_model *mod)
{
	size_t	img_size;

	mod->img.mlx_img = mlx_new_image(mod->mlx, mod->win_width, mod->win_height);
	mod->img.addr = mlx_get_data_addr(mod->img.mlx_img, &(mod->img.bpp),
			&(mod->img.line_len), &(mod->img.endian));
	img_size = mod->win_height * mod->win_width * sizeof(mod->img.bpp);
	ft_bzero(mod->img.addr, img_size);
}

void	img_pix_put(t_model *mod, t_point_2d *point, int clr)
{
	char	*pixel;
	int		i;

	if (point->x < 1 || point->x >= mod->win_width)
		dbg_printf(no_block, "pixel x coordinate out of window");
	else if (point->y < 1 || point->y > mod->win_height)
		dbg_printf(no_block, "pixel y coordinate out of window");
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

void	create_next_img(t_model *mod)
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
	update_image(mod);
}
