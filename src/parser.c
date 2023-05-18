/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:30:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/18 17:14:13 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

/*  check if there are args
    try open file
    read line by line and create rows and columns linked list
    return that
*/
void	load_file(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		ft_printf("\n\nERROR!\nMissing a filename as a parameter!\n\n");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	ft_printf("1. Line: %s", line);
	free(line);
	close(fd);
}
