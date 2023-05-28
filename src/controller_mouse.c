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

int	deal_mouse(int code, t_model *mod)
{
	int	degree;

	dbg_printf(no_block, "mouse action. code: (%d)", code);
	degree = 10;
	if (code == M_SCROLL_DOWN)
		rot_mod(mod, ft_false, new_point(pnt_dim_3, -degree, 0, 0));
	return (0);
}
