/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:39:45 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function counts the digits of 'c'.
 * 			If 'c' < 0 the result includes one digit for the negative sign "-"
 * 
 * @param	c 
 * @return	int 
 */
static int	count_digits(long c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		c *= -1;
		i++;
	}
	while (c > 0)
	{
		c /= 10;
		i++;
	}
	return (i);
}

char	*ft_dtoa(double d, size_t digits)
{
	long	part_int;
	double	part_dec;
	char	*result;
	char	*buffer[2];
	size_t	i;

	part_int = (int)d;
	part_dec = fabs(d - part_int);

	i = 0;
	while (i < digits)
	{
		part_dec *= 10;
		i++;
	}
	part_dec = (int)(part_dec);
	buffer[0] = ft_itoa(part_int);
	buffer[1] = ft_itoa((int)part_dec);
	if (digits != 0)
		result = ft_calloc(count_digits(part_int)
				+ count_digits((int)part_dec) + 2, sizeof(char));
	else
		result = ft_calloc(count_digits(part_int) + 1, sizeof(char));
	ft_strlcat (result, buffer[0], ft_strlen (buffer[0]) + 1);
	if (digits != 0)
	{
		ft_strlcat (result, ".", ft_strlen (buffer[0]) + 2);
		ft_strlcat (result, buffer[1], ft_strlen(result)
			+ ft_strlen (buffer[1]) + 1);
	}
	free_whatever ("pp", buffer[0], buffer[1]);
	return (result);
}
