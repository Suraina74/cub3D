/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_playable.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 09:35:36 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/20 15:31:33 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int is_metadata(t_maze *maze)
{
	if (maze->map.parsed.rgb_floor || maze->map.parsed.rgb_ceiling || maze->map.parsed.NO || maze->map.parsed.SO || maze->map.parsed.EA || maze->map.parsed.WE)
		return (1);
	return (0);
}

int	valid_map_character(t_maze *maze)
{
	int	row;
	int	col;

	col = 0;
	int flag = 0;
	//this needs tobe a valid skip meta data function
	while (maze->map.cpy_map[col])
	{
		if (is_metadata(maze))
			flag++; //amt o cols to skip
		col++;
	}
	col = 8;
	while (maze->map.cpy_map[col])
	{
		row = 0;
		while (maze->map.cpy_map[col][row])
		{
			if (maze->map.cpy_map[col][row] == '0' || maze->map.cpy_map[col][row] == '1' || 
				maze->map.cpy_map[col][row] == 'E' || maze->map.cpy_map[col][row] == 'N' ||
				maze->map.cpy_map[col][row] == 'S' || maze->map.cpy_map[col][row] == 'W' ||
				maze->map.cpy_map[col][row] == ' ')
				printf("valid map thing\n");
			else 
				printf("this ends here\n");
			printf(" %c ", maze->map.cpy_map[col][row]);
			row++;
		}
		printf("\n");
		col++;
	}
	if(maze->map.parsed.player == 0)
		printf("no player found\n");
	return (0);
}

// int map_size()
// {
// }

// int get_playable_map(t_maze_map *map)
// {
// 	if (valid_map_character(map))
// 		return (1);
// 	return (0);
// }
