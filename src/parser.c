/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 19:43:08 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	first split it to array
	then create 
*/
static void	str_line(char *line, int y, t_node **last_row, t_model *model)
{
	char	**arr;
	int		i;
	int		x;
	t_node	*last_node;
	t_node	*last_row_local;
	t_node	*new_node;
	t_node	*first_node;

	first_node = NULL;
	last_row_local = *last_row;
	dbg_printf(model, start_block, "str_line");
	dbg_printf(model, no_block, "parsing the line no.: %i", y);
	last_node = NULL;
	arr = ft_split(line, ' ');
	i = 0;
	x = 1;
	while (arr[i])
	{
		new_node = malloc(sizeof(t_node));
		new_node->x = x;
		new_node->y = y;
		new_node->z = ft_atoi(arr[i]);
		update_max_values(model, x, y, new_node->z);
		new_node->next = NULL;
		new_node->west = last_node;
		new_node->north = NULL;
		if (last_row_local)
		{
			new_node->north = last_row_local;
			last_row_local = last_row_local->next;
		}
		print_node(model, new_node);
		node_add_back(&model->net, new_node);
		if (i == 0)
			first_node = new_node;
		last_node = new_node;
		x++;
		i++;
	}
	//START CHAT GBT EDIT
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	//ENDD CHAT GBT EDIT
	free(arr);
	arr = NULL;
	*last_row = first_node;
	dbg_printf(model, end_block, "str_line");
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
	t_node	*last_row;

	dbg_printf(model, start_block, "load_file");
	if (argc != 2)
		dbg_printf(model, error_block, "Missing a filename as a parameter!");
	model->net = NULL;
	dbg_printf(model, no_block, "open file: %s", argv[1]);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	cur_row = 1;
	last_row = NULL;
	while (line)
	{
		dbg_printf(model, no_block, "read Line: %s", line);
		str_line(line, cur_row, &last_row, model);
		free(line);
		line = get_next_line(fd);
		cur_row++;
	}
	dbg_printf(model, no_block, "read Line: %s", line);
	free(line);
	line = NULL;
	close(fd);
	dbg_printf(model, end_block, "load_file");
}
