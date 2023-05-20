/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:10:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 17:28:22 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	deal_key(int key, t_model *model)
{
	// dbg_printf(model, no_block,"Key pressed: %c (%i)\n", key, key);
	ft_printf("Key pressed: %c (%i)\n", key, key);
	ft_printf("%i", model->height);
	if (key == 'q')
		exit(0);
	if (key == 't')
	{
		model->x_rotate_radian = degree2radian(0);
		model->y_rotate_radian = degree2radian(0);
	}
	else if (key == 'f')
	{
		model->x_rotate_radian = degree2radian(0);
		model->y_rotate_radian = degree2radian(90);
	}
	else if (key == 'b')
	{
		model->x_rotate_radian = degree2radian(0);
		model->y_rotate_radian = degree2radian(180);
	}
	else if (key == 's')
	{
		model->x_rotate_radian = degree2radian(90);
		model->y_rotate_radian = degree2radian(0);
	}
	else if (key == 'p')
	{
		model->x_rotate_radian = degree2radian(45);
		model->y_rotate_radian = degree2radian(45);
	}
	else if (key == '1')
		model->zoom -= 5;
	else if (key == '2')
		model->zoom += 5;
	else if (key == '3')
		model->z_factor -= 0.1;
	else if (key == '4')
		model->z_factor += 0.1;
	else if (key == K_ARROW_UP)
		model->y_translate -= 5;
	else if (key == K_ARROW_DOWN)
		model->y_translate += 5;
	else if (key == K_ARROW_LEFT)
		model->x_translate -= 5;
	else if (key == K_ARROW_RIGHT)
		model->x_translate += 5;
	mlx_clear_window(model->mlx, model->win);
	draw_net(model);
	return (0);
}

int	deal_mouse(int code, t_model *model)
{
	// dbg_printf(model, no_block,"Mouse action. code: (%i)", code);
	ft_printf("Mouse action. code: (%i)", code);
}
