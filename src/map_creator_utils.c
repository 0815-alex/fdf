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

/**
 * @brief	used to store the fd of all charcaters of the new map
 */
typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;

}				t_fd;

/**
 * @brief	opens the character file containing a space (./.../sp.fdf) and
 * 			adding it's fd to the end of the linked list 'fds'
 * 
 * @param	fds	the linked list of all fd's
 */
static void	insert_empty_char_fd(t_list **fds)
{
	t_list	*cur_fd;
	char	*cur_fn;

	cur_fn = ft_strcat_multi(2, P_CHARS, "sp.fdf");
	cur_fd = malloc(sizeof(t_fd));
	((t_fd *)cur_fd)->next = NULL;
	((t_fd *)cur_fd)->fd = open(cur_fn, O_RDONLY);
	dbg_printf(no_block, "open file: %s | fd=%i",
		cur_fn, ((t_fd *)cur_fd)->fd);
	ft_lstadd_back(fds, cur_fd);
	free(cur_fn);
}

/**
 * @brief	creates the filename of the char 'c' by prefixing the path and
 * 			suffix the .fdf file extension and returns it. the following special
 * 			characters are also valid:	"!?. _-"
 * 
 * 			NOTE:	other characters will generate an error and stop the program
 * 					via 'dbg_printf()'
 * 
 * @param	c		the char a file should be found for
 * @return	char*	the path to the file representing the char 'c'
 */
static char	*create_filename(char c)
{
	char	*fn;
	char	*buf;

	if (ft_isalnum(c))
	{
		buf = ft_chr2str(c);
		fn = ft_strcat_multi(3, P_CHARS, buf, ".fdf");
		free(buf);
	}
	else if (c == '!')
		fn = ft_strcat_multi(2, P_CHARS, "em.fdf");
	else if (c == '?')
		fn = ft_strcat_multi(2, P_CHARS, "qm.fdf");
	else if (c == '-')
		fn = ft_strcat_multi(2, P_CHARS, "dh.fdf");
	else if (c == '.')
		fn = ft_strcat_multi(2, P_CHARS, "dt.fdf");
	else if (c == '_')
		fn = ft_strcat_multi(2, P_CHARS, "us.fdf");
	else if (c == ' ')
		fn = ft_strcat_multi(2, P_CHARS, "sp.fdf");
	else
		dbg_printf(err_block, "char '%c' is not allowed. only a-b, A-Z, 0-9 and"
			" '!?. _-' are allowed!", c);
	return (fn);
}

/**
 * @brief	creates and opens the new map file. the filename will be mofifierd
 * 			so that those "!?. " characters will be replaced by '_'
 * 
 * 			NOTE:	the permissions of the file are set to RW only
 * 
 * @param	str		string of the new file	
 * @param	new_fd	[return]	the fd of the new map file
 * @return	char*	[return]	the name of the new map file
 */
char	*create_new_file(char *str, int *new_fd)
{
	char	*new_fn;
	mode_t	pmode;

	dbg_printf(start_block, "create_new_file");
	ft_str_replace_chr(str, '!', '_');
	ft_str_replace_chr(str, '?', '_');
	ft_str_replace_chr(str, '.', '_');
	ft_str_replace_chr(str, ' ', '_');
	new_fn = ft_strcat_multi(3, P_NAMES, str, ".fdf");
	pmode = S_IRUSR | S_IWUSR;
	*new_fd = open(new_fn, O_RDWR | O_CREAT, pmode);
	if (*new_fd == -1)
		dbg_printf(err_block, "creating new map file: %s", new_fn);
	dbg_printf(no_block, "new fd %i | file path: %s", *new_fd, new_fn);
	dbg_printf(end_block, "create_new_file");
	return (new_fn);
}

/**
 * @brief	creates and returns a linked list 'fds'. the list holds a fd for
 * 			each character of the string 'str'. to get the filenames of each
 * 			char 'create_filename()' is used and the resulting filneame will be
 * 			opend in readonly to recive a fd. 
 * 
 * 			NOTE:	an additional space is attached to the front and the end of
 * 					the list via 'insert_empty_char_fd()' to get a better 3D map
 * 
 * @param	str			string to create a fds list from
 * @return	t_list**	the head of the resulting linked list of fd's
 */
t_list	**create_fd_list(char *str)
{
	t_list	**fds;
	t_list	*cur_fd;
	char	*cur_fn;

	fds = malloc(sizeof(t_list *));
	*fds = NULL;
	insert_empty_char_fd(fds);
	while (*str)
	{
		cur_fn = create_filename(str[0]);
		cur_fd = malloc(sizeof(t_fd));
		((t_fd *)cur_fd)->next = NULL;
		((t_fd *)cur_fd)->fd = open(cur_fn, O_RDONLY);
		if (((t_fd *)cur_fd)->fd == -1)
			dbg_printf(err_block, "opening letter file: %s", cur_fn);
		dbg_printf(no_block, "open file: %s | fd=%i",
			cur_fn, ((t_fd *)cur_fd)->fd);
		free(cur_fn);
		ft_lstadd_back(fds, cur_fd);
		str++;
	}
	insert_empty_char_fd(fds);
	return (fds);
}

/**
 * @brief	after the new map file is created this function cleans up all the
 * 			mess.
 * 		therfore it:
 * 			- closes all fd's stored in the 'fds' linked list
 * 			- frees the linked list using 'free_whatever()'
 * 			- closes an opens the new_file to be able to read from the beginning
 * 				of the file.
 * 
 * @param fds		linked list containing all fd's
 * @param new_fn	the name of the new map (will be freed)		
 * @param new_fd	the fd of the new map (to reopen it)
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
