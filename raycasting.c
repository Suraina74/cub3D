/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/04/10 18:08:22 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initial_ray_length(t_maze *maze)
{
	maze->raycast.grid_x = (int)maze->player.pos_x;
	maze->raycast.grid_y = (int)maze->player.pos_y;
	if (maze->vector.ray_dir_x < 0)
	{
		maze->raycast.step_x = -1;
		maze->raycast.ray_len_x = (maze->player.pos_x \
- maze->raycast.grid_x) * maze->raycast.delta_dist_x;
	}
	else
	{
		maze->raycast.step_x = 1;
		maze->raycast.ray_len_x = (maze->raycast.grid_x + 1.0 \
- maze->player.pos_x) * maze->raycast.delta_dist_x;
	}
	if (maze->vector.ray_dir_y < 0)
	{
		maze->raycast.step_y = -1;
		maze->raycast.ray_len_y = (maze->player.pos_y \
- maze->raycast.grid_y) * maze->raycast.delta_dist_y;
	}
	else
	{
		maze->raycast.step_y = 1;
		maze->raycast.ray_len_y = (maze->raycast.grid_y + 1.0 \
- maze->player.pos_y) * maze->raycast.delta_dist_y;
	}
}

void	distance_between_intersections(t_maze *maze)
{
	if (maze->vector.ray_dir_x == 0)
		maze->raycast.delta_dist_x = 1e30;
	else
		maze->raycast.delta_dist_x = fabs(1 / maze->vector.ray_dir_x);
	if (maze->vector.ray_dir_y == 0)
		maze->raycast.delta_dist_y = 1e30;
	else
		maze->raycast.delta_dist_y = fabs(1 / maze->vector.ray_dir_y);
}

void	ray_direction(t_maze *maze, int x)
{
	maze->raycast.camera_x = 2 * x / (double)WIDTH - 1;
	maze->vector.ray_dir_x = maze->vector.dir_x + maze->vector.plane_x \
* maze->raycast.camera_x;
	maze->vector.ray_dir_y = maze->vector.dir_y + maze->vector.plane_y \
* maze->raycast.camera_x;
}

void	find_wall(t_maze *maze)
{
	bool	wall;

	wall = false;
	while (wall == false)
	{
		if (maze->raycast.ray_len_x < maze->raycast.ray_len_y)
		{
			maze->raycast.ray_len_x += maze->raycast.delta_dist_x;
			maze->raycast.grid_x += maze->raycast.step_x;
			maze->raycast.side = 0;
		}
		else
		{
			maze->raycast.ray_len_y += maze->raycast.delta_dist_y;
			maze->raycast.grid_y += maze->raycast.step_y;
			maze->raycast.side = 1;
		}
		if (maze->map.parsed.map_data[maze->raycast.grid_y]\
[maze->raycast.grid_x] == '1')
			wall = true;
	}
}

void	raycasting(t_maze *maze)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ray_direction(maze, x);
		distance_between_intersections(maze);
		initial_ray_length(maze);
		find_wall(maze);
		if (maze->raycast.side == 0)
			maze->raycast.distance_to_wall = maze->raycast.ray_len_x \
- maze->raycast.delta_dist_x;
		else
			maze->raycast.distance_to_wall = maze->raycast.ray_len_y \
- maze->raycast.delta_dist_y;
		maze->draw.line_height = (int)(HEIGHT / maze->raycast.distance_to_wall);
		draw_line(maze, x);
		x++;
	}
}
