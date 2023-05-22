/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:21:49 by astein            #+#    #+#             */
/*   Updated: 2023/05/21 15:30:46 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	deal_mouse(int code, t_model *model)
{
    ft_printf("%i%i\n",code , model->win_width);
	// dbg_printf(model, no_block, "mouse action. code: ()");
    return(0);
}
