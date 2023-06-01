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

/**
 * @brief	conversion of an angle from degrees to radians
 * 
 * @param	degrees	angle in degrees which should be converted
 * @return	double	converted angle in radians
 */
double	degree2radian(int degrees)
{
	double	radians;

	degrees = degrees % 360;
	if (degrees < 0)
		degrees += 360;
	radians = degrees * (M_PI / 180.0);
	return (radians);
}

/**
 * @brief	conversion of an angle from radians to degrees
 * 
 * @param radians	angle in radians which should be converted
 * @return int		converted angle in degrees (rounded to int)
 */
int	radian2degree(double radians)
{
	int	degrees;

	degrees = (int)(radians * (180.0 / M_PI));
	return (degrees);
}
