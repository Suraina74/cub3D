/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialization.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/17 13:42:35 by schabboe      #+#    #+#                 */
/*   Updated: 2026/02/26 14:44:06 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_maze *maze)
{
	// maze->player.start_grid_x = 0; // x where player starts in grid, where the NSOW is.
	// maze->player.start_grid_y = 0; // y where player starts in grid, where the NSOW is.
	// maze->player.start_pixel_x = 0; // x where player starts in pixels/units, where the NSOW is.
	// maze->player.start_pixel_y = 0; // y where player starts in pixels/units, where the NSOW is.
	maze->player.viewing_angle = 90; // Depends on whether it starts at N (90), S(270), O(0) or W(180).
	maze->player.vof = 60;
	maze->player.height = 64/2;
	maze->player.grid_pos_x = 0; // The x position in the grid where the player is.
	maze->player.grid_pos_y = 0; // The y position in the grid where the player is.
	maze->player.pixel_pos_x = 0; // The x position in pixels/units where the player is and the start pos of a ray.
	maze->player.pixel_pos_y = 0; // The y position in pixels/units where the player is and the start pos of a ray.
}

void	init_projection_plane(t_maze *maze)
{
	// maze->projection_plane.width = 320; // Means 320 rays to cast.
	// maze->projection_plane.length = 200;
	maze->projection_plane.distance_to_plane = 160 / tan(30); // distance from player to projection plane
}

void    init_raycast_variables(t_maze *maze)
{
	// Raycasting is done to find walls by checking intersections with horizontal grid lines and intersections with vertical grid lines separately.
	// And if a wall is found on an intersection, the closer distance (between horizontal and vertical) to the intersection point is chosen.
	
    maze->raycast.ray_degree = 0; // degree of most left ray = viewing angle - vof/2
	
    maze->raycast.angle_increment = 60/320; // ray degree wordt dan, ray degree + angle increment.
    maze->raycast.distance_to_wall = 0; // The distance is in units/pixels
    maze->raycast.pixel_x = 0; // x pixel coordinate where the player is at the moment.
    maze->raycast.pixel_y = 0; // y pixel coordinate where the player is at the moment.
    maze->raycast.x_grid_intersect = 0; // x coordinate of intersection with grid
    maze->raycast.x_grid_intersect = 0; // y coordinate of intersection with grid
}
