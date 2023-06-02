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

/**
 * @brief	Here everything starts ;)
 * 			
 * 			the whole project is based on a instance of 't_model' here named mod
 * 			it will be created using 'new_model'
 * 
 * 			the programm allows to different parameters
 * 			either	a path to a map 			e.g. './maps/astein.fdf'
 * 			or		a string to create a map	e.g. 'Hello World!'
 *
 * @param	argc 	see above
 * @param	argv 	see above
 * @return	int		always 0
 */
int	main(int argc, char **argv)
{
	t_model	*mod;

	dbg_printf(start_block, "main");
	mod = new_model(argc, argv);
	dbg_printf(no_block, "start deamon...\n");
	sleep(1);
	mlx_loop(mod->mlx);
	dbg_printf(end_block, "main");
	return (0);
}
