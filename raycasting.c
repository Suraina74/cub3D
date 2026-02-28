/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/02/24 17:44:52 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycasting(t_maze *maze)
{
    int array[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
    int grid_x = 1;
    int grid_y = 2;
    int pixels_x;
    int pixels_y;
    int i;
    int first_ray;

    // Starting position in pixels (where NOSW is positioned):
    // x_pixels = x_grid * 64 + 32
    // y_pixels = y_grid * 64 + 32
    // So that it starts in the middle of a block of 64 by 64
    pixels_x = grid_x * 64 + 32;
    pixels_y = grid_y * 64 + 32;
    // Degree van eerste ray:
    maze->raycasting.ray_degree = maze->player.viewing_angle - (maze->player.vof / 2);

    // Horizontal intersections:

    // See if angle of the ray is facing upward or downward. Downward if between 0 and 180 degrees and upward if between 180 and 360 degrees.
	// The calculation of the intersection is calculated differently depending on an upward or downward facing ray.

    // Ray is facing up
    if (first_ray >= 180 && first_ray < 360)
    {
        // Find coordinates of first intersection point
        maze->raycasting.pixel_y = floor(pixels_y/64) * (64) - 1;
        maze->raycasting->y_grid_intersect = floor(maze->raycasting.pixel_y / 64);
        maze->raycasting->pixel_x = pixels_x + (pixels_y - maze->raycasting.pixel_y)/tan(maze->raycasting.ray_degree);
        
        // Find Ya
        // Find Xa
        // Check grid at intersection point to see if there is a wall.
        // If there is a wall, stop and calculate the distance.
        // If there is no wall, then go to next intersection point: Xnew=Xold+Xa, and Ynew=Yold+Ya.
    }

    // Ray is facing down
    if (first_ray >= 0 && first_ray < 180)
    {
        // Find first intersection point

        // Find Ya
        // Find Xa
        // Check grid at intersection point to see if there is a wall.
        // If there is a wall, stop and calculate the distance.
        // If there is no wall, then go to next intersection point: Xnew=Xold+Xa, and Ynew=Yold+Ya.
    }

    
    
    // Vertical intersections:
    


    i = 1;
    while (i < WIDTH)
    {
        maze->raycast.ray_degree = first_ray + maze->raycast.angle_increment;
        i++;
    }
}
