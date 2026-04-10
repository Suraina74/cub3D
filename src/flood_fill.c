/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:57:51 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/10 18:27:24 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
