/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 01:07:33 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 00:06:56 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	used to store the fd of all charcaters of the new map
 */
typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;

}				t_fd;

/**
 * @brief 	creates a new map for the string 'str' and returns the fd of it.
 * 
 * 			to do so this happens:
 * 			- 	all character files are opened and stored in the linked list
 * 				'fds' via 'create_fd_list()'
 * 			-	a new file is created and opend via 'create_new_file()'
 * 			-	a loop through all 'fds' will be started until reaching the EOF
 * 				- a line of the current fd is read via 'get_next_line()'
 * 				- the '\n' is cropped of via 'ft_strtrim()'
 * 				- the cropped line is written to the new map file
 * 				- if the last fd is reached
 * 					- a '\n' is written to the new map file
 * 					- the 'cur_fd' is set back to the beginning of the list
 * 				- else a ' ' is written
 * 			-	all files are closed, the list 'fds' is freed and the new map
 * 				file will be reopend all via 'free_fd_list()'
 * 
 * 			NOTE:	'strs' values are:
 * 						[0]	= current get_next_line
 * 						[1]	= current get_next_line without linebreak
 * 						[2]	= new filename
 * 
 * @param	str	the string to create a map for
 * @return	int	the fd of the new created and opend map
 */
int	create_map(char *str)
{
	t_list	**fds;
	int		new_fd;
	char	*strs[3];
	t_list	*cur_fd;

	fds = create_fd_list(str);
	cur_fd = *fds;
	strs[2] = create_new_file(str, &new_fd);
	while (cur_fd && strs[0])
	{
		strs[0] = gnl(((t_fd *)cur_fd)->fd);
		strs[1] = ft_strtrim(strs[0], "\n");
		free(strs[0]);
		write(new_fd, strs[1], ft_strlen(strs[1]));
		free(strs[1]);
		cur_fd = ((t_list *)cur_fd)->next;
		if (!cur_fd)
			write(new_fd, "\n", 1);
		if (!cur_fd)
			cur_fd = *fds;
		else
			write(new_fd, " ", 1);
	}
	free_fd_list(fds, strs[2], &new_fd);
	return (new_fd);
}
