/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 14:08:49 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

/*
	first split it to array
	then create 
*/
static t_node	*str_line(char *line, int y, t_node *last_row, t_model *model)
{
	char	**arr;
	int		i;
	int		x;
	int		z;
	t_node	*last_node;
	t_node	*new_node;
	t_node	*new_last_row;

	dbg_printf(model, start_block, "str_line");
	dbg_printf(model, no_block, "parsing the line no.: %i", y);
	last_node = malloc(sizeof(t_node));
	last_node = NULL;
	new_last_row = malloc(sizeof(t_node));
	new_last_row = NULL;
	arr = ft_split(line, ' ');
	i = 0;
	x = 1;
	while (arr[i])
	{
		new_node = malloc(sizeof(t_node));
		new_node->x = x;
		new_node->y = y;
		new_node->z = ft_atoi(arr[i]);
		new_node->next = NULL;
		new_node->west = last_node;
		if (last_row)
		{
			new_node->north = last_row;
			last_row = last_row->next;
		}
		print_node(model, new_node);
		node_add_back(&model->net, new_node);
		last_node = new_node;
		if (i == 0)
			new_last_row = new_node;
		x++;
		i++;
	}
	free(arr);
	dbg_printf(model, end_block, "str_line");
	return (new_last_row);
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
	t_point	*curr_point;
	t_node	*last_row;

	dbg_printf(model, start_block, "load_file");
	if (argc != 2)
	
		dbg_printf(model, error_block, "Missing a filename as a parameter!");
	
	last_row = malloc(sizeof(t_node));
	last_row = NULL;
	dbg_printf(model, no_block, "open file: %s", argv[1]);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	cur_row = 1;
	while (line)
	{
		dbg_printf(model, no_block, "read Line: %s", line);
		//store it somehow
		last_row = str_line(line, cur_row, last_row, model);
		//free it
		free(line);
		//load nex one
		line = get_next_line(fd);
		cur_row++;
	}
	dbg_printf(model, no_block, "read Line: %s", line);
	free(line);
	close(fd);
	dbg_printf(model, end_block, "load_file");
}
