/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:10:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 22:47:45 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_bool	check_translate(int key, t_model *model)
{
	t_bool	check;
	int		offset;

	offset = 5;
	check = ft_true;
	if (key == K_ARROW_UP)
		translate_model(model, ft_false, new_point(pnt_dim_2, 0, -offset, 0));
	else if (key == K_ARROW_DOWN)
		translate_model(model, ft_false, new_point(pnt_dim_2, 0, offset, 0));
	else if (key == K_ARROW_LEFT)
		translate_model(model, ft_false, new_point(pnt_dim_2, -offset, 0, 0));
	else if (key == K_ARROW_RIGHT)
		translate_model(model, ft_false, new_point(pnt_dim_2, offset, 0, 0));
	else
		check = ft_false;
	return (check);
}

static t_bool	check_rotate(int key, t_model *model)
{
	t_bool	check;
	int		degree;

	check = ft_true;
	degree = 10;
	if (key == 'd')
		rotate_model(model, ft_false, new_point(pnt_dim_3, 0, degree, 0));
	else if (key == 'a')
		rotate_model(model, ft_false, new_point(pnt_dim_3, 0, -degree, 0));
	else if (key == 'w')
		rotate_model(model, ft_false, new_point(pnt_dim_3, degree, 0, 0));
	else if (key == 's')
		rotate_model(model, ft_false, new_point(pnt_dim_3, -degree, 0, 0));
	else if (key == 'q')
		rotate_model(model, ft_false, new_point(pnt_dim_3, 0, 0, degree));
	else if (key == 'e')
		rotate_model(model, ft_false, new_point(pnt_dim_3, 0, 0, -degree));
	else if (key == 'r')
		model->dof.auto_rotate = !model->dof.auto_rotate;
	else
		check = ft_false;
	return (check);
}

static t_bool	check_zoom(int key, t_model *model)
{
	t_bool	check;

	check = ft_true;
	if (key == '1')
		scale_model(model, ft_false, -5, 0);
	else if (key == '2')
		scale_model(model, ft_false, 5, 0);
	else if (key == '3')
		scale_model(model, ft_false, 0, -1);
	else if (key == '4')
		scale_model(model, ft_false, 0, 1);
	else
		check = ft_false;
	return (check);
}

static t_bool	check_presets(int key, t_model *model)
{
	t_bool	check;

	check = ft_true;
	if (key == 't')
		rotate_model(model, ft_true, new_point(pnt_dim_3, 0, 0, 0));
	else if (key == 'f')
		rotate_model(model, ft_true, new_point(pnt_dim_3, 90, 0, 0));
	else if (key == 'b')
		rotate_model(model, ft_true, new_point(pnt_dim_3, 180, 00, 0));
	else if (key == 's')
		rotate_model(model, ft_true, new_point(pnt_dim_3, 90, 90, 0));
	else if (key == 'p')
		rotate_model(model, ft_true, new_point(pnt_dim_3, 45, 45, 0));
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
