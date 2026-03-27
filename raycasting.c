/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/27 13:13:24 by schabboe         ###   ########.fr       */
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
		maze->raycast.step_y = 1;
		maze->raycast.ray_len_y = (maze->raycast.grid_y + 1.0 \
- maze->player.pos_y) * maze->raycast.delta_dist_y;
	}
	else
	{
		maze->raycast.step_y = -1;
		maze->raycast.ray_len_y = (maze->player.pos_y \
- maze->raycast.grid_y) * maze->raycast.delta_dist_y;
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

// ray direction = forward direction + horizontal offset
// dir = where the player looks
// plane = sideways direction (camera width)
// cameraX = how far sideways we go
// We multiply by cameraX because it tells how far left or right on the camera plane the ray should be.
// A direction vector just tells which way the ray points.

void	ray_direction(t_maze *maze, int x)
{
	maze->raycast.camera_x = 2 * x / (double)WIDTH - 1;
	maze->vector.ray_dir_x = maze->vector.dir_x + maze->vector.plane_x \
* maze->raycast.camera_x;
	maze->vector.ray_dir_y = maze->vector.dir_y + maze->vector.plane_y \
* maze->raycast.camera_x;
}

// DDA gaat elke x en y intersection langs en kijkt welke dichterbij is.
// Het gaat dan naar de volgende intersectie (x of y) en kijkt dan weer welke dichterbij is.
// Als de afstand tot de x intersection kleiner is dan de afstand tot de y intersectie,
// dan is de x intersectie dichterbij.
// The smaller ray_distance tells us which grid boundary the ray reaches first.
// add the delta_dist_x to the ray distance, om naar de volgende x intersectie te gaan.
// Om in de volgende loop instance te kijken of de (nieuwe) x of de y intersectie dichterbij is.
// Als we een muur hebben gevonden dan zijn we 1 delta_dist te ver gegaan. Daarom subtracten om distance to wall te krijgen.

void	find_wall(t_maze *maze)
{
	bool	wall;

	wall = false;
	while (wall == false)
	{
		if (maze->raycast.ray_len_x < maze->raycast.ray_len_y)
		{
			maze->raycast.ray_len_x += maze->raycast.delta_dist_x;
			maze->raycast.grid_x += maze->raycast.step_x; // Een x grid line is part of the block to the right of the line
			maze->raycast.side = 0; // hit a vertical grid line
		}
		else
		{
			maze->raycast.ray_len_y += maze->raycast.delta_dist_y;
			maze->raycast.grid_y += maze->raycast.step_y; // Een y grid line is part of the block above the line
			maze->raycast.side = 1; // hit a horizontal grid line
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
	init_vectors(maze);
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
