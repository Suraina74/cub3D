/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/07 13:23:01 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//cpy map to a 2d array
//loop over map to skip metadata
//fill metadata struct
//find width and height of the map

// int skip_metadata(t_parse *data, t_maze_map *map)
// {
// 	if (map->map != data->C || map->map != data->F || map->map != data->NO \
// 		|| map->map != data->SO || map->map != data->WE || map->map != data->EA)
// 	{
// 		get_map_size(map);
// 	}
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
		printf("line: %s", line);
		map->width = ft_strlen(line);
		map->height++;
	}
	map->map = malloc((map->width * map->height) * sizeof(char));
	if (!map->map)
		return (close(fd), 1);
	return (0);
}

// int cpy_map()
// {

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