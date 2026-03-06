/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/06 18:36:05 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initial_dist_from_player_pos(t_maze *maze)
{
	maze->raycast.grid_x = floor(maze->player.pos_x);
	maze->raycast.grid_y = floor(maze->player.pos_y);
	if (maze->vector.ray_dir_x < 0)
	{
		maze->raycast.step_x = -1;
		maze->raycast.dist_from_start_x = (maze->player.pos_x - maze->raycast.grid_x) * maze->raycast.delta_dist_x;
	}
	else
	{
		maze->raycast.step_x = 1;
		maze->raycast.dist_from_start_x = (maze->raycast.grid_x + 1 - maze->player.pos_x) * maze->raycast.delta_dist_x;
	}
	if (maze->vector.ray_dir_y < 0)
	{
		maze->raycast.step_y = -1;
		maze->raycast.dist_from_start_y = (maze->player.pos_y - maze->raycast.grid_y) * maze->raycast.delta_dist_y;
	}
	else
	{
		maze->raycast.step_y = 1;
		maze->raycast.dist_from_start_y = (maze->raycast.grid_y + 1 - maze->player.pos_y) * maze->raycast.delta_dist_y;
	}
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
	// ray direction = forward direction + horizontal offset
	// dir = where the player looks
	// plane = sideways direction (camera width)
	// cameraX = how far sideways we go
	maze->vector.ray_dir_x = maze->vector.dir_x + maze->vector.plane_x * maze->raycast.camera_x;
	maze->vector.ray_dir_y = maze->vector.dir_y + maze->vector.plane_y * maze->raycast.camera_x;
	// We multiply by cameraX because it tells how far left or right on the camera plane the ray should be.
	// A direction vector just tells which way the ray points.
}

void	raycasting(t_maze *maze)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ray_direction(maze, x);
		distance_next_intersection(maze);
		initial_dist_from_player_pos(maze);
		// Perform DDA
		x++;
	}
}
