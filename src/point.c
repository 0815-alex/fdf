/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:58:19 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 23:53:32 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	print_point(t_model *model, t_point *point)
{
	if (point == NULL)
		dbg_printf(model, no_block, "(no point)");
	else
	{
		dbg_printf(model, no_block, "(%i|%i)", point->x, point->y);
	}
}

char	*point2str(t_model *model, t_point *point)
{
	char	*str;

	dbg_printf(model, start_block, "point2str");
	if (point == NULL)
	{
		dbg_printf(model, end_block, "point2str");
		return ("(no point)");
	}
	else
	{
		str = ft_strjoin("(", ft_itoa(point->x));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(point->y));
		str = ft_strjoin(str, ")");
	dbg_printf(model, end_block, "point2str");
		return (str);
	}
}
