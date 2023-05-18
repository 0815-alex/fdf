/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/18 18:55:18 by astein           ###   ########.fr       */
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
	t_node	*new_node;

	ft_printf("Parsing the line %i\n", y);
	arr = ft_split(line, ' ');
	i = 0;
	x = 0;
	while (arr[i])
	{
		new_node = malloc(sizeof(t_node));
		new_node->x = x;
		new_node->y = y;
		new_node->z = ft_atoi(arr[i]);
		ft_printf(" node created:");
		print_node(new_node);
		node_add_back(net, new_node);
		x++;
		i++;
	}
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
	cur_row = 0;
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
