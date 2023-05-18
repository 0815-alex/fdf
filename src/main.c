/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:31:40 by astein            #+#    #+#             */
/*   Updated: 2023/05/18 20:02:29 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

void	node2point(t_node *node, t_point *point)
{
	int	offset;

	offset = 20;
	point->x = node->x * 10 + offset * node->z;
	point->y = node->y * 10 + offset * node->z;
}

void	put_point(t_win *win, t_point *point, int color)
{
	mlx_pixel_put(win->mlx, win->win, point->x, point->y, color);
}

void	put_line(t_win *win, t_point *pnt_a, t_point *pnt_b, int color)
{
	t_point	*curr_point;
	t_point	*delta;
	t_point	*sign;
	int		err;
	int		e2;

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
		put_point(win, curr_point, 0x00FFFF);
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
}

void	put_net(t_win *win, t_node **net, int color)
{
	t_point	*cur_point;
	t_point	*cur_conn_point;

	cur_point = malloc(sizeof(t_point));
	cur_conn_point = malloc(sizeof(t_point));
	while (*net)
	{
		node2point(*net, cur_point);
		//draw point (unnsessarry when drawing lines)
		mlx_pixel_put(win->mlx, win->win, cur_point->x, cur_point->y, color);
		//draw line to west
		if ((*net)->west)
		{
			node2point((*net)->west, cur_conn_point);
			put_line(win, cur_point, cur_conn_point, color);
		}
		//draw line to north
		if ((*net)->north)
		{
			node2point((*net)->north, cur_conn_point);
			put_line(win, cur_point, cur_conn_point, color);
		}
		*net = (*net)->next;
	}
	// free(cur_node);
	// free(cur_point);
	// free(cur_conn_point);
}

int	deal_key(int key, void *param)
{
	ft_printf("Key pressed: %c (%i)\n", key, key);
	// ft_putstr_fd("Key pressed: ", 1);
	// ft_putchar_fd(key, 1);
	if (key == 'q')
		exit(0);
	if (key == K_ARROW_DOWN)
	{
		// tparam->y =param->y +1;
	}
	return (0);
}

void	*ini_win(int width, int heigth, char *title)
{
	t_win	*new_window;

	new_window = malloc(sizeof(t_win));
	if (!new_window)
		return (NULL);
	new_window->mlx = mlx_init();
	new_window->win = mlx_new_window(new_window->mlx, width, heigth, title);
	return (new_window);
}

int	main(int argc, char **argv)
{
	t_win	*window;
	t_point	*curr_point;
	t_point	*curr_point2;
	t_node	**net;

	// 0. create net
	*net = malloc(sizeof(t_node));
	*net = NULL;
	ft_putstr_fd("Lets go!\n\n", 1);
	// 1. load File
	load_file(argc, argv, net);
	// 2. creat Window
	window = ini_win(1000, 1000, "Hi");
	// 3. hook keys
	mlx_key_hook(window->win, deal_key, curr_point);
	// 4. draw
	put_net(window, net, 0x00FFFF);
	// curr_point = malloc(sizeof(t_point));
	// curr_point2 = malloc(sizeof(t_point));
	// curr_point->x = 10;
	// curr_point->y = 10;
	// curr_point2->x = 500;
	// curr_point2->y = 500;
	// put_point(window, curr_point, 0x00FFFF);
	// put_point(window, curr_point2, 0x00FFFF);
	// put_line(window, curr_point, curr_point2, 0x00FFFF);
	// 5. loop for ever
	mlx_loop(window->mlx);
	return (0);
}
