/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:10:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 13:59:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

int	deal_key(int key, void *param)
{
	// dbg_printf(model, no_block,"Key pressed: %c (%i)\n", key, key);
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
	// dbg_printf(model, no_block,"Mouse action. code: (%i)", code);
	ft_printf("Mouse action. code: (%i)", code);
}
