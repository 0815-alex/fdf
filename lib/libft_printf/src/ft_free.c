/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:39:45 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

static void	free_arr(void **arr)
{
	int	arr_i;

	arr_i = 0;
	while (arr[arr_i])
	{
		free(arr[arr_i]);
		arr_i++;
	}
	free(arr);
}

void	*free_whatever(char *str, ...)
{
	va_list	args;
	void	*ptr;

	ptr = NULL;
	va_start(args, str);
	while (*str)
	{
		if (*str == 'p')
		{
			ptr = va_arg(args, void *);
			if (ptr)
				free(ptr);
			ptr = NULL;
		}
		else if (*str == 'a')
			free_arr(va_arg(args, void **));
		else
			ft_printf("bad param free_whatever: %c\n", str[0]);
		str++;
	}
	va_end(args);
	return (NULL);
}
