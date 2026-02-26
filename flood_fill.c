/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/24 16:57:51 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/26 12:43:25 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_maze *maze, int  x, int y)
{
	if (y < 0 || y >= maze->map.width || x < 0 || x >= maze->map.height)
	{
		ft_putendl_fd("Map is not enclosed", 2);
		return ;
	}
	if (maze->map.parsed.map_data[x][y] == ' ')
	{
		ft_putendl_fd("map failure", 2);
		return ;
	}
	if (maze->map.parsed.map_data[x][y] == '-' || maze->map.parsed.map_data[x][y] == '1' )
		return ;
	maze->map.parsed.map_data[x][y] = '-';
	flood_fill(maze, x, y+1);
	flood_fill(maze, x, y-1);
	flood_fill(maze, x+1, y);
	flood_fill(maze, x-1, y);
}