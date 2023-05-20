/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:11:27 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 16:45:03 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_debug(t_model *model, int curr_stack_depth)
{
	model->dbg = malloc(sizeof(t_dbg));
	model->dbg->count_stack_depth = curr_stack_depth;
}

void	dbg_printf(t_model *model, t_dbg_flag dbg_flg, char *str, ...)
{
	va_list	args;
	int		len;
	int		tabs;
	int		tab_width;

	tabs = 0;
	tab_width = 5;
	if (DEBUG == 1 || dbg_flg == error_block)
	{
		//change stack DONE
		if (dbg_flg == end_block)
			model->dbg->count_stack_depth--;
		//Print tabs
		while (tabs < (model->dbg->count_stack_depth) * tab_width)
		{
			print_char(' ', &len);
			tabs++;
		}
		//change stack START
		if (dbg_flg == start_block)
			model->dbg->count_stack_depth++;
		//Change color and print START and DONEreset color
		if (dbg_flg == start_block)
			ft_putstr_fd(WRITE_COLOR_ORANGE "  [START] >", 1);
		else if (dbg_flg == end_block)
			ft_putstr_fd(WRITE_COLOR_GREEN "  [DONE] >>", 1);
		else if (dbg_flg == error_block)
			ft_putstr_fd(WRITE_COLOR_RED "[ERROR] ", 1);
		//reset color
		ft_putstr_fd(WRITE_COLOR_DEFAULT, 1);
		//print the actual string
		// print_char('>', &len);
		va_start(args, str);
		len = 0;
		while (*str)
		{
			if (*str == '%')
			{
				str++;
				len += print_whatever(args, (char *)str);
			}
			else
				print_char(*str, &len);
			str++;
		}
		va_end(args);
		//print a new line
		ft_putstr_fd("\n", 1);
		if (dbg_flg == error_block)
			exit(0);
	}
}
