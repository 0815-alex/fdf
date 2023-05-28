/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 21:34:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ini_help(t_model *mod);

void	ini_win(t_model *mod)
{
	int	screen_width;
	int	screen_height;

	screen_width = 0;
	screen_height = 0;
	dbg_printf(mod, start_block, "ini_win");
	mod->mlx = mlx_init();
	mlx_get_screen_size(mod->mlx, &screen_width, &screen_height);
	mod->win_width = screen_width;
	mod->win_height = screen_height - 60;
	mod->win = mlx_new_window(mod->mlx, mod->win_width, mod->win_height,
			"astein | fdf");
	mod->close_pending = ft_false;
	ini_help(mod);
	dbg_printf(mod, end_block, "ini_win");
}

static void	ini_help(t_model *mod)
{
	int		fd;
	char	*cur_line;
	char	*cur_line_trimmed;
	t_list	*cur_node;

	fd = open(PATH_2_HELP, O_RDONLY);

	if (fd < 0 || fd > FOPEN_MAX)
		dbg_printf(mod, err_block, "error opening help file: %s", PATH_2_HELP);
	mod->help = malloc(sizeof(t_list *));
	(*mod->help) = NULL;
	cur_line = get_next_line(fd);
	while (cur_line)
	{
		dbg_printf(mod, no_block, "read help: %s", cur_line);
		cur_line_trimmed = ft_strtrim(cur_line, "\n");
		free(cur_line);
		cur_node = malloc(sizeof(t_list));
		cur_node->content = (char *)cur_line_trimmed;
		cur_node->next = NULL;
		ft_lstadd_back(mod->help, cur_node);
		cur_line = get_next_line(fd);
	}
	close(fd);
}

void	free_help(t_model *mod)
{
	t_list	*cur_node;

	while (*mod->help)
	{
		cur_node = *mod->help;
		*mod->help = (*mod->help)->next;
		free(cur_node->content);
		free(cur_node);
	}
}

static void	put_help_to_view(t_model *mod)
{
	t_list	*cur_line;
	int		y;

	cur_line = *(mod->help);
	y = 2 * STR_PXL_HEIGHT;
	while (cur_line)
	{
		mlx_string_put(mod->mlx, mod->win, STR_PXL_HEIGHT, y, COLOR_GREEN,
			(char *)cur_line->content);
		cur_line = cur_line->next;
		y += STR_PXL_HEIGHT;
	}
}

static void	put_stats_to_view(t_model *mod)
{
	char	*buf;
	int 	x;

	x = 300 * mod->show_help + STR_PXL_HEIGHT;

	mlx_string_put(mod->mlx, mod->win, x, 2*STR_PXL_HEIGHT, COLOR_GREEN,
		"STATS | TRANS ROT ZOOM     | AUTO");
	mlx_string_put(mod->mlx, mod->win, x, 3*STR_PXL_HEIGHT, COLOR_GREEN,
		"------|------------------------------------------------");
	mlx_string_put(mod->mlx, mod->win, x, 4*STR_PXL_HEIGHT, COLOR_GREEN,
		"    x | ");
	mlx_string_put(mod->mlx, mod->win, x, 5*STR_PXL_HEIGHT, COLOR_GREEN,
		"    y | ");
	mlx_string_put(mod->mlx, mod->win, x, 6*STR_PXL_HEIGHT, COLOR_GREEN,
		"    z | ");
	x += 50;
	buf = ft_itoa(mod->dof.trans.x);
	mlx_string_put(mod->mlx, mod->win, x, 4*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_itoa(mod->dof.trans.y);
	mlx_string_put(mod->mlx, mod->win, x, 5*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	mlx_string_put(mod->mlx, mod->win, x, 6*STR_PXL_HEIGHT, COLOR_GREEN, "-");
	x += 30;
	free(buf);
	buf = ft_itoa(radian2degree(mod->dof.rot_rad.x));
	mlx_string_put(mod->mlx, mod->win, x, 4*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_itoa(radian2degree(mod->dof.rot_rad.y));
	mlx_string_put(mod->mlx, mod->win, x, 5*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_itoa(radian2degree(mod->dof.rot_rad.z));
	mlx_string_put(mod->mlx, mod->win, x, 6*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	x += 30;
	free(buf);
	buf = ft_dtoa(mod->dof.zoom, 2);
	mlx_string_put(mod->mlx, mod->win, x, 4*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	mlx_string_put(mod->mlx, mod->win, x, 5*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_itoa(radian2degree(mod->dof.rot_rad.z));
	mlx_string_put(mod->mlx, mod->win, x, 6*STR_PXL_HEIGHT, COLOR_GREEN, buf);
	x += 30;
	mlx_string_put(mod->mlx, mod->win, x, 4*STR_PXL_HEIGHT, COLOR_GREEN,
		"|");
	mlx_string_put(mod->mlx, mod->win, x, 5*STR_PXL_HEIGHT, COLOR_GREEN,
		"|");
	mlx_string_put(mod->mlx, mod->win, x, 6*STR_PXL_HEIGHT, COLOR_GREEN,
		"|");

	free(buf);
	// free_whatever(mod, "pp", zoom, rot_x);
}

/*
trans soll gesetzt werden
so dass die mitte des netz auf die mitte der fensterbreite faellt

aktuelle koordinate der mitte des netz
mod->center_point.x * mod->dof.zoom;
mod->center_point.y * mod->dof.zoom;
aktuelle fenster mitte
mod->width / 2
mod->height / 2
differenz zur fenstermitte
(mod->width / 2) - (mod->center_point.x * mod->dof.zoom)
(mod->height / 2) - (mod->center_point.y * mod->dof.zoom)
verschieben um die differenz geteilt durch den zoom
((mod->width / 2) - (mod->center_point.x * mod->dof.zoom))
/ mod->dof.zoom
((mod->height / 2) - (mod->center_point.y * mod->dof.zoom))
/mod->dof.zoom
*/
void	center_model(t_model *mod)
{
	int	smaller_win_size;
	int	possbile_zoom_x;
	int	possbile_zoom_y;

	mod->dof.trans.x = ((mod->win_width / 2) - (mod->center_point.x
				* mod->dof.zoom) / mod->dof.zoom);
	mod->dof.trans.y = ((mod->win_height / 2) - (mod->center_point.y
				* mod->dof.zoom) / mod->dof.zoom);
	smaller_win_size = mod->win_width;
	if ((mod->win_height) < smaller_win_size)
		smaller_win_size = mod->win_height;
	possbile_zoom_x = (smaller_win_size - 100) / mod->net_dim.x;
	possbile_zoom_y = (smaller_win_size - 100) / mod->net_dim.y;
	if (possbile_zoom_x > possbile_zoom_y)
		mod->dof.zoom = possbile_zoom_y;
	else
		mod->dof.zoom = possbile_zoom_x;
	if (mod->z_max - mod->z_min == 0)
		dbg_printf(mod, err_block, "mod is only 2d!");
	mod->dof.z_factor = (double)2 / (mod->z_max - mod->z_min);
}

void	update_image(t_model *mod)
{
	mlx_put_image_to_window(mod->mlx, mod->win, mod->img.mlx_img, 0, 0);
	if (mod->show_help && mod->dof.auto_zoom == 0)
		put_help_to_view(mod);
	if (mod->show_stats && mod->dof.auto_zoom == 0)
		put_stats_to_view(mod);
}
