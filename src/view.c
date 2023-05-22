/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/21 18:19:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	create_new_img(t_model *model)
{
	t_img	next_img;

	next_img.mlx_img = mlx_new_image(model->mlx, model->win_width,
			model->win_height);
	next_img.addr = mlx_get_data_addr(&next_img, &next_img.bpp,
			&next_img.line_len, &next_img.endian);
}

void	ini_win(t_model *model)
{
	int	screen_width;
	int	screen_height;

	screen_width = 0;
	screen_height = 0;
	dbg_printf(model, start_block, "ini_win");
	model->mlx = mlx_init();
	mlx_get_screen_size(model->mlx, &screen_width, &screen_height);
	model->win_width = screen_width - 700;
	model->win_height = screen_height - 300;
	model->win = mlx_new_window(model->mlx, model->win_width, model->win_height,
			"astein | fdf");
	dbg_printf(model, end_block, "ini_win");
}

int	auto_rotate(void *void_model)
{
	t_model			*model;
	static double	randomValue;
	static int		random_axis;
	static int		step;

	model = (t_model *)void_model;
	if (model->auto_rotate)
	{
		if (random_axis == 0 || step >= 45)
		{
			randomValue = drand48();
			random_axis = 1 + round(randomValue * 2);
		}
		if (step >= 45)
			step = 0;
		step++;
		if (random_axis == 1)
			model->x_rot_rad += (M_PI / 180.0);
		else if (random_axis == 2)
			model->y_rot_rad += (M_PI / 180.0);
		else if (random_axis == 3)
			model->z_rot_rad += (M_PI / 180.0);
		mlx_clear_window(model->mlx, model->win);
		draw_net(model);
	}
	else
		sleep(1);
	dbg_printf(model, no_block, "Auto Rotate...");
	return (0);
}

void	center_model(t_model *model)
{
	//trans soll gesetzt werden
	// so dass die mitte des netz auf die mitte der fensterbreite faellt
	model->x_trans = ((model->win_width / 2) - (model->center_point.x
				* model->zoom) / model->zoom);
	model->y_trans = ((model->win_height / 2) - (model->center_point.y
				* model->zoom) / model->zoom);
	//aktuelle koordinate der mitte des netz
	// model->center_point.x * model->zoom;
	// model->center_point.y * model->zoom;
	//aktuelle fenster mitte
	// model->width / 2
	// model->height / 2
	//differenz zur fenstermitte
	// (model->width / 2) - (model->center_point.x * model->zoom)
	// (model->height / 2) - (model->center_point.y * model->zoom)
	//verschieben um die differenz geteilt durch den zoom
	// ((model->width / 2) - (model->center_point.x * model->zoom))
	// / model->zoom
	// ((model->height / 2) - (model->center_point.y * model->zoom))
	// /model->zoom
}

void	draw_point(t_model *model, t_point *point)
{
	mlx_pixel_put(model->mlx, model->win, point->x, point->y, model->color);
}

void	draw_line(t_model *model, t_point *pnt_a, t_point *pnt_b)
{
	t_point	*curr_point;
	t_point	*delta;
	t_point	*sign;
	int		err;
	int		e2;

	// dbg_printf(model, start_block, "draw_line");
	// dbg_printf(model, no_block, ft_strjoin(ft_strjoin(point2str(model,
	// pnt_a),
	// "-> "), point2str(model, pnt_b)));
	curr_point = malloc(sizeof(t_point));
	delta = malloc(sizeof(t_point));
	sign = malloc(sizeof(t_point));
	curr_point->x = pnt_a->x;
	curr_point->y = pnt_a->y;
	delta->x = abs(pnt_b->x - curr_point->x);
	delta->y = -abs(pnt_b->y - curr_point->y);
	if (curr_point->x < pnt_b->x)
		sign->x = 1;
	else
		sign->x = -1;
	if (curr_point->y < pnt_b->y)
		sign->y = 1;
	else
		sign->y = -1;
	err = delta->x + delta->y;
	while (1)
	{
		draw_point(model, curr_point);
		if (curr_point->x == pnt_b->x && curr_point->y == pnt_b->y)
			break ;
		e2 = 2 * err;
		if (e2 > delta->y)
		{
			err += delta->y;
			curr_point->x += sign->x;
		}
		if (e2 < delta->x)
		{
			err += delta->x;
			curr_point->y += sign->y;
		}
	}
	free(curr_point);
	free(delta);
	free(sign);
	// dbg_printf(model, end_block, "draw_line");
}

void	draw_test_line(t_model *model)
{
	t_point	*point_a;
	t_point	*point_b;

	dbg_printf(model, start_block, "draw_test_line");
	point_a = malloc(sizeof(t_point));
	point_b = malloc(sizeof(t_point));
	point_a->x = 15;
	point_a->y = 15;
	point_b->x = 25;
	point_b->y = 25;
	draw_line(model, point_a, point_b);
	dbg_printf(model, end_block, "draw_test_line");
	free(point_a);
	free(point_b);
}



// void create_new_img();
// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);


void	draw_net(t_model *model)
{
	t_node	*cur_node;
	t_point	*cur_point;
	t_point	*cur_conn_point;

	dbg_printf(model, start_block, "draw_net");
	cur_node = model->net;
	cur_point = malloc(sizeof(t_point));
	cur_conn_point = malloc(sizeof(t_point));
	while (cur_node)
	{
		node2point(model, cur_node, cur_point);
		draw_point(model, cur_point);
		if (cur_node->west)
		{
			node2point(model, cur_node->west, cur_conn_point);
			draw_line(model, cur_point, cur_conn_point);
		}
		if (cur_node->north)
		{
			node2point(model, cur_node->north, cur_conn_point);
			draw_line(model, cur_point, cur_conn_point);
		}
		(cur_node) = (cur_node)->next;
	}
	free(cur_node);
	free(cur_point);
	free(cur_conn_point);
	dbg_printf(model, end_block, "draw_net");
}
