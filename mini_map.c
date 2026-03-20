/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:35:41 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/20 15:57:23 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_map(t_maze *maze)
{
	double x;
	double y;
	int step;

	x = maze->player.pos_x;
	y = maze->player.pos_y;
	step = 1;
	mlx_put_pixel(maze->mini_map, maze->player.pos_x, maze->player.pos_y, 0xFF0000FF);
	// maze->raycast.distance_to_wall * maze->vector.ray_dir_y ;
	while (step < maze->raycast.distance_to_wall)
	{
		mlx_put_pixel(maze->mini_map, x, y, 0x00FF00FF);
		x = step * maze->vector.ray_dir_x;
		y = step * maze->vector.ray_dir_y;
	}
}
