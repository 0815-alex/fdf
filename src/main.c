/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:31:40 by astein            #+#    #+#             */
/*   Updated: 2023/05/21 17:59:39 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_model	*model;

	ft_putstr_fd("\n\nLets go!\n===========================\n\n", 1);
	model = new_model(argc, argv);
	create_new_img(model);
	dbg_printf(model, no_block, "start deamon...\n");
	mlx_loop(model->mlx);
	return (0);
}
