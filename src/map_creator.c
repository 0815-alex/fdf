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
	dbg_printf(no_block, "open file: %s | fd=%d\n", cur_filename,
			((t_fd *)cur_fd)->fd);
	ft_lstadd_back(fds, cur_fd);
	ft_bzero(cur_filename, 100);
}

static char	*create_new_filename(char *str, int *new_fd)
{
	char	*new_filename;

	dbg_printf(start_block, "create_new_file");
	new_filename = malloc(sizeof(char) * (ft_strlen(str)
				+ ft_strlen(PATH_2_CHARS) + 20));
	new_filename[0] = '\0';
	ft_strlcat(new_filename, PATH_2_NAMES, ft_strlen(PATH_2_NAMES) + 1);
	ft_strlcat(new_filename, str, ft_strlen(new_filename) + ft_strlen(str) + 1);
	ft_strlcat(new_filename, ".fdf", ft_strlen(new_filename) + 5);
	dbg_printf(no_block, "new file path: %s\n", new_filename);
	*new_fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dbg_printf(end_block, "create_new_file");
	return (new_filename);
}

static char	*create_filename(char *str)
{
	char	*buffer;
	char	*cur_filename;

	cur_filename = ft_calloc(ft_strlen(PATH_2_CHARS) + 8, sizeof(char));
	buffer = malloc(sizeof(char) * 2);
	ft_bzero(cur_filename, 8);
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
	free(buffer);
	return (cur_filename);
}

static t_list	**create_fd_list(char *str)
{
	t_list	**fds;
	t_list	*cur_fd;
	char	*cur_filename;

	fds = malloc(sizeof(t_list *));
	*fds = NULL;
	insert_empty_char(fds);
	while (*str)
	{
		cur_filename = create_filename(str);
		cur_fd = malloc(sizeof(t_fd));
		((t_fd *)cur_fd)->next = NULL;
		((t_fd *)cur_fd)->fd = open(cur_filename, O_RDONLY);
		free(cur_filename);
		ft_lstadd_back(fds, cur_fd);
		str++;
	}
	insert_empty_char(fds);
	return (fds);
}

static void	free_fd_list(t_list **fds, int new_fd)
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
	ft_lstclear(fds, null_ptr);
	free(fds);
	close(new_fd);
}

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
	strs[0] = get_next_line(((t_fd *)cur_fd)->fd);
	strs[2] = create_new_filename(str, &new_fd);
	while (cur_fd && strs[0])
	{
		strs[1] = ft_strtrim(strs[0], "\n");
		free(strs[0]);	//sure that this free frees all? im not sure :D
		write(new_fd, strs[1], ft_strlen(strs[1]));
		free(strs[1]);
		cur_fd = ((t_list *)cur_fd)->next;
		if (!cur_fd)
			write(new_fd, "\n", 1);
		if (!cur_fd)
			cur_fd = *fds;
		else
			write(new_fd, " ", 1);
		strs[0] = get_next_line(((t_fd *)cur_fd)->fd);
	}
	free_fd_list(fds, new_fd);
	return (strs[2]);
}
