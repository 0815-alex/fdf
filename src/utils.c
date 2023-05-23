/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:06:51 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 19:26:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double	degree2radian(int degree)
{
	double	radian;

	radian = degree * M_PI / 180.0;
	return (radian);
}

int	radian2degree2(double radian)
{
	int	degree;

	degree = (int)(radian * (180.0 / M_PI));
	return (degree);
}

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	return (ptr);
}
