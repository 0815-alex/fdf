/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator_utils.c                                :+:      :+:    :+:   */
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

void	insert_empty_char(t_list **fds)
{
	t_list	*cur_fd;
	char	*cur_filename;

	cur_filename = ft_strcat_multi(2, P_CHARS, "sp.fdf");
	cur_fd = malloc(sizeof(t_fd));
	((t_fd *)cur_fd)->next = NULL;
	((t_fd *)cur_fd)->fd = open(cur_filename, O_RDONLY);
	dbg_printf(no_block, "open file: %s | fd=%i",
		cur_filename, ((t_fd *)cur_fd)->fd);
	ft_lstadd_back(fds, cur_fd);
	free(cur_filename);
}

char	*create_new_file(char *str, int *new_fd)
{
	char	*new_filename;
	mode_t	pmode;

	dbg_printf(start_block, "create_new_file");
	ft_str_replace_chr(str, '!', '_');
	ft_str_replace_chr(str, '?', '_');
	ft_str_replace_chr(str, '.', '_');
	ft_str_replace_chr(str, ' ', '_');
	new_filename = ft_strcat_multi(3, P_NAMES, str, ".fdf");
	pmode = S_IRUSR | S_IWUSR;
	*new_fd = open(new_filename, O_RDWR | O_CREAT, pmode);
	if (*new_fd == -1)
		dbg_printf(err_block, "creating new map file: %s", new_filename);
	dbg_printf(no_block, "new fd %i | file path: %s", *new_fd, new_filename);
	dbg_printf(end_block, "create_new_file");
	return (new_filename);
}

char	*create_filename(char *str)
{
	char	*buffer;
	char	*cur_filename;

	cur_filename = ft_calloc(ft_strlen(P_CHARS) + 8, sizeof(char));
	buffer = malloc(sizeof(char) * 2);
	ft_bzero(cur_filename, 8);
	ft_strlcat(cur_filename, P_CHARS, ft_strlen(P_CHARS) + 1);
	ft_strlcpy(buffer, &str[0], 2);
	if (ft_isalnum(*buffer))
		ft_strlcat(cur_filename, buffer, ft_strlen(cur_filename) + 2);
	else if (*buffer == '!')
		ft_strlcat(cur_filename, "em", ft_strlen(cur_filename) + 3);
	else if (*buffer == '?')
		ft_strlcat(cur_filename, "qm", ft_strlen(cur_filename) + 3);
	else if (*buffer == '-')
		ft_strlcat(cur_filename, "dh", ft_strlen(cur_filename) + 3);
	else if (*buffer == '.')
		ft_strlcat(cur_filename, "dt", ft_strlen(cur_filename) + 3);
	else if (*buffer == '_')
		ft_strlcat(cur_filename, "us", ft_strlen(cur_filename) + 3);
	else if (*buffer == ' ')
		ft_strlcat(cur_filename, "sp", ft_strlen(cur_filename) + 3);
	else
		dbg_printf(err_block, "char '%c' is not allowed. only a-b, A-Z, 0-9 and"
				" '!?. _-' are allowed!", buffer[0]);
	ft_strlcat(cur_filename, ".fdf", ft_strlen(cur_filename) + 5);
	free(buffer);
	return (cur_filename);
}

t_list	**create_fd_list(char *str)
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
		if (((t_fd *)cur_fd)->fd == -1)
			dbg_printf(err_block, "opening letter file: %s", cur_filename);
		dbg_printf(no_block, "open file: %s | fd=%i",
			cur_filename, ((t_fd *)cur_fd)->fd);
		free(cur_filename);
		ft_lstadd_back(fds, cur_fd);
		str++;
	}
	insert_empty_char(fds);
	return (fds);
}

/**
 * @brief	reopening the new_file to be able to read from the beginning
 * 
 * 
 * @param fds 
 * @param strs 
 * @param new_fd 
 */
void	free_fd_list(t_list **fds, char *new_fn, int *new_fd)
{
	t_list	*cur_fd;

	cur_fd = *fds;
	while (cur_fd)
	{
		close(((t_fd *)cur_fd)->fd);
		dbg_printf(no_block, "closed file fd=%i", ((t_fd *)cur_fd)->fd);
		cur_fd = ((t_list *)cur_fd)->next;
	}
	cur_fd = *fds;
	free_whatever("lp", fds, fds);
	close(*new_fd);
	*new_fd = open(new_fn, O_RDONLY);
	if (*new_fd == -1)
		dbg_printf(err_block, "reopening new map file: %s", new_fn);
	dbg_printf(no_block, "reopen new map file: %s | fd=%i", new_fn, *new_fd);
	free(new_fn);
}
