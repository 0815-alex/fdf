/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_txt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:08:26 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 21:22:27 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	only called from 'new_model' inizializing all helpscreen message
 * 
 * 			it opens the file 'P_HELP' (defined in fdf.h) and reads it line by
 * 			line with 'get_next_line'. each line will be stored in a malloced
 * 			't_list' instance and added to a linked list stored in 'mod->help'
 * 	
 * @param	mod	pointer to the struct that contains all info about the model
 */
void	ini_help(t_model *mod)
{
	int		fd;
	char	*cur_line;
	char	*cur_line_trimmed;
	t_list	*cur_node;

	fd = open(P_HELP, O_RDONLY);
	if (fd < 0 || fd > FOPEN_MAX)
		err_exit("error: ini_help: open help file");
	mod->help = malloc(sizeof(t_list *));
	(*mod->help) = NULL;
	cur_line = gnl(fd);
	while (cur_line)
	{
		cur_line_trimmed = ft_strtrim(cur_line, "\n");
		free(cur_line);
		cur_node = malloc(sizeof(t_list));
		cur_node->content = (char *)cur_line_trimmed;
		cur_node->next = NULL;
		ft_lstadd_back(mod->help, cur_node);
		cur_line = gnl(fd);
	}
	close(fd);
}

/**
 * @brief	loops through the linked list 'mod->help' and prints each line to
 * 			the window using 'mlx_string_put'
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 */
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

/**
 * @brief	see 'put_stats_to_view'
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 */
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
		ft_btoa(mod->dof.auto_rot, 1));
	mlx_string_put(mod->mlx, mod->win, x + SZ, 5 * SZ, CLR_G,
		ft_btoa(mod->dof.auto_color_change, 1));
}

/**
 * @brief	to print all stats to the screen i use those two functions
 * 				'put_stats_to_view'			-> for the values
 * 				'put_stats_frame_to_view'	-> for the layout symbols
 * 
 * 			the values are converted into char* via 'ft_itoa' or 'ft_dtoa',
 * 			stored in the array 'v', printed to screen with 'mlx_string_put'
 * 			and then freed with 'free_whatever'
 * 
 * @param	mod	pointer to the struct that contains all info about the model
 */
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
	free_whatever ("m", v);
}
