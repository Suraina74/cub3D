/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/07 14:25:06 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//cpy map to a 2d array -> done
//fill metadata struct and check if it is matches C F NO SO EA WE
//loop over map to skip metadata -> wip
//find width and height of the map
//change gnl

// int	fill_metadata(t_maze_map *map, t_parse *parsed)
// {
// 	size_t i = 0;
// 	size_t j = 0;

// 	while (i < ft_strlen(map->map[i]))
// 	{
// 		j = 0;
// 		// while (j < map->map[i][j])
// 		// {
// 			if (map->map[i][j] == 'C')
// 				parsed.C = map->map[i][j];
// 			// j++;
// 		// }
// 		i++;
// 		printf("%c\n", parsed->C);
// 	}
// 	return (0);
// }

int	get_map_size(t_maze_map *map)
{
	int			fd;
	char		*line;

	map->height = 0;
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map->width = ft_strlen(line);
		map->height++;
	}
	map->map = malloc((map->width * map->height) * sizeof(char *));
	if (!map->map)
		return (close(fd), 1);
	if (cpy_map(map))
		return (1);
	// if (fill_metadata(map))
	// 	return (1);
	return (0);
}

// int skip_metadata(t_parse *data, t_maze_map *map)
// {
// 	if (map->map != data->C || map->map != data->F || map->map != data->NO \
// 		|| map->map != data->SO || map->map != data->WE || map->map != data->EA)
// 	{
// 		get_map_size(map);
// 	}
// }

// int check_map(t_maze_map *map)
// {
// 	int i = 0;
// 	while (i < map->height)
// 	{
// 		int j = 0;
// 		while (j < map->width)
// 		{
// 			map->map[0][0] = j;
// 		}
// 		i++;
// 	}
// }