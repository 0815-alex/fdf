/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:31:40 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 14:47:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftf.h"

int	main(int argc, char **argv)
{
	t_model	*model;
	t_point	*curr_point;
	t_point	*curr_point2;

	ft_putstr_fd("\n\nLets go!\n===========================\n\n", 1);
	model = new_model(argc, argv);
	// 4. draw
	put_test_line(model);
	// put_net(model, COLOR_WHITE, 0, 0);
	// 5. loop for ever
	dbg_printf(model, no_block, "start deamon...\n");
	mlx_loop(model->mlx);
	return (0);
}
