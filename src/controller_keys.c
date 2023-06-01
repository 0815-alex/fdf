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

/**
 * @brief	checks if the pressed key is assigned to TRANSLATE the model
 * 
 * @param	key	the code of the pressed key
 * @param 	mod	pointer to the struct that contains all info about the model
 */
static void	check_translate(int key, t_model *mod)
{
	int		offset;

	offset = 5;
	if (key == K_ARROW_UP)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, 0, -offset, 0));
	else if (key == K_ARROW_DOWN)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, 0, offset, 0));
	else if (key == K_ARROW_LEFT)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, -offset, 0, 0));
	else if (key == K_ARROW_RIGHT)
		trans_mod(mod, ft_false, new_point(pnt_dim_2, offset, 0, 0));
	else if (key == '0')
	{
		center_model(mod);
		render_next_img(mod);
	}
}

/**
 * @brief	checks if the pressed key is assigned to ROTATE the model
 * 
 * @param key	the code of the pressed key
 * @param mod	pointer to the struct that contains all info about the model
 * @return	t_bool 
 */
static void	check_rotate(int key, t_model *mod)
{
	int		degree;

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
		mod->dof.auto_rot = !mod->dof.auto_rot;
}

/**
 * @brief	checks if the pressed key is assigned to ZOOM the model
 * 
 * @param	key	the code of the pressed key
 * @param	mod	pointer to the struct that contains all info about the model
 * @return	t_bool 
 */
static void	check_zoom(int key, t_model *mod)
{
	int		zoom;
	float	z_factor;

	zoom = 5;
	z_factor = 0.1;
	if (key == '1')
		scale_mod(mod, ft_false, -zoom, 0);
	else if (key == '2')
		scale_mod(mod, ft_false, zoom, 0);
	else if (key == '3')
		scale_mod(mod, ft_false, 0, -z_factor);
	else if (key == '4')
		scale_mod(mod, ft_false, 0, z_factor);
	else if (key == '5')
		mod->dof.auto_zoom = -1;
	else if (key == '6')
		mod->dof.auto_zoom = 1;
}

/**
 * @brief	checks if the pressed key is assigned to DISPLAY A PRESET
 * 
 * @param	key	the code of the pressed key
 * @param	mod	pointer to the struct that contains all info about the model
 * @return t_bool	true if the 
 */
static void	check_presets(int key, t_model *mod)
{
	if (key == 't')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 0, 0, 0));
	else if (key == 'f')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 90, 0, 0));
	else if (key == 'l')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 90, 90, 0));
	else if (key == 'p')
		rot_mod(mod, ft_true, new_point(pnt_dim_3, 45, 45, 0));
	else if (key == K_TAB)
		next_clr_map(mod);
	else if (key == 'c')
		mod->dof.auto_color_change = !mod->dof.auto_color_change;
}

/**
 * @brief	only called from 'mlx_key_hook' processing all keyevents using the
 * 			4 static functions:
 * 				- 'check_translate'
 * 				- 'check_rotate'
 * 				- 'check_zoom'
 * 				- 'check_presets'
 * 
 * @param	key	the code of the pressed key
 * @param	mod	pointer to the struct that contains all info about the model
 * @return	int	always 0
 */
int	deal_key(int key, t_model *mod)
{
	if (key == K_ESC)
		shedule_close(mod);
	check_translate(key, mod);
	check_rotate(key, mod);
	check_zoom(key, mod);
	check_presets(key, mod);
	if (key == K_F1)
	{
		mod->show_help = !mod->show_help;
		update_view(mod);
	}
	else if (key == K_F2)
	{
		mod->show_stats = !mod->show_stats;
		update_view(mod);
	}
	return (0);
}
