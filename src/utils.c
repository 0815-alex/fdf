/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:06:51 by astein            #+#    #+#             */
/*   Updated: 2023/05/24 11:38:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double	degree2radian(int degree)
{
	double	radian;

	radian = degree * (M_PI / 180.0);
	return (radian);
}

int	radian2degree(double radian)
{
	int	degree;

	degree = (int)(radian * (180.0 / M_PI));
	return (degree);
}

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

//die idee ist, dass die mit in libftprintf kommt
//genau wie dbg_printf
//dbg printf muesste dann aber in der lage sein
//eine projektspezifische END function aufzurufen, die alles rueckwaerts
//freed, kein plan wie das gehen soll
// void	*check_malloc(size_t s)
// {
// 	void	*ptr;
// 	ptr = malloc (s);
// 	if (!ptr)
//         dbg_printf(mod, err_block, "malloc failed");
// 	return(ptr);
// }

/**
 * p = pointer
 * a = array
*/
void	*free_whatever(t_model *mod, char *str, ...)
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
			dbg_printf(mod, err_block, "bad param free_whatever: %c", str[0]);
		str++;
	}
	va_end(args);
	return (NULL);
}
