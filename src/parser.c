/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 00:07:14 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	creates a nodes for each value of the line stored in 'arr' and
 * 			appends them to the end of the linked list 'mod->net'
 * 
 * 			to do so it:
 * 				-	converts each value str into an int via 'ft_atoi'
 * 				-	creates a new node via 'new_node' with the x,y and z values
 * 				-	updates the max values of the model via 'update_max_values'
 * 				-	creates links to the WEST and NORTH node (if exisiting)
 * 				-	add the new created node to the end of 'mod->net'
 * 				-	returns via ptr param the first node of this line 'prev_row'
 * 			
 * @param	arr			all values of a map line stored in a char* array		
 * @param	y			the index of the current line
 * @param	prev_row	a ptr to the first node of the previous row
 * @param	mod			ptr to the struct that contains all info about the model
 */
static void	line2nodes(char **arr, int y, t_node **prev_row, t_model *mod)
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

/**
 * @brief	examples:
 * 				ex1:	'str' = "./maps/astein.fdf"
 * 				ex2:	'str' = "hello world!"
 * 
 * 			checks if a file with the path and filename 'str' exists (ex1)
 * 					if not check if a file exists in the 'name' folder (ex2)
							if not create that file via 'create_map'
			now that a file exists, it is opened and the fd is returned
 * 			
 * @param	str
 * 				either	a path to a map 			e.g. './maps/astein.fdf'
 * 				or		a string to create a map	e.g. 'Hello World!'
 * @return	int	fd of opened map file
 */
static int	open_or_create(char *str)
{
	int		fd;
	char	*fn;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		fn = ft_strcat_multi(3, P_NAMES, str, ".fdf");
		fd = open(fn, O_RDONLY);
		free(fn);
		if (fd == -1)
		{
			if (ft_strlen(str) + 5 >= FOPEN_MAX)
				dbg_printf(err_block, "max: %i charaters :/", FOPEN_MAX - 6);
			else
				fd = create_map(str);
		}
		else
			dbg_printf(no_block, "map with name '%s' already exists so it will"
				" be opend instead of creating it again", str);
	}
	return (fd);
}

/*  check if there are args
    try open file
    read line by line and create rows and columns linked list
    return that
*/

/**
 * @brief	checks if 'argc' = 2 and takes the string from 'argv[1]' to
 * 			create (if it does't exist) and open the map with 'open_or_create'.
 *
 * 			with 'fd' set the map-file is read line by line via 'get_next_line'.
 * 			each line is split into single values via 'ft_split' and passed to
 * 			'line2nodes', which creates a new node for each value and appends it
 * 			to the end of the linked list 'mod->net'. furthermore the pointer
 * 			'prev_row' is set (by 'line2nodes') to the first node in the current
 * 			line, so that starting from the second line each node can be linked
 * 			to its NORTH neighbor node.
 * 
 * 			Finally the opened map is closed.
 * 
 * @param	argc	see 'main'
 * @param	argv	see 'main'	 
 * @param	mod		pointer to the struct that contains all info about the model	
 */
void	load_map(int argc, char **argv, t_model *mod)
{
	int		fd;
	char	*line;
	int		cur_row;
	t_node	*prev_row;

	if (argc != 2)
		dbg_printf(err_block, "wrong arguments!");
	mod->net = NULL;
	fd = open_or_create(argv[1]);
	line = gnl(fd);
	dbg_printf(no_block, "read Line: %s", line);
	cur_row = 1;
	prev_row = NULL;
	while (line)
	{
		line2nodes(ft_split(line, ' '), cur_row, &prev_row, mod);
		free(line);
		line = gnl(fd);
		dbg_printf(no_block, "read Line: %s", line);
		cur_row++;
	}
	free(line);
	line = NULL;
	close(fd);
}
