/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 04:00:55 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	first split it to array
	then create 
*/
static void	str_line(char **arr, int y, t_node **prev_row, t_model *mod)
{
	int		i;
	t_node	*node_prev;
	t_node	*node_new;
	t_node	*node_first_in_row;

	node_prev = NULL;
	i = 0;
	while (arr[i])
	{
		node_new = new_node(new_point(pnt_dim_3, i + 1, y, ft_atoi(arr[i])));
		update_max_values(mod, i + 1, y, node_new->pnt->z);
		node_new->west = node_prev;
		node_new->north = *prev_row;
		if (*prev_row)
			*prev_row = (*prev_row)->next;
		print_node(node_new);
		node_add_back(&mod->net, node_new);
		if (i == 0)
			node_first_in_row = node_new;
		node_prev = node_new;
		i++;
	}
	free_whatever("a", arr);
	*prev_row = node_first_in_row;
}

static int	open_or_create(char **argv)
{
	int		fd;
	char	*fn;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fn = ft_calloc((ft_strlen(argv[1]) + ft_strlen(P_CHARS) + 20), 1);
		ft_strlcat(fn, P_NAMES, ft_strlen(P_NAMES) + 1);
		ft_strlcat(fn, argv[1], ft_strlen(fn) + ft_strlen(argv[1]) + 1);
		ft_strlcat(fn, ".fdf", ft_strlen(fn) + 5);
		fd = open(fn, O_RDONLY);
		free(fn);
		if (fd == -1)
		{
			if (ft_strlen(argv[1]) + 5 >= FOPEN_MAX)
				dbg_printf(err_block, "max: %i charaters :/", FOPEN_MAX - 4);
			else
			{
				fn = create_map(argv[1]);
				fd = open(fn, O_RDONLY);
				free(fn);
			}
		}
	}
	return (fd);
}

/*  check if there are args
    try open file
    read line by line and create rows and columns linked list
    return that
*/
void	load_file(int argc, char **argv, t_model *mod)
{
	int		fd;
	char	*line;
	int		cur_row;
	t_node	*prev_row;

	if (argc != 2)
		dbg_printf(err_block, "Missing a filename as a parameter!");
	mod->net = NULL;
	fd = open_or_create(argv);
	line = get_next_line(fd);
	cur_row = 1;
	prev_row = NULL;
	while (line)
	{
		dbg_printf(no_block, "read Line: %s\n", line);
		str_line(ft_split(line, ' '), cur_row, &prev_row, mod);
		free(line);
		line = get_next_line(fd);
		cur_row++;
	}
	dbg_printf(no_block, "read Line: %s", line);
	free(line);
	line = NULL;
	close(fd);
}
