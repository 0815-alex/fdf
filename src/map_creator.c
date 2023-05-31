/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 01:07:33 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 21:19:42 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;

}				t_fd;

/**
 * @brief Create a map object
 * 
 * 	Is store in strs	0	get_next_line
 * 						1	get_next_line without linebreak
 * 						2	new filename
 * @param str 
 * @return char* 
 */
char	*create_map(char *str)
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
		strs[0] = get_next_line(((t_fd *)cur_fd)->fd);
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
	free_fd_list(fds, new_fd);
    sleep(1);
	return (strs[2]);
}
