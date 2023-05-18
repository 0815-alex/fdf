/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:31:40 by astein            #+#    #+#             */
/*   Updated: 2023/05/16 18:41:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*window_ptr;

	mlx_ptr = mlx_init();
	window_ptr = mlx_new_window(mlx_ptr, 500 , 500, "HI");
	mlx_loop(mlx_ptr);
	return(0);
	
}
