/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/06 16:28:12 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initial_dist_from_start(maze)
{
	
}

void	distance_next_intersection(t_maze *maze)
{
	if (maze->vector.ray_dir_x == 0)
		maze->vector.ray_dir_x = 1e30;
	if (maze->vector.ray_dir_y == 0)
		maze->vector.ray_dir_y = 1e30;
    maze->raycast.delta_dist_x = abs(1/maze->vector.ray_dir_x);
    maze->raycast.delta_dist_y = abs(1/maze->vector.ray_dir_y);
}

void	ray_direction(t_maze *maze, int x)
{
	maze->raycast.camera_x = 2 * x / WIDTH - 1;
	maze->vector.ray_dir_x = maze->vector.dir_x + maze->vector.plane_x * maze->raycast.camera_x;
	maze->vector.ray_dir_y = maze->vector.dir_y + maze->vector.plane_y * maze->raycast.camera_x;
}

void	raycasting(t_maze *maze)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ray_direction(maze, x);
		distance_next_intersection(maze);
		initial_dist_from_start(maze);
		x++;
	}
}
