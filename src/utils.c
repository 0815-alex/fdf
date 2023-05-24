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

int	radian2degree2(double radian)
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

/**
 * p = pointer
 * a = array
*/
void	*free_whatever(t_model *model, char *str, ...)
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
			dbg_printf(model, err_block, "bad param free_whatever: %c", str[0]);
		str++;
	}
	va_end(args);
	return (NULL);
}
