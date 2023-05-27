/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:58:19 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 22:31:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// static t_pnt_dim	check_dim(void *pnt)
// {
// 	t_point_2d	*new_pnt_2d;
// 	t_point_3d	*new_pnt_3d;

// 	if (sizeof(*((t_point_2d *)pnt)) == sizeof(t_point_2d))
// 	{
// 		new_pnt_2d = (t_point_2d *)pnt;
// 		return (pnt_dim_2);
// 	}
// 	else if (sizeof(*((t_point_3d *)pnt)) == sizeof(t_point_3d))
// 	{
// 		new_pnt_3d = (t_point_3d *)pnt;
// 		return (pnt_dim_3);
// 	}
// 	else
// 	{
// 		return (pnt_dim_error);
// 	}
// }

void	*new_point(t_pnt_dim dim, int x, int y, int z)
{
	t_point_2d	*new_pnt_2d;
	t_point_3d	*new_pnt_3d;

	if (dim == pnt_dim_2)
	{
		new_pnt_2d = malloc(sizeof(t_point_2d));
		new_pnt_2d->x = x;
		new_pnt_2d->y = y;
		return (new_pnt_2d);
	}
	else if (dim == pnt_dim_3)
	{
		new_pnt_3d = malloc(sizeof(t_point_3d));
		new_pnt_3d->x = x;
		new_pnt_3d->y = y;
		new_pnt_3d->z = z;
		return (new_pnt_3d);
	}
	else
		return (NULL);
}

void	print_point(t_model *mod, t_point_2d*point)
{
	if (point == NULL)
		dbg_printf(mod, no_block, "(no point)");
	else
	{
		dbg_printf(mod, no_block, "(%i|%i)", point->x, point->y);
	}
}

char	*point2str(t_model *mod, t_point_2d*point)
{
	char	*str;

	dbg_printf(mod, start_block, "point2str");
	if (point == NULL)
	{
		dbg_printf(mod, end_block, "point2str");
		return ("(no point)");
	}
	else
	{
		str = ft_strjoin("(", ft_itoa(point->x));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(point->y));
		str = ft_strjoin(str, ")");
		dbg_printf(mod, end_block, "point2str");
		return (str);
	}
}
