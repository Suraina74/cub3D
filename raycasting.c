/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/13 15:55:36 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_line(int side, t_maze *maze, int x)
{
	(void)side;
	uint32_t	draw_start;
	uint32_t	draw_end;
	// int i = 0;
	int y = 0;

	draw_start = HEIGHT /2 - maze->raycast.line_height / 2;
	if(draw_start < 0)
		draw_start = 0;
	draw_end = maze->raycast.line_height  / 2 + HEIGHT / 2;
	// if(draw_end >= HEIGHT)
	// 	draw_end = HEIGHT - 1;

	double step = 1.0 * maze->txtr.north->height /  maze->raycast.line_height;
 	double texPos = (draw_start - HEIGHT / 2 + maze->raycast.line_height / 2) * step;

	mlx_image_t* img = mlx_texture_to_image(maze->mlx, maze->txtr.north);

	int tex_y = 0;
	int tex_x = 0;
	
	uint32_t *get_all_pxls = (uint32_t *)maze->txtr.north->pixels;
	
	y = draw_start;
	while (y < draw_end)
	{
		// uint32_t clr = get_all_pxls[tex_y * maze->txtr.north->width + tex_x];
		uint32_t clr = get_all_pxls[tex_y * maze->txtr.north->height + tex_x];
		mlx_put_pixel(img, x, y, clr);
		y++;
	
	}
	// Hoe te weten waar je een bepaalde muur laat zien:
		// if(side == 0 && maze->vector.ray_dir_x > 0)
		// {
			
		// } //Rechts
		// // Load image East
		// if(side == 1 && maze->vector.ray_dir_y < 0) // Onder
		// // Load image South
		// if(side == 0 && maze->vector.ray_dir_x < 0) // Boven
		// // Load image North
		// if(side == 1 && maze->vector.ray_dir_y < 0) // Links
		// // Load image West
}

void	initial_ray_distance(t_maze *maze)
{
	maze->raycast.grid_x = floor(maze->player.pos_x);
	maze->raycast.grid_y = floor(maze->player.pos_y);
	if (maze->vector.ray_dir_x < 0)
	{
		maze->raycast.step_x = -1;
		maze->raycast.start_to_intersection_x = (maze->player.pos_x - maze->raycast.grid_x) * maze->raycast.delta_dist_x;
	}
	else
	{
		maze->raycast.step_x = 1;
		maze->raycast.start_to_intersection_x = (maze->raycast.grid_x + 1 - maze->player.pos_x) * maze->raycast.delta_dist_x;
	}
	if (maze->vector.ray_dir_y < 0)
	{
		maze->raycast.step_y = -1;
		maze->raycast.start_to_intersection_y = (maze->player.pos_y - maze->raycast.grid_y) * maze->raycast.delta_dist_y;
	}
	else
	{
		maze->raycast.step_y = 1;
		maze->raycast.start_to_intersection_y = (maze->raycast.grid_y + 1 - maze->player.pos_y) * maze->raycast.delta_dist_y;
	}
}

void	distance_between_intersections(t_maze *maze)
{
	if (maze->vector.ray_dir_x == 0)
		maze->vector.ray_dir_x = 1e30;
	if (maze->vector.ray_dir_y == 0)
		maze->vector.ray_dir_y = 1e30;
    maze->raycast.delta_dist_x = fabs(1/maze->vector.ray_dir_x);
    maze->raycast.delta_dist_y = fabs(1/maze->vector.ray_dir_y);
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
	int		x;
	bool	wall;
	int		side;

	x = 0;
	side = 0;
	
	init_vectors(maze);
	while (x < WIDTH)
	{
		ray_direction(maze, x);
		distance_between_intersections(maze);
		initial_ray_distance(maze);
		wall = false;
		// DDA gaat elke x en y intersection langs en kijkt welke dichterbij is.
		// Het gaat dan naar de volgende intersectie (x of y) en kijkt dan weer welke dichterbij is.
		// That’s exactly why it’s often called “DDA for ray-grid traversal”.
		while (wall == false)
		{
			// Als de afstand tot de x intersection kleiner is dan de afstand tot de y intersectie,
			// dan is de x intersectie dichterbij.
			// The smaller ray_distance tells us which grid boundary the ray reaches first.
			if (maze->raycast.start_to_intersection_x < maze->raycast.start_to_intersection_y)
			{
				// add the delta_dist_x to the ray distance, om naar de volgende x intersectie te gaan.
				// Om in de volgende loop instance te kijken of de (nieuwe) x of de y intersectie dichterbij is.
				maze->raycast.start_to_intersection_x += maze->raycast.delta_dist_x;
				// Een x grid line is part of the block to the right of the line
				maze->raycast.grid_x += maze->raycast.step_x;
				side = 0;
			}
			else
			{
				// Een y grid line is part of the block above the line
				maze->raycast.start_to_intersection_y += maze->raycast.delta_dist_y;
				maze->raycast.grid_y += maze->raycast.step_y;
				side = 1;
			}
			if (maze->map.parsed.map_data[maze->raycast.grid_x][maze->raycast.grid_y] == '1')
				wall = true;
		}
		// Als we een muur hebben gevonden dan zijn we 1 delta_dist te ver gegaan.
		// Daarom subtracten om distance to wall te krijgen.
		if (side == 0)
			maze->raycast.distance_to_wall = maze->raycast.start_to_intersection_x - maze->raycast.delta_dist_x;
		else
			maze->raycast.distance_to_wall = maze->raycast.start_to_intersection_y - maze->raycast.delta_dist_y;
		// Close wall -> small distance to wall -> large line_height -> tall wall on screen.
		// Far wall -> large distance to wall -> small line_height -> short wall on screen
		// Line height is in pixels
		maze->raycast.line_height = HEIGHT / maze->raycast.distance_to_wall;
		// Draw line to be drawn with MLX.
		draw_line(side, maze, x);
		x++;
	}
}
