/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:31:40 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 21:17:49 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void err_exit(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

/**
 * @brief	Here everything starts ;)
 * 			
 * 			the whole project is based on a instance of 't_model' called 'mod'
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

	mod = new_model(argc, argv);
	sleep(1);
	mlx_loop(mod->mlx);
	return (0);
}
