/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:10:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 20:02:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_bool	check_translate(int key, t_model *model)
{
	t_bool	check;

	check = ft_true;
	if (key == K_ARROW_UP)
		model->y_trans -= 10;
	else if (key == K_ARROW_DOWN)
		model->y_trans += 10;
	else if (key == K_ARROW_LEFT)
		model->x_trans -= 10;
	else if (key == K_ARROW_RIGHT)
		model->x_trans += 10;
	else
		check = ft_false;
	return (check);
}

static t_bool	check_rotate(int key, t_model *model)
{
	t_bool	check;
	int		step_degree;

	check = ft_true;
	step_degree = 10;
	if (key == 'd')
		model->y_rot_rad += step_degree * (M_PI / 180.0);
	else if (key == 'a')
		model->y_rot_rad -= step_degree * (M_PI / 180.0);
	else if (key == 'w')
		model->x_rot_rad += step_degree * (M_PI / 180.0);
	else if (key == 's')
		model->x_rot_rad -= step_degree * (M_PI / 180.0);
	else if (key == 'q')
		model->z_rot_rad += step_degree * (M_PI / 180.0);
	else if (key == 'e')
		model->z_rot_rad -= step_degree * (M_PI / 180.0);
	else if (key == 'r')
		model->auto_rotate = !model->auto_rotate;
	else
		check = ft_false;
	return (check);
}

static t_bool	check_zoom(int key, t_model *model)
{
	t_bool	check;

	check = ft_true;
	if (key == '1')
		model->zoom -= 5;
	else if (key == '2')
		model->zoom += 5;
	else if (key == '3')
		model->z_factor -= 1;
	else if (key == '4')
		model->z_factor += 1;
	else
		check = ft_false;
	return (check);
}

static t_bool	check_presets(int key, t_model *model)
{
	t_bool	check;

	check = ft_true;
	if (key == 't')
	{
		model->x_rot_rad = degree2radian(0);
		model->y_rot_rad = degree2radian(0);
		model->z_rot_rad = degree2radian(0);
	}
	else if (key == 'f')
	{
		model->x_rot_rad = degree2radian(90);
		model->y_rot_rad = degree2radian(0);
		model->z_rot_rad = degree2radian(0);
	}
	else if (key == 'b')
	{
		model->x_rot_rad = degree2radian(-180);
		model->y_rot_rad = degree2radian(0);
		model->z_rot_rad = degree2radian(0);
	}
	else if (key == 's')
	{
		model->x_rot_rad = degree2radian(90);
		model->y_rot_rad = degree2radian(0);
		model->z_rot_rad = degree2radian(0);
	}
	else if (key == 'p')
	{
		model->x_rot_rad = degree2radian(45);
		model->y_rot_rad = degree2radian(45);
		model->z_rot_rad = degree2radian(0);
	}
	else if (key == 'c')
	{
		center_model(model);
	}
	else
		check = ft_false;
	return (check);
}

int	deal_key(int key, t_model *model)
{
	if (key == K_ESC)
		free_model(model);
	if (check_translate(key, model))
		;
	else if (check_rotate(key, model))
		;
	else if (check_zoom(key, model))
		;
	else if (check_presets(key, model))
		;
	return (0);
}
