/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/20 17:44:19 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	where_ray_hit_tex(t_maze *maze)
{
	double wall_hit;

	if (maze->raycast.side == 0) // hit a vertical wall. Where on that wall did we hit it?
		wall_hit = maze->player.pos_y + maze->raycast.distance_to_wall * maze->vector.ray_dir_y;
	else // hit a horizontal wall. Where on that wall did we hit it?
		wall_hit = maze->player.pos_x + maze->raycast.distance_to_wall * maze->vector.ray_dir_x;
	wall_hit = wall_hit - floor (wall_hit);
	maze->raycast.txtr_x = wall_hit * TEX_WIDTH;
	// if (maze->raycast.side == 0 && maze->vector.ray_dir_x > 0)
	// 	wall_hit = TEX_WIDTH - wall_hit - 1;
    // if (maze->raycast.side == 1 && maze->vector.ray_dir_y < 0) 
	// 	wall_hit = TEX_WIDTH - wall_hit - 1;
}

// Convert to MLX Color
void	convert_to_mlx_color(t_maze *maze, int tex_y, uint32_t *color)
{
	int	index;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	mlx_texture_t *tex;
	
	tex = NULL;
	if (maze->raycast.side == 0 && maze->vector.ray_dir_x > 0)
		tex = maze->txtr.west;
	else if (maze->raycast.side == 0 && maze->vector.ray_dir_x < 0)
		tex = maze->txtr.east;
	else if (maze->raycast.side == 1 && maze->vector.ray_dir_y > 0)
		tex = maze->txtr.north;
	else if (maze->raycast.side == 1 && maze->vector.ray_dir_y < 0)
		tex = maze->txtr.south;
	index = (tex_y * TEX_WIDTH + maze->raycast.txtr_x) * 4;
	r = tex->pixels[index + 0];
	g = tex->pixels[index + 1];
	b = tex->pixels[index + 2];
	a = tex->pixels[index + 3];
	*color = (r << 24) | (g << 16) | (b << 8) | a;
}

void draw_line(t_maze *maze, int x)
{
	double	draw_start;
	double	draw_end;
	int			tex_y;
	uint32_t	y;
	uint32_t color;

	draw_start = 0;
	draw_end = 0;
	draw_start = HEIGHT / 2 - maze->raycast.line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = maze->raycast.line_height  / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	double step = 1.0 * TEX_HEIGHT /  maze->raycast.line_height;
 	double tex_pos = (draw_start - HEIGHT / 2 + maze->raycast.line_height / 2) * step;
	where_ray_hit_tex(maze);
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		convert_to_mlx_color(maze, tex_y, &color);
		tex_pos += step;
		mlx_put_pixel(maze->big_img, x, y, color);
		y++;
	}
}

void	initial_ray_distance(t_maze *maze)
{
	maze->raycast.grid_x = (int)maze->player.pos_x;
	maze->raycast.grid_y = (int)maze->player.pos_y;
	if (maze->vector.ray_dir_x < 0)
	{
		maze->raycast.step_x = -1;
		maze->raycast.start_to_intersection_x = (maze->player.pos_x - maze->raycast.grid_x) * maze->raycast.delta_dist_x;
	}
	else
	{
		maze->raycast.step_x = 1;
		maze->raycast.start_to_intersection_x = (maze->raycast.grid_x + 1.0 - maze->player.pos_x) * maze->raycast.delta_dist_x;
	}
	if (maze->vector.ray_dir_y < 0)
	{
		maze->raycast.step_y = -1;
		maze->raycast.start_to_intersection_y = (maze->player.pos_y - maze->raycast.grid_y) * maze->raycast.delta_dist_y;
	}
	else
	{
		maze->raycast.step_y = 1;
		maze->raycast.start_to_intersection_y = (maze->raycast.grid_y + 1.0 - maze->player.pos_y) * maze->raycast.delta_dist_y;
	}
}

void	distance_between_intersections(t_maze *maze)
{
	if (maze->vector.ray_dir_x == 0)
		maze->vector.ray_dir_x = 1e30;
	else
		maze->raycast.delta_dist_x = fabs(1/maze->vector.ray_dir_x);
	if (maze->vector.ray_dir_y == 0)
		maze->vector.ray_dir_y = 1e30;
	else
		maze->raycast.delta_dist_y = fabs(1/maze->vector.ray_dir_y);
   
}

void	ray_direction(t_maze *maze, int x)
{
	maze->raycast.camera_x = 2 * x / (double)WIDTH - 1;
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
	double	l_h;

	x = 0;
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
				maze->raycast.side = 0; // hit a vertical grid line
			}
			else
			{
				maze->raycast.start_to_intersection_y += maze->raycast.delta_dist_y;
				// Een y grid line is part of the block above the line
				maze->raycast.grid_y += maze->raycast.step_y;
				maze->raycast.side = 1; // hit a horizontal grid line
			}
			if (maze->map.parsed.map_data[maze->raycast.grid_x][maze->raycast.grid_y] == '1')
				wall = true;
		}
		// Als we een muur hebben gevonden dan zijn we 1 delta_dist te ver gegaan.
		// Daarom subtracten om distance to wall te krijgen.
		if (maze->raycast.side == 0)
			maze->raycast.distance_to_wall = maze->raycast.start_to_intersection_x - maze->raycast.delta_dist_x;
		else
			maze->raycast.distance_to_wall = maze->raycast.start_to_intersection_y - maze->raycast.delta_dist_y;
		// Close wall -> small distance to wall -> large line_height -> tall wall on screen.
		// Far wall -> large distance to wall -> small line_height -> short wall on screen
		// Line height is in pixels
		l_h = HEIGHT / maze->raycast.distance_to_wall;
		maze->raycast.line_height = (int)l_h;
		// Draw line to be drawn with MLX.
		draw_line(maze, x);
		x++;
	}
}
