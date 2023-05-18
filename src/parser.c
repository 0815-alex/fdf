/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/18 20:03:42 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

void	print_node(t_node *node)
{
	if (node == NULL)
		ft_printf("(no node)");
	else
	{
		ft_printf("(%i|%i|%i)", node->x, node->y, node->z);
	}
}

/*
	first split it to array
	then create 
*/
static t_node	*str_line(char *line, int y, t_node *last_row, t_node **net)
{
	char	**arr;
	int		i;
	int		x;
	int		z;
	t_node	*last_node;
	t_node	*new_node;
	t_node	*new_last_row;

	ft_printf("Parsing the line %i\n", y);
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
		print_node(new_node);
		node_add_back(net, new_node);
		last_node = new_node;
		if (i == 0)
			new_last_row = new_node;
		x++;
		i++;
	}
	free(arr);
	return (new_last_row);
}

/*  check if there are args
    try open file
    read line by line and create rows and columns linked list
    return that
*/
void	load_file(int argc, char **argv, t_node **net)
{
	int		fd;
	char	*line;
	int		cur_row;
	t_point	*curr_point;
	t_node	*last_row;

	if (argc != 2)
	{
		ft_printf("\n\nERROR!\nMissing a filename as a parameter!\n\n");
		exit(0);
	}
	last_row = malloc(sizeof(t_node));
	last_row = NULL;
	ft_printf("Open file: %s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	cur_row = 1;
	while (line)
	{
		ft_printf("read Line: %s\n", line);
		//store it somehow
		last_row = str_line(line, cur_row, last_row, net);
		//free it
		free(line);
		//load nex one
		line = get_next_line(fd);
		cur_row++;
	}
	ft_printf("read Line: %s\n", line);
	free(line);
	close(fd);
}
