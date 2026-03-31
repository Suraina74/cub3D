/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/24 16:57:51 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/03/06 17:05:30 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(t_maze *maze, int row, int col)
{
	if (row < 0 || row >= maze->map.height || col < 0
		|| col >= (int)ft_strlen(maze->map.parsed.map_data[row]))
		return (FAILURE);
	if (maze->map.parsed.map_data[row][col] == ' ')
		return (FAILURE);
	if (maze->map.parsed.map_data[row][col] == '-'
		|| maze->map.parsed.map_data[row][col] == '1' )
		return (SUCCESS);
	maze->map.parsed.map_data[row][col] = '-';
	if (flood_fill(maze, row, col +1) || flood_fill(maze, row, col -1)
		|| flood_fill(maze, row +1, col) || flood_fill(maze, row -1, col))
		return (FAILURE);
	return (SUCCESS);
}
