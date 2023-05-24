/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/24 17:18:14 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	first split it to array
	then create 
*/
static void	str_line(char **arr, int y, t_node **prev_row, t_model *model)
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
		update_max_values(model, i + 1, y, node_new->pnt->z);
		node_new->west = node_prev;
		node_new->north = *prev_row;
		if (*prev_row)
			*prev_row = (*prev_row)->next;
		print_node(model, node_new);
		node_add_back(&model->net, node_new);
		if (i == 0)
			node_first_in_row = node_new;
		node_prev = node_new;
		i++;
	}
	free_whatever(model, "a", arr);
	*prev_row = node_first_in_row;
}

/*  check if there are args
    try open file
    read line by line and create rows and columns linked list
    return that
*/
void	load_file(int argc, char **argv, t_model *model)
{
	int		fd;
	char	*line;
	int		cur_row;
	t_node	*prev_row;

	if (argc != 2)
		dbg_printf(model, err_block, "Missing a filename as a parameter!");
	model->net = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		dbg_printf(model, err_block, "fdf file not found!");
	line = get_next_line(fd);
	cur_row = 1;
	prev_row = NULL;
	while (line)
	{
		dbg_printf(model, no_block, "read Line: %s", line);
		str_line(ft_split(line, ' '), cur_row, &prev_row, model);
		free(line);
		line = get_next_line(fd);
		cur_row++;
	}
	dbg_printf(model, no_block, "read Line: %s", line);
	free(line);
	line = NULL;
	close(fd);
}
