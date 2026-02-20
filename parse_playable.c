/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_playable.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 09:35:36 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/20 18:50:24 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_metadata(t_maze *maze, int *cols_skip)
{
	int row;
	int col;

	col = 0;
	while (maze->map.cpy_map[col])
	{
		row = 0;
		if ((ft_strncmp(maze->map.cpy_map[col], "NO", 2) == 0) || 
			(ft_strncmp(maze->map.cpy_map[col], "SO", 2) == 0) || 
			(ft_strncmp(maze->map.cpy_map[col], "WE", 2) == 0) ||
			(ft_strncmp(maze->map.cpy_map[col], "EA", 2) == 0) || 
			maze->map.cpy_map[col][row] == '\n' || 
			maze->map.cpy_map[col][row] == 'C' || 
			maze->map.cpy_map[col][row] == 'F')
			(*cols_skip)++;
		while (maze->map.cpy_map[col][row])
		{
			row++;
		}
		col++;
	}
	return (0);
}

int	valid_map_character(t_maze *maze)
{
	int	row;
	int	col;
	char c;

	col = 0;
	if (is_metadata(maze, &col))
		return (1);
	while (maze->map.cpy_map[col])
	{
		row = 0;
		c = maze->map.cpy_map[col][row];
		while (maze->map.cpy_map[col][row])
		{
			printf("%c", maze->map.cpy_map[col][row]);
			if (c == '0' || c == '1' || c == 'E' || c == 'N' || c == 'S' || c == 'W' || c == ' ' || c == '\n')
				row++;
			else
				return (ft_putendl_fd("Invalid character in map", 2), 1);	
		}
		col++;
	}
	if (maze->map.parsed.player == 0)
		printf("no player found\n");
	return (0);
}


//check if map is enclosed correctly 