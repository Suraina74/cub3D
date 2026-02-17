/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:42:35 by schabboe          #+#    #+#             */
/*   Updated: 2026/02/17 13:59:08 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_maze *maze)
{
	maze->player.start_x = 0; // x where player starts in grid, where the NSOW is.
	maze->player.start_y = 0; // y where player starts in grid, where the NSOW is.
	maze->player.viewing_angle = 90; // Depends on whether it starts at N (90), S(270), O(0) or W(180).
	maze->player.vof = 60;
	maze->player.x_pos = 0; // The x position in the grid whenever the player moves.
	maze->player.y_pos = 0; // The y position in the grid whenever the player moves.
}

void	init_projection_plane(t_maze *maze)
{
	maze->projection_plane.width = 320;
	maze->projection_plane.length = 200;
	maze->projection_plane.distance_to_plane = 160 / tan(30); // distance from player to projection plane
}

void    init_raycast_variables(t_maze *maze)
{
    maze->raycast.angle_increment = 60/320;
    maze->raycast.distance_to_wall = 0;
    maze->raycast.ray_degree = 0; // = viewing angle - vof/2
    maze->raycast.x_grid_coordinate = 0;
    maze->raycast.y_grid_coordinate = 0;
    maze->raycast.x_intersect = 0; // x grid coordinate of intersection with wall
    maze->raycast.x_intersect = 0; // y grid coordinate of intersection with wall
}
