/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 01:07:33 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 06:26:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;

}				t_fd;

char	*create_map(char *str)
{
	t_list	**fds;
	t_list	*cur_fd;
	char	*cur_letter;
	char	cur_filename[100];
	int		new_file_fd;
	char	*new_file_name;
	char	*str_backup;
	char	*cur_line;
	t_list	*temp;
	t_bool	eof;

	printf("NEW MAP CREATE START: %s\n", str);
	str_backup = str;
	//looped durch den string
	fds = NULL;
	cur_filename[0] = '\0';
	cur_letter = malloc(sizeof(char) * 2);
	fds = malloc(sizeof(t_list *));
	*fds = NULL;
	cur_fd = malloc(sizeof(t_fd));
	((t_fd *)cur_fd)->next = NULL;
	ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
	ft_strlcat(cur_filename, "space", ft_strlen(cur_filename) + 6);
	ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
	((t_fd *)cur_fd)->fd = open(&cur_filename[0], O_RDONLY);
	printf("open file: %s | fd=%d\n", cur_filename, ((t_fd *)cur_fd)->fd);
	ft_bzero(cur_filename, 100);
	ft_lstadd_back(fds, cur_fd);
	while (*str)
	{
		// *str = ft_toupper(*str);
		if (ft_isalnum(*str))
		{
			//oeffnet die datein und speichert die fd in einer liste
			cur_fd = malloc(sizeof(t_fd));
			((t_fd *)cur_fd)->next = NULL;
			ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
			ft_strlcpy(cur_letter, &str[0], 2);
			printf("cur letter: %s\n", cur_letter);
			ft_strlcat(cur_filename, cur_letter, ft_strlen(cur_filename) + 2);
			ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
			((t_fd *)cur_fd)->fd = open(&cur_filename[0], O_RDONLY);
			printf("open file: %s | fd=%d\n", cur_filename,
					((t_fd *)cur_fd)->fd);
			ft_lstadd_back(fds, cur_fd);
			ft_bzero(cur_filename, 100);
			cur_fd = malloc(sizeof(t_fd));
			((t_fd *)cur_fd)->next = NULL;
			ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
			ft_strlcpy(cur_letter, &str[0], 2);
			printf("cur letter: %s\n", cur_letter);
			ft_strlcat(cur_filename, cur_letter, ft_strlen(cur_filename) + 2);
			ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
			((t_fd *)cur_fd)->fd = open(&cur_filename[0], O_RDONLY);
			printf("open file: %s | fd=%d\n", cur_filename,
					((t_fd *)cur_fd)->fd);
			ft_lstadd_back(fds, cur_fd);
			ft_bzero(cur_filename, 100);
		}
		else
		{
			cur_fd = malloc(sizeof(t_fd));
			((t_fd *)cur_fd)->next = NULL;
			ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
			ft_strlcat(cur_filename, "questionmark", ft_strlen(cur_filename) + 13);
			ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
			((t_fd *)cur_fd)->fd = open(&cur_filename[0], O_RDONLY);
			printf("open file: %s | fd=%d\n", cur_filename,
					((t_fd *)cur_fd)->fd);
			ft_bzero(cur_filename, 100);
			ft_lstadd_back(fds, cur_fd);
			str[0] = '?';
		}
		str++;
	}
	cur_fd = malloc(sizeof(t_fd));
	((t_fd *)cur_fd)->next = NULL;
	ft_bzero(cur_filename, 100);
	ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
	ft_strlcat(cur_filename, "space", ft_strlen(cur_filename) + 6);
	ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
	((t_fd *)cur_fd)->fd = open(&cur_filename[0], O_RDONLY);
	printf("open file: %s | fd=%d\n", cur_filename, ((t_fd *)cur_fd)->fd);
	ft_lstadd_back(fds, cur_fd);
	cur_fd = malloc(sizeof(t_fd));
	((t_fd *)cur_fd)->next = NULL;
	ft_bzero(cur_filename, 100);
	ft_strlcat(cur_filename, PATH_2_CHARS, ft_strlen(PATH_2_CHARS) + 1);
	ft_strlcat(cur_filename, "space", ft_strlen(cur_filename) + 6);
	ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
	((t_fd *)cur_fd)->fd = open(&cur_filename[0], O_RDONLY);
	printf("open file: %s | fd=%d\n", cur_filename, ((t_fd *)cur_fd)->fd);
	ft_lstadd_back(fds, cur_fd);
	printf("all opened!\n");
	//looped duch die fd
	new_file_name = malloc(sizeof(char) * (ft_strlen(str)
				+ ft_strlen(PATH_2_CHARS) + 20));
	new_file_name[0] = '\0';
	ft_strlcat(new_file_name, PATH_2_NAMES, ft_strlen(PATH_2_NAMES) + 1);
	ft_strlcat(new_file_name, str_backup, ft_strlen(new_file_name)
			+ ft_strlen(str_backup) + 1);
	ft_strlcat(new_file_name, ".fdf", ft_strlen(new_file_name) + 5);
	printf("new file path: %s\n", new_file_name);
	new_file_fd = open(new_file_name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	cur_fd = *fds;
	eof = ft_false;
	while (cur_fd && eof == ft_false)
	{
		printf("read from fd: %d\n", ((t_fd *)cur_fd)->fd);
		cur_line = ft_strtrim(get_next_line(((t_fd *)cur_fd)->fd), "\n");
		printf("read = %s\n", cur_line);
		if (cur_line == NULL)
			eof = ft_true;
		else
			write(new_file_fd, cur_line, ft_strlen(cur_line));
		free(cur_line);
		cur_fd = ((t_list *)cur_fd)->next;
			write(new_file_fd, " ", 1);
		if (!cur_fd)
		{
			write(new_file_fd, "\n", 1);
			cur_fd = *fds;
		}
		
	}
	//  liest immer eine zeile
	//  dann linebreak
	// add EOF
	//closed alle fd
	close(new_file_fd);
	printf("closed fd new file: %d\n", new_file_fd);
	cur_fd = *fds;
	while (cur_fd)
	{
		close(((t_fd *)cur_fd)->fd);
		printf("closed fd: %d\n", ((t_fd *)cur_fd)->fd);
		cur_fd = ((t_list *)cur_fd)->next;
	}
	//freed stuff
	free(cur_letter);
	while (*fds)
	{
		temp = *fds;
		*fds = (*fds)->next;
		free(temp);
	}
	free(fds);
	// exit(0);
	sleep(1);
	printf("return (new filename: %s\n", new_file_name);
	return (new_file_name);
}
