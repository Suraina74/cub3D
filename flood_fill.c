/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/24 16:57:51 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/26 14:11:00 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(t_maze *maze, int  x, int y)
{
	if (y < 0 || y >= maze->map.width || x < 0 || x >= maze->map.height)
		return (FAILURE);
	if (maze->map.parsed.map_data[x][y] == '-' || maze->map.parsed.map_data[x][y] == '1' )
		return (SUCCESS);
	maze->map.parsed.map_data[x][y] = '-';
	if (flood_fill(maze, x, y+1) || flood_fill(maze, x, y-1)
		|| flood_fill(maze, x+1, y) || flood_fill(maze, x-1, y))
		return (FAILURE);
	return (SUCCESS);
}