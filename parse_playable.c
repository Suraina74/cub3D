/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_playable.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 09:35:36 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/13 09:38:11 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_character(t_maze_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->cpy_map[i][j] == ' ')
		j++;
	while (map->cpy_map[i])
	{
		if (map->cpy_map[i][j] == '1' || map->cpy_map[i][j] == '0'  || \
			map->cpy_map[i][j] == ' ' || map->cpy_map[i][j] == 'N' || \
			map->cpy_map[i][j] == 'S' || map->cpy_map[i][j] == 'W' || \
			map->cpy_map[i][j] == 'E')
			printf("valid map\n");
		else
			return (ft_putendl_fd("Error: Invalid character in map", 2), 1);
		i++;
	}
	return (0);
}

// int skip_meta_data()
// {
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
