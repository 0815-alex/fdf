/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:06:51 by astein            #+#    #+#             */
/*   Updated: 2023/05/24 11:38:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double	degree2radian(int degree)
{
	double	radian;

	degree = degree % 360;
	if (degree < 0)
		degree += 360;
	radian = degree * (M_PI / 180.0);
	return (radian);
}

int	radian2degree(double radian)
{
	int	degree;

	degree = (int)(radian * (180.0 / M_PI));
	return (degree);
}



//die idee ist, dass die mit in libftprintf kommt
//genau wie dbg_printf
//dbg printf muesste dann aber in der lage sein
//eine projektspezifische END function aufzurufen, die alles rueckwaerts
//freed, kein plan wie das gehen soll
// void	*check_malloc(size_t s)
// {
// 	void	*ptr;
// 	ptr = malloc (s);
// 	if (!ptr)
//         dbg_printf(err_block, "malloc failed");
// 	return(ptr);
// }

/**
 * p = pointer
 * a = array
*/