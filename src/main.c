/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:31:40 by astein            #+#    #+#             */
/*   Updated: 2023/05/25 22:24:02 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_model	*mod;

    printf("DEBUG: %d", DEBUG);
	dbg_printf(start_block, "main");
	mod = new_model(argc, argv);
	dbg_printf(no_block, "start deamon...\n");
	sleep(1);
	mlx_loop(mod->mlx);
	dbg_printf(end_block, "main");
	return (0);
}
