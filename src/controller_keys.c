/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:10:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 00:27:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_bool	check_translate(int key, t_model *mod)
{
	t_bool	check;
	int		offset;

	offset = 5;
	check = ft_true;
	if (key == K_ARROW_UP)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, 0, -offset, 0));
	else if (key == K_ARROW_DOWN)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, 0, offset, 0));
	else if (key == K_ARROW_LEFT)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, -offset, 0, 0));
	else if (key == K_ARROW_RIGHT)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, offset, 0, 0));
	else
		check = ft_false;
	return (check);
}

static t_bool	check_rotate(int key, t_model *mod)
{
	t_bool	check;
	int		degree;

	check = ft_true;
	degree = 10;
	if (key == 'd')
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, degree, 0));
	else if (key == 'a')
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, -degree, 0));
	else if (key == 'w')
		rot_mod(mod, ft_false, new_point(pnt_dim_3, degree, 0, 0));
	else if (key == 's')
		rot_mod(mod, ft_false, new_point(pnt_dim_3, -degree, 0, 0));
	else if (key == 'q')
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, 0, degree));
	else if (key == 'e')
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, 0, -degree));
	else if (key == 'r')
		mod->dof.auto_rotate = !mod->dof.auto_rotate;
	else
		check = ft_false;
	return (check);
}

static t_bool	check_zoom(int key, t_model *mod)
{
	t_bool	check;

	check = ft_true;
	if (key == '1')
		scale_mod(mod, ft_false, -5, 0);
	else if (key == '2')
		scale_mod(mod, ft_false, 5, 0);
	else if (key == '3')
		scale_mod(mod, ft_false, 0, -0.1);
	else if (key == '4')
		scale_mod(mod, ft_false, 0, 0.1);
	else if (key == '7')
		mod->dof.auto_zoom = -1;
	else if (key == '8')
		mod->dof.auto_zoom = 1;
	else
		check = ft_false;
	return (check);
}

static t_bool	check_presets(int key, t_model *mod)
{
	t_bool	check;

	check = ft_true;
	if (key == 't')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 0, 0, 0));
	else if (key == 'f')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 90, 0, 0));
	else if (key == 'b')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 180, 00, 0));
	else if (key == 's')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 90, 90, 0));
	else if (key == 'p')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 45, 45, 0));
	else if (key == 'c')
	{
		center_model(mod);
		create_next_img(mod);
	}
	else if (key == 'm')
		next_color_map(mod);
	else if (key == '6')
		mod->dof.auto_color_change = !mod->dof.auto_color_change;
	else
		check = ft_false;
	return (check);
}

int	deal_key(int key, t_model *mod)
{
	if (key == K_ESC)
		shedule_close(mod);
	check_translate(key, mod);
	check_rotate(key, mod);
	check_zoom(key, mod);
	check_presets(key, mod);
	return (0);
}
