/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:35:41 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/20 16:47:08 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_map(t_maze *maze)
{
	// int x;
	// int y;
	int	i;
	int	j;
	// int step;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 100)
		{
			mlx_put_pixel(maze->mini_map, i, j, 0x80808080);
			j++;
		}
		i++;
	}
	// double conv_x = 200/maze->map.width;
	// double conv_y = 100/maze->map.height;
	// x = maze->player.pos_x * 64;
	// y = maze->player.pos_y * 64;
	// mlx_put_pixel(maze->mini_map, x, y, 0xFF0000FF);

	// // maze->raycast.distance_to_wall * maze->vector.ray_dir_y 
	// while (step < maze->raycast.distance_to_wall)
	// {
	// 	mlx_put_pixel(maze->mini_map, x, y, 0x00FF00FF);
	// 	x = step * maze->vector.ray_dir_x;
	// 	y = step * maze->vector.ray_dir_y;
	// }
}
