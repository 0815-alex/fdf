/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/29 13:58:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	gets initialized via 'ini_line'
 * 			each time it will be called it adds 'cur_step' times the 'clr_step'
 * 			to 'clr_start'
 * 			the color will then be prepared for mlx using 'color2int'
 * 
 * @param	mod			ptr to the struct that contains all info about the model
 * @param	clr_start	the RGB color which to start from
 * @param	clr_step	the RGB color incement for each step 'color2int'
 * @return	int			the calculated color formated for mlx via 'color2int'
 */
static int	calc_cur_clr(t_model *mod, t_clr *clr_start, t_clr *clr_step)
{
	static int	cur_step;
	t_clr		*clr;
	int			clr_int;

	clr_int = 0;
	if (!mod || !clr_start || !clr_step)
		cur_step = 0;
	else
	{
		clr = sum_clr(clr_start, clr_step, cur_step);
		clr_int = color2int(mod, clr);
		free(clr);
		cur_step++;
	}
	return (clr_int);
}

/**
 * @brief	part of the "bresenham's line algorithm" see function 'draw_line'
 * 
 * 			initializing the 'calc_cur_clr' function calling it with NULL
 * 
 * @param	pnts		see function 'draw_line'	
 * @param	pnt_a		point where the line should START (incl. color at START)
 * @param	pnt_b		point where the line should END	  (incl. color at END)
 * @param	clr_step	see function 'step_clr'
 */
static void	ini_line(t_pnt_2d **pnts,
	t_pnt_2d_clr *pnt_a, t_pnt_2d_clr *pnt_b, t_clr **clr_step)
{
	double	hypotenuse;

	pnts[0] = new_point(pnt_dim_2, pnt_a->x, pnt_a->y, 0);
	pnts[1] = new_point(pnt_dim_2, abs(pnt_b->x - pnt_a->x), -abs(pnt_b->y
				- pnt_a->y), 0);
	pnts[2] = malloc(sizeof(t_pnt_2d));
	if (pnt_a->x < pnt_b->x)
		pnts[2]->x = 1;
	else
		pnts[2]->x = -1;
	if (pnt_a->y < pnt_b->y)
		pnts[2]->y = 1;
	else
		pnts[2]->y = -1;
	hypotenuse = sqrt(pow((pnts[1]->x), 2) + pow((pnts[1]->y), 2));
	*clr_step = step_clr(pnt_a->clr, pnt_b->clr, hypotenuse);
	calc_cur_clr(NULL, NULL, NULL);
}

/**
 * @brief	drawing a line using the "bresenham's line algorithm"
 *	 			(https://de.wikipedia.org/wiki/Bresenham-Algorithmus)
 *
 * 			the funcion is split in 3 seperate functions:
 * 				1. initializing the loop
 * 					-> ini_line
 * 				2. the loop
 * 					-> 'draw_line'
 * 				3. the caluclatin of the color gradient 
 * 					-> 'calc_cur_clr'
 * 
 * 			the variable 'calc_pnts' contains:
 * 					0 = current point
 * 					1 = delta between points
 * 					2 = sign of increment i x or y
 *
 * @param	mod		pointer to the struct that contains all info about the model
 * @param	pnt_a	point where the line should START 	(incl. color at START)
 * @param	pnt_b	point where the line should END		(incl. color at END)
 */
void	draw_line(t_model *mod, t_pnt_2d_clr *pnt_a, t_pnt_2d_clr *pnt_b)
{
	t_pnt_2d	*calc_pnts[3];
	int			err[2];
	t_clr		*clr_step;

	ini_line(calc_pnts, pnt_a, pnt_b, &clr_step);
	err[0] = calc_pnts[1]->x + calc_pnts[1]->y;
	while (1)
	{
		img_pix_put(mod, calc_pnts[0],
			calc_cur_clr(mod, &pnt_a->clr, clr_step));
		if (calc_pnts[0]->x == pnt_b->x && calc_pnts[0]->y == pnt_b->y)
			break ;
		err[1] = 2 * err[0];
		if (err[1] > calc_pnts[1]->y)
		{
			err[0] += calc_pnts[1]->y;
			calc_pnts[0]->x += calc_pnts[2]->x;
		}
		if (err[1] < calc_pnts[1]->x)
		{
			err[0] += calc_pnts[1]->x;
			calc_pnts[0]->y += calc_pnts[2]->y;
		}
	}
	free_whatever("pppp", calc_pnts[0], calc_pnts[1], calc_pnts[2], clr_step);
}
