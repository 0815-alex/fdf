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

#include "../libft_printf.h"

/**
 * @brief	keeps track of the indent level of the debug messages. each time a
 * 			'start_block' / 'end_block' is called the indent level will be
 * 			in- / decreased to improve the readability of the output.
 * 
 * 			'start_block', 	'err_block'	and 'end_block' msgs will be highlighted
 * 			with color and keywords.
 * 
 * 			the current indent level is stored in the static var 'cur_indent'.
 * 
 * @param dbg_flg	defining the type of message which should be printed
 */
static void	print_indent_level(t_dbg_flag dbg_flg)
{
	static int	cur_indent;
	int			tabs;
	int			tab_width;

	tabs = 0;
	tab_width = 5;
	if (dbg_flg == end_block && cur_indent > 0)
		cur_indent--;
	while (tabs < (cur_indent) * tab_width)
	{
		write(1, " ", 1);
		tabs++;
	}
	if (dbg_flg == start_block)
		cur_indent++;
	if (dbg_flg == start_block)
		ft_putstr_fd(WRITE_COLOR_ORANGE "  [START] >", 1);
	else if (dbg_flg == end_block)
		ft_putstr_fd(WRITE_COLOR_GREEN "  [DONE] >>", 1);
	else if (dbg_flg == err_block)
		ft_putstr_fd(WRITE_COLOR_RED "[ERROR] ", 1);
	ft_putstr_fd(WRITE_COLOR_DEFAULT, 1);
}

/**
 * @brief   prints debug messages folowed by a new line if the DEBUG equals 1.
 *          the parameter can be set via the MAKEFILE.
 * 
 * 			'start_block', 	'err_block'	and 'end_block' msgs will be highlighted
 * 			with the keywords definded in 'print_indent_level()'.
 * 
 * 			each time a 'start_block' / 'end_block' is called the indent level
 * 			will be in- / decreased to improve the readability of the output.
 * 
 *          NOTE:   'err_block' messages will be printed always followed by the
 *                  'perror' message and the programm will exit!
 * 
 * @param dbg_flg   defining the type of message which should be printed
 * @param str       the message itself following the 'ft_printf' scheme
 * @param ...       values to be included in the message (see 'ft_printf')
 */
void	dbg_printf(t_dbg_flag dbg_flg, char *str, ...)
{
	va_list			args;

	if (DEBUG == 1 || dbg_flg == err_block)
	{
		print_indent_level(dbg_flg);
		va_start(args, str);
		while (*str)
		{
			if (*str == '%')
			{
				if (print_whatever(args, (char *)(++str)) == 0)
					print_whatever_digits(args, (char *)(str++));
			}
			else
				ft_putchar_fd(*str, 1);
			str++;
		}
		va_end(args);
		ft_putstr_fd("\n", 1);
		if (dbg_flg != err_block)
			return ;
		perror("\nSystem error msg");
		exit (1);
	}
}
