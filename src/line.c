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

static void	ini_line(t_point_2d **pnts,
	t_col_point_2d *pnt_a, t_col_point_2d *pnt_b, t_clr **clr_step)
{
	double	hypotenuse;

	pnts[0] = new_point(pnt_dim_2, pnt_a->x, pnt_a->y, 0);
	pnts[1] = new_point(pnt_dim_2, abs(pnt_b->x - pnt_a->x), -abs(pnt_b->y
				- pnt_a->y), 0);
	pnts[2] = malloc(sizeof(t_point_2d));
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
 * @brief 
 * 
 * 				In points I have
 * 					0 = current point
 * 					1 = delta between points
 * 					2 = sign of increment i x or y
 * 
 * @param mod 
 * @param pnt_a 
 * @param pnt_b 
 */
void	draw_line(t_model *mod, t_col_point_2d *pnt_a, t_col_point_2d *pnt_b)
{
	t_point_2d	*calc_pnts[3];
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
