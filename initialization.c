/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:42:35 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/06 15:42:55 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vectors(t_maze *maze)
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
	else if (maze->map.parsed.player == 'S')
	{
		maze->vector.dir_x = 0;
		maze->vector.dir_y = 1;
		maze->vector.plane_x = -0.66;
		maze->vector.plane_y = 0;
	}
	// If player is facing left
	else if (maze->map.parsed.player == 'W')
	{
		maze->vector.dir_x = -1;
		maze->vector.dir_y = 0;
		maze->vector.plane_x = 0;
		maze->vector.plane_y = 0.66;
	}
	// If player is facing right
	else if (maze->map.parsed.player == 'O')
	{
		maze->vector.dir_x = 1;
		maze->vector.dir_y = 0;
		maze->vector.plane_x = 0;
		maze->vector.plane_y = -0.66;
	}
}
