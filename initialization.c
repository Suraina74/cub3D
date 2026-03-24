/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:42:35 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/24 14:43:01 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_north_south(t_maze *maze)
{
	// If player is facing up
	if (maze->map.parsed.player == 'N')
	{
		maze->vector.dir_x = 0;
		maze->vector.dir_y = -1;
		maze->vector.plane_x = 0.66;
		maze->vector.plane_y = 0;
	}
	// If player is facing down
	if (maze->map.parsed.player == 'S')
	{
		maze->vector.dir_x = 0;
		maze->vector.dir_y = 1;
		maze->vector.plane_x = -0.66;
		maze->vector.plane_y = 0;
	}
}

void	init_vectors(t_maze *maze)
{
	init_north_south(maze);
	// If player is facing left
	if (maze->map.parsed.player == 'W')
	{
		maze->vector.dir_x = -1;
		maze->vector.dir_y = 0;
		maze->vector.plane_x = 0;
		maze->vector.plane_y = 0.66;
	}
	// If player is facing right
	if (maze->map.parsed.player == 'E')
	{
		maze->vector.dir_x = 1;
		maze->vector.dir_y = 0;
		maze->vector.plane_x = 0;
		maze->vector.plane_y = -0.66;
	}
}
