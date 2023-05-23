/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:06:51 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 23:38:10 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double	degree2radian(int degree)
{
	double	radian;

	radian = degree * (M_PI / 180.0);
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
	return (NULL);
}

void	*free_2_ptr(void *ptr1, void *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	return (NULL);
}

void	*free_3_ptr(void *ptr1, void *ptr2, void *ptr3)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	return (NULL);
}
