/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/24 16:57:51 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/25 12:03:45 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_maze *maze, size_t  x, size_t y)
{
	if (y < 0 || x < 0 || y > maze->map.height || x >= maze->map.width)
		return ;
	maze->map.parsed.map_data[x][y] = '2';
	flood_fill(maze, x, y+1);
	flood_fill(maze, x, y-1);
	flood_fill(maze, x+1, y);
	flood_fill(maze, x-1, y);
}