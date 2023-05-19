/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:10:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/19 17:45:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

int	deal_key(int key, void *param)
{
	ft_printf("Key pressed: %c (%i)\n", key, key);
	
	if (key == 'q')
		exit(0);
	// if (key == 't')
	// 	if (key == 's')
	// 		if (key == K_ARROW_DOWN)
	// 		{
	// 			// tparam->y =param->y +1;
	// 		}
	return (0);
}

int	deal_mouse(int code, void *param)
{
	ft_printf("Mouse action. code: (%i)", code);
}
