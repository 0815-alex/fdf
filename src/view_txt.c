/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_txt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2023/05/29 14:06:28 by astein           ###   ########.fr       */
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
	y = 2 * SZ;
	while (cur_line)
	{
		mlx_string_put(mod->mlx, mod->win, SZ, y, CLR_G,
			(char *)cur_line->content);
		cur_line = cur_line->next;
		y += SZ;
	}
}

static void	put_stats_frame_to_view(t_model *mod)
{
	int	x;

	x = 300 * mod->show_help + SZ;
	mlx_string_put(mod->mlx, mod->win, x, 2 * SZ, CLR_G,
		"STATS | TRAN ROT ZOOM | AUTO");
	mlx_string_put(mod->mlx, mod->win, x, 3 * SZ, CLR_G,
		"------|---------------|-----");
	mlx_string_put(mod->mlx, mod->win, x, 4 * SZ, CLR_G, "    x |");
	mlx_string_put(mod->mlx, mod->win, x, 5 * SZ, CLR_G, "    y |");
	mlx_string_put(mod->mlx, mod->win, x, 6 * SZ, CLR_G, "    z |");
	x += 132;
	mlx_string_put(mod->mlx, mod->win, x, 4 * SZ, CLR_G, "|");
	mlx_string_put(mod->mlx, mod->win, x, 5 * SZ, CLR_G, "|");
	mlx_string_put(mod->mlx, mod->win, x, 6 * SZ, CLR_G, "|");
	mlx_string_put(mod->mlx, mod->win, x + SZ, 4 * SZ, CLR_G,
		ft_btoa(mod->dof.auto_rotate, 1));
	mlx_string_put(mod->mlx, mod->win, x + SZ, 5 * SZ, CLR_G,
		ft_btoa(mod->dof.auto_color_change, 1));
}

void	put_stats_to_view(t_model *mod)
{
	char	**v;
	int		x;

	put_stats_frame_to_view(mod);
	v = malloc(sizeof(char *) * 8);
	v[0] = ft_itoa(mod->dof.trans.x);
	v[1] = ft_itoa(mod->dof.trans.y);
	v[2] = ft_itoa(radian2degree(mod->dof.rot_rad.x));
	v[3] = ft_itoa(radian2degree(mod->dof.rot_rad.y));
	v[4] = ft_itoa(radian2degree(mod->dof.rot_rad.z));
	v[5] = ft_dtoa(mod->dof.zoom, 0);
	v[6] = ft_dtoa(mod->dof.z_factor, 1);
	v[7] = NULL;
	x = 300 * mod->show_help + SZ;
	mlx_string_put(mod->mlx, mod->win, x + 3 * SZ, 4 * SZ, CLR_G, v[0]);
	mlx_string_put(mod->mlx, mod->win, x + 3 * SZ, 5 * SZ, CLR_G, v[1]);
	mlx_string_put(mod->mlx, mod->win, x + 3 * SZ, 6 * SZ, CLR_G, "-");
	mlx_string_put(mod->mlx, mod->win, x + 5 * SZ, 4 * SZ, CLR_G, v[2]);
	mlx_string_put(mod->mlx, mod->win, x + 5 * SZ, 5 * SZ, CLR_G, v[3]);
	mlx_string_put(mod->mlx, mod->win, x + 5 * SZ, 6 * SZ, CLR_G, v[4]);
	mlx_string_put(mod->mlx, mod->win, x + 7 * SZ, 4 * SZ, CLR_G, v[5]);
	mlx_string_put(mod->mlx, mod->win, x + 7 * SZ, 5 * SZ, CLR_G, v[5]);
	mlx_string_put(mod->mlx, mod->win, x + 7 * SZ, 6 * SZ, CLR_G, v[6]);
	free_whatever ("a", v);
}
