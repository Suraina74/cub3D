/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_playable.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 09:35:36 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/17 13:41:59 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_character(t_maze *maze)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (maze->map.cpy_map[i][j] == ' ')
		j++;
	while (maze->map.cpy_map[i])
	{
		if (maze->map.cpy_map[i][j] == '1' || maze->map.cpy_map[i][j] == '0'  || \
			maze->map.cpy_map[i][j] == ' ' || maze->map.cpy_map[i][j] == 'N' || \
			maze->map.cpy_map[i][j] == 'S' || maze->map.cpy_map[i][j] == 'W' || \
			maze->map.cpy_map[i][j] == 'E')
			printf("valid map\n");
		else
			return (ft_putendl_fd("Error: Invalid character in map", 2), 1);
		i++;
	}
	return (0);
}

// int skip_metadata(t_parse *data, t_maze_map *map)
// {
// 	if (map->map != data->C || map->map != data->F || map->map != data->NO \
// 		|| map->map != data->SO || map->map != data->WE || map->map != data->EA)
// 	{
// 	}
// }

// int map_size()
// {
// }

// int get_playable_map(t_maze_map *map)
// {
// 	if (valid_map_character(map))
// 		return (1);
// 	return (0);
// }
