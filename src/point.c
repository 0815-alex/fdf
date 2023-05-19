/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:58:19 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 00:29:18 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

void	print_point(t_model *model, t_point *point)
{
	if (point == NULL)
		dbg_printf(model, no_block, "(no point)");
	else
	{
		dbg_printf(model, no_block, "(%i|%i)", point->x, point->y);
	}
}
