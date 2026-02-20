/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:45:20 by schabboe          #+#    #+#             */
/*   Updated: 2026/02/20 18:54:12 by schabboe         ###   ########.fr       */
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
    first_ray = maze->player.viewing_angle - (maze->player.vof / 2);
    // Horizontal intersections:
    
    
    // Vertical intersections:
    


    i = 1;
    while (i < WIDTH)
    {
        maze->raycast.ray_degree = first_ray + maze->raycast.angle_increment;
        i++;
    }
}
