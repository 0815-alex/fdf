/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:21:14 by astein            #+#    #+#             */
/*   Updated: 2023/05/29 14:00:18 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_clr	*step_clr(t_clr start_clr, t_clr end_clr, double n_steps)
{
	t_clr	*step;

	step = malloc(sizeof(t_clr));
	if (fabs(n_steps) < 1)
		cpy_color(&end_clr, step);
	else
	{
		step->red = (end_clr.red - start_clr.red) / n_steps;
		step->green = (end_clr.green - start_clr.green) / n_steps;
		step->blue = (end_clr.blue - start_clr.blue) / n_steps;
	}
	return (step);
}

/**
 * @brief   copies the RGB values frome src to the ones of dest
 * 
 * @param   src     the t_clr objet to GET the colors FROM
 * @param   dest    the t_clr objet to SET the colors TO
 */
void	cpy_color(t_clr *src, t_clr *dest)
{
	dest->red = src->red;
	dest->green = src->green;
	dest->blue = src->blue;
}

t_clr	*sum_clr(t_clr *a, t_clr *b, int b_factor)
{
	t_clr	*clr;

	clr = malloc(sizeof(t_clr));
	clr->red = a->red + (b_factor * b->red);
	clr->green = a->green + (b_factor * b->green);
	clr->blue = a->blue + (b_factor * b->blue);
	return (clr);
}

int	color2int(t_model *mod, t_clr *clr)
{
	int	i_clr;

	clr->red = (int)round(clr->red);
	clr->green = (int)round(clr->green);
	clr->blue = (int)round(clr->blue);
	if (clr->red < 0)
		clr->red = 0;
	if (clr->green < 0)
		clr->green = 0;
	if (clr->blue < 0)
		clr->blue = 0;
	if (clr->red > 255)
		clr->red = 255;
	if (clr->green > 255)
		clr->green = 255;
	if (clr->blue > 255)
		clr->blue = 255;
	i_clr = mlx_get_color_value(mod->mlx,
			(((uint8_t)clr->red) << 16)
			| ((uint8_t)(clr->green) << 8)
			| (uint8_t)(clr->blue));
	return (i_clr);
}
