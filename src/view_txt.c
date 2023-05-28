/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_txt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 21:34:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_help(t_model *mod)
{
	int		fd;
	char	*cur_line;
	char	*cur_line_trimmed;
	t_list	*cur_node;

	fd = open(PATH_2_HELP, O_RDONLY);

	if (fd < 0 || fd > FOPEN_MAX)
		dbg_printf(err_block, "error opening help file: %s", PATH_2_HELP);
	mod->help = malloc(sizeof(t_list *));
	(*mod->help) = NULL;
	cur_line = get_next_line(fd);
	while (cur_line)
	{
		dbg_printf(no_block, "read help: %s", cur_line);
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

void	put_help_to_view(t_model *mod)
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

void	put_stats_to_view(t_model *mod)
{
	char	*buf;
	int 	x;

	x = 300 * mod->show_help + STR_PXL_HEIGHT;

	mlx_string_put(mod->mlx, mod->win, x, 2 * STR_PXL_HEIGHT, COLOR_GREEN,
		"STATS | TRANS ROT ZOOM  | AUTO");
	mlx_string_put(mod->mlx, mod->win, x, 3 * STR_PXL_HEIGHT, COLOR_GREEN,
		"------|------------------------------------------------");
	mlx_string_put(mod->mlx, mod->win, x, 4 * STR_PXL_HEIGHT, COLOR_GREEN,
		"    x | ");
	mlx_string_put(mod->mlx, mod->win, x, 5 * STR_PXL_HEIGHT, COLOR_GREEN,
		"    y | ");
	mlx_string_put(mod->mlx, mod->win, x, 6 * STR_PXL_HEIGHT, COLOR_GREEN,
		"    z | ");
	x += 50;
	buf = ft_itoa(mod->dof.trans.x);
	mlx_string_put(mod->mlx, mod->win, x, 4 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_itoa(mod->dof.trans.y);
	mlx_string_put(mod->mlx, mod->win, x, 5 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	mlx_string_put(mod->mlx, mod->win, x, 6 * STR_PXL_HEIGHT, COLOR_GREEN, "-");
	x += 30;
	free(buf);
	buf = ft_itoa(radian2degree(mod->dof.rot_rad.x));
	mlx_string_put(mod->mlx, mod->win, x, 4 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_itoa(radian2degree(mod->dof.rot_rad.y));
	mlx_string_put(mod->mlx, mod->win, x, 5 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_itoa(radian2degree(mod->dof.rot_rad.z));
	mlx_string_put(mod->mlx, mod->win, x, 6 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	x += 30;
	free(buf);
	buf = ft_dtoa(mod->dof.zoom, 0);
	mlx_string_put(mod->mlx, mod->win, x, 4 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	mlx_string_put(mod->mlx, mod->win, x, 5 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	free(buf);
	buf = ft_dtoa(mod->dof.z_factor, 1);
	mlx_string_put(mod->mlx, mod->win, x, 6 * STR_PXL_HEIGHT, COLOR_GREEN, buf);
	x += 30;
	mlx_string_put(mod->mlx, mod->win, x, 4 * STR_PXL_HEIGHT, COLOR_GREEN,
		"|");
	mlx_string_put(mod->mlx, mod->win, x, 5 * STR_PXL_HEIGHT, COLOR_GREEN,
		"|");
	mlx_string_put(mod->mlx, mod->win, x, 6 * STR_PXL_HEIGHT, COLOR_GREEN,
		"|");
	x += STR_PXL_HEIGHT;
	mlx_string_put(mod->mlx, mod->win, x, 4 * STR_PXL_HEIGHT, COLOR_GREEN,
		ft_btoa(mod->dof.auto_rotate, 1));
	mlx_string_put(mod->mlx, mod->win, x, 5 * STR_PXL_HEIGHT, COLOR_GREEN,
		ft_btoa(mod->dof.auto_color_change, 1));
	free(buf);
}
