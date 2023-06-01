/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:21:49 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 20:10:23 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	deal_mouse(int btn, int x, int y, t_model *mod)
{
	(void)x;
	(void)y;
	if (btn == M_LEFT)
	{
		mod->show_help = !mod->show_help;
		update_image(mod);
	}
	else if (btn == M_RIGHT)
	{
		mod->show_stats = !mod->show_stats;
		update_image(mod);
	}
	else if (btn == M_MIDDLE)
		mod->dof.auto_zoom = 1;
	else if (btn == M_SCROLL_UP)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 5, 0, 0));
	else if (btn == M_SCROLL_DOWN)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, -5, 0, 0));
	else if (btn == M_SCROLL_LEFT)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, -5, 0));
	else if (btn == M_SCROLL_RIGHT)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, 0, 5, 0));
	return (0);
}
