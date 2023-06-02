/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:32:33 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

static void	malloc_result_str(int amount_of_strs, va_list args,
	t_list ***strs, char **result)
{
	size_t	len;
	int		i;
	char	*buffer;

	len = 0;
	i = -1;
	*strs = malloc(sizeof(t_list *));
	**strs = NULL;
	while (++i < amount_of_strs)
	{
		buffer = va_arg(args, char *);
		len += ft_strlen(buffer);
		ft_lstadd_back(*strs, ft_lstnew(buffer));
	}
	*result = ft_calloc(len + 1, sizeof(char));
}

static void	fill_result_str(t_list **strs, char *result)
{
	size_t	len;
	char	*cur_ptr;
	t_list	*cur_node;

	cur_node = *strs;
	cur_ptr = result;
	while (cur_node)
	{
		len = ft_strlen(cur_node->content);
		ft_memcpy(cur_ptr, cur_node->content, len);
		cur_ptr += len;
		cur_node = cur_node->next;
	}
	free_whatever("l", strs);
	*cur_ptr = '\0';
}

char	*ft_strcat_multi(int amount_of_strs, ...)
{
	va_list	args;
	char	*result;
	t_list	**strs;

	strs = NULL;
	va_start(args, amount_of_strs);
	malloc_result_str(amount_of_strs, args, &strs, &result);
	va_end(args);
	fill_result_str(strs, result);
	return (result);
}
