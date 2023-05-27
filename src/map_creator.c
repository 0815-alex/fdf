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

static void	insert_empty_char(t_list **fds)
{
	t_list	*cur_fd;
	char	cur_filename[100];

	cur_filename[0] = '\0';
	ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
	ft_strlcat(cur_filename, "sp.fdf", ft_strlen(cur_filename) + 7);
	cur_fd = malloc(sizeof(t_fd));
	((t_fd *)cur_fd)->next = NULL;
	((t_fd *)cur_fd)->fd = open(cur_filename, O_RDONLY);
	printf("open file: %s | fd=%d\n", cur_filename, ((t_fd *)cur_fd)->fd);
	ft_lstadd_back(fds, cur_fd);
	ft_bzero(cur_filename, 100);
}

static char	*create_new_file(char *str, int *new_fd)
{
	char	*new_file;

	new_file = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(PATH_2_CHARS)
				+ 20));
	new_file[0] = '\0';
	ft_strlcat(new_file, PATH_2_NAMES, ft_strlen(PATH_2_NAMES) + 1);
	ft_strlcat(new_file, str, ft_strlen(new_file) + ft_strlen(str) + 1);
	ft_strlcat(new_file, ".fdf", ft_strlen(new_file) + 5);
	printf("new file path: %s\n", new_file);
	*new_fd = open(new_file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (new_file);
}

static void	create_fd_list(t_list **fds, char *str)
{
	char	*buffer;
	t_list	*cur_fd;
	char	cur_filename[100];

	cur_filename[0] = '\0';
	buffer = malloc(sizeof(char) * 2);
	insert_empty_char(fds);
	while (*str)
	{
		ft_bzero(cur_filename, 100);
		ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
		ft_strlcpy(buffer, &str[0], 2);
		if (ft_isalnum(*buffer))
			ft_strlcat(cur_filename, buffer, ft_strlen(cur_filename) + 2);
		else if (*buffer == '!')
			ft_strlcat(cur_filename, "em", ft_strlen(cur_filename) + 3);
		else if (*buffer == '-')
			ft_strlcat(cur_filename, "dh", ft_strlen(cur_filename) + 3);
		else if (*buffer == '.')
			ft_strlcat(cur_filename, "dt", ft_strlen(cur_filename) + 3);
		else if (*buffer == '_')
			ft_strlcat(cur_filename, "us", ft_strlen(cur_filename) + 3);
		else if (*buffer == ' ')
			ft_strlcat(cur_filename, "sp", ft_strlen(cur_filename) + 3);
		else
			ft_strlcat(cur_filename, "qm", ft_strlen(cur_filename) + 3);
		ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
		cur_fd = malloc(sizeof(t_fd));
		((t_fd *)cur_fd)->next = NULL;
		((t_fd *)cur_fd)->fd = open(cur_filename, O_RDONLY);
		printf("open file: %s | fd=%d\n", cur_filename, ((t_fd *)cur_fd)->fd);
		ft_lstadd_back(fds, cur_fd);
		str++;
	}
	insert_empty_char(fds);
	free(buffer);
}

static void	free_fd_list(t_list **fds)
{
	t_list	*cur_fd;

	cur_fd = *fds;
	while (cur_fd)
	{
		close(((t_fd *)cur_fd)->fd);
		printf("closed fd: %d\n", ((t_fd *)cur_fd)->fd);
		cur_fd = ((t_list *)cur_fd)->next;
	}
	cur_fd = *fds;
	while (*fds)
	{
		cur_fd = *fds;
		*fds = (*fds)->next;
		free(cur_fd);
	}
}

char	*create_map(t_model *mod, char *str)
{
	t_list	**fds;
	int		new_fd;
	char	*new_file;
	char	*cur_line;
	char	*cur_line_trimmed;
	t_list	*cur_fd;

	fds = malloc(sizeof(t_list *));
	*fds = NULL;
	create_fd_list(fds, str);
	new_file = create_new_file(str, &new_fd);
	// ft_striteri(new_file)
	// hier den dateinamen noch von sonderyeichen befreien
	//loop through fd list and write a lines
	cur_fd = *fds;
	while (cur_fd)
	{
		dbg_printf(mod, no_block, "CUR FD %d\n", ((t_fd *)cur_fd)->fd);
		cur_line = get_next_line(((t_fd *)cur_fd)->fd);
		cur_line_trimmed = ft_strtrim(cur_line, "\n");
		free(cur_line);
		if (cur_line_trimmed == NULL)
			break ;
		write(new_fd, cur_line_trimmed, ft_strlen(cur_line_trimmed));
		free(cur_line_trimmed);
		cur_fd = ((t_list *)cur_fd)->next;
		if (!cur_fd)
		{
			write(new_fd, "\n", 1);
			cur_fd = *fds;
		}
		else
			write(new_fd, " ", 1);
	}
	//closed alle fd
	close(new_fd);
	free_fd_list(fds);
	free(fds);
	sleep(1);
	return (new_file);
}
