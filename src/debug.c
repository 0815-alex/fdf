/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:11:27 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 17:44:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ini_debug(t_model *model, int curr_stack_depth)
{
	model->dbg.count_stack_depth = curr_stack_depth;
}

static void	print_tab_level(t_model *model, t_dbg_flag dbg_flg)
{
	int	tabs;
	int	tab_width;

	tabs = 0;
	tab_width = 5;
	if (dbg_flg == end_block)
		model->dbg.count_stack_depth--;
	while (tabs < (model->dbg.count_stack_depth) * tab_width)
	{
		write(1, " ", 1);
		tabs++;
	}
	if (dbg_flg == start_block)
		model->dbg.count_stack_depth++;
	if (dbg_flg == start_block)
		ft_putstr_fd(WRITE_COLOR_ORANGE "  [START] >", 1);
	else if (dbg_flg == end_block)
		ft_putstr_fd(WRITE_COLOR_GREEN "  [DONE] >>", 1);
	else if (dbg_flg == err_block)
		ft_putstr_fd(WRITE_COLOR_RED "[ERROR] ", 1);
	ft_putstr_fd(WRITE_COLOR_DEFAULT, 1);
}

void	dbg_printf(t_model *model, t_dbg_flag dbg_flg, char *str, ...)
{
	va_list	args;
	int		len;
	int		len_add;

	if (DEBUG == 1 || dbg_flg == err_block)
	{
		print_tab_level(model, dbg_flg);
		va_start(args, str);
		len = 0;
		while (*str)
		{
			if (*str == '%')
			{
				str++;
				len_add = 0;
				len_add = print_whatever(args, (char *)str);
				if (len_add == 0)
				{
					len_add = print_whatever_digits(args, (char *)str);
					str++;
				}
				len += len_add;
			}
			else
				print_char(*str, &len);
			str++;
		}
		va_end(args);
		ft_putstr_fd("\n", 1);
		if (dbg_flg == err_block)
		{
			perror("\nSystem error msg");
			exit(0);
		}
	}
}
