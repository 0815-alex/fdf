/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:02:07 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 17:41:59 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief This sometimes works :D I still have some issues with rounding
 * 
 * @param d 
 * @param len 
 * @param digits 
 */
void	print_double(double d, int *len, int digits)
{
	double	rounded;
	int		part_int;
	double	part_dec;
	int		part_dec_int;

	rounded = round(d * pow(10, digits + 1)) / pow(10, digits + 1);
	part_int = (int)rounded;
	print_nbr(part_int, len);
	print_char('.', len);
	part_dec = rounded - part_int;
	part_dec *= pow(10, digits + 1);
	part_dec_int = (int)(round(part_dec) / 10);
	print_nbr(part_dec_int, len);
}
