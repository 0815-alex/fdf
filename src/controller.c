/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:10:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 18:01:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_bool	check_translate(int key, t_model *model)
{
	t_bool	check;

	check = ft_false;
	if (key == K_ARROW_UP)
	{
		check = ft_true;
		model->y_trans -= 5;
	}
	else if (key == K_ARROW_DOWN)
	{
		check = ft_true;
		model->y_trans += 5;
	}
	else if (key == K_ARROW_LEFT)
	{
		check = ft_true;
		model->x_trans -= 5;
	}
	else if (key == K_ARROW_RIGHT)
	{
		check = ft_true;
		model->x_trans += 5;
	}
	return (check);
}

static t_bool	check_rotate(int key, t_model *model)
{
	t_bool	check;
	int		step_degree;

	// check = malloc(sizeof(t_bool));
	check = ft_false;
	step_degree = 5;
	if (key == 'a')
	{
		check = ft_true;
		model->x_rot_rad += step_degree * (M_PI / 180.0);
	}
	else if (key == 'd')
	{
		check = ft_true;
		model->x_rot_rad -= step_degree * (M_PI / 180.0);
	}
	else if (key == 'w')
	{
		check = ft_true;
		model->y_rot_rad += step_degree * (M_PI / 180.0);
	}
	else if (key == 's')
	{
		check = ft_true;
		model->y_rot_rad -= step_degree * (M_PI / 180.0);
	}
	return (check);
}

static t_bool	check_zoom(int key, t_model *model)
{
	t_bool	check;

	// check = malloc(sizeof(t_bool));
	check = ft_false;
	if (key == '1')
	{
		check = ft_true;
		model->zoom -= 5;
	}
	else if (key == '2')
	{
		check = ft_true;
		model->zoom += 5;
	}
	else if (key == '3')
	{
		check = ft_true;
		model->z_factor -= 0.1;
	}
	else if (key == '4')
	{
		check = ft_true;
		model->z_factor += 0.1;
	}
	return (check);
}

static t_bool	check_presets(int key, t_model *model)
{
	t_bool	check;

	// check = malloc(sizeof(t_bool));
	check = ft_false;
	if (key == 't')
	{
		check = ft_true;
		model->x_rot_rad = degree2radian(0);
		model->y_rot_rad = degree2radian(0);
	}
	else if (key == 'f')
	{
		check = ft_true;
		model->x_rot_rad = degree2radian(0);
		model->y_rot_rad = degree2radian(90);
	}
	else if (key == 'b')
	{
		check = ft_true;
		model->x_rot_rad = degree2radian(0);
		model->y_rot_rad = degree2radian(180);
	}
	else if (key == 's')
	{
		check = ft_true;
		model->x_rot_rad = degree2radian(90);
		model->y_rot_rad = degree2radian(0);
	}
	else if (key == 'p')
	{
		check = ft_true;
		model->x_rot_rad = degree2radian(45);
		model->y_rot_rad = degree2radian(45);
	}
	return (check);
}

int	deal_key(int key, t_model *model)
{
	t_bool	check;

	// check = malloc(sizeof(t_bool));
	check = ft_false;
	if (check_translate(key, model))
		check = ft_true;
	else if (check_rotate(key, model))
		check = ft_true;
	else if (check_zoom(key, model))
		check = ft_true;
	else if (check_presets(key, model))
		check = ft_true;
	if (check)
	{
		mlx_clear_window(model->mlx, model->win);
		draw_net(model);
	}
	if (key == 'q')
		exit(0);
	return (0);
}

int	deal_mouse(int code, t_model *model)
{
	// dbg_printf(model, no_block,"Mouse action. code: (%i)", code);
	ft_printf("Mouse action. code: (%i)", code);
}
