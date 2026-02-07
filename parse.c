/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/07 15:04:03 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//cpy map to a 1d array -> done ✅
//once we are SURE that the map is validated we put the map into a 2d array
//loop over map to skip metadata -> wip
//find width and height of the actual playable map
//split 1d array map into cols/rows and add it into map->map from map->cpy_map
//fill metadata struct and check if it is matches C F NO SO EA WE -> wip
//change gnl to not remove \n

int	fill_metadata(t_maze_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->width)
	{
			if (ft_strncmp(map->cpy_map[i], "NO", 2))
			{
				while (map->cpy_map[i] == ' ')
					i++;
				map->parsed.NO = map->map[i];
			}
			printf("%s\n", map->cpy_map[i]);
		i++;
	}
	printf("%c\n", map->parsed.C);
	return (0);
}

int validate_texture(t_maze_map *map)
{
	int	texture;
	
	texture = open(map->parsed.NO, O_RDONLY);
	if (texture == -1)
		return (ft_putendl_fd("North texture doesn't exist", 2), 1);
	texture = open(map->parsed.SO, O_RDONLY);
	if (texture == -1)
		return (ft_putendl_fd("South texture doesn't exist", 2), 1);
	texture = open(map->parsed.EA, O_RDONLY);
	if (texture == -1)
		return (ft_putendl_fd("East texture doesn't exist", 2), 1);
	texture = open(map->parsed.WE, O_RDONLY);
	if (texture == -1)
		return (ft_putendl_fd("West texture doesn't exist", 2), 1);
}

int validate_rgb(t_maze_map *map)
{
	ft_atoi(map->parsed.F[0]);
	if (map->parsed.F[0] > 255 || map->parsed.F[0] < 0)
		return (ft_putendl_fd("RGB value not in 0-255 range", 2), 1);
}

int	cpy_map_size(t_maze_map *map)
{
	int			fd;
	char		*line;

	map->height = 0;
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Map doesn't exist", 2), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map->width = ft_strlen(line);
		map->height++;
	}
	map->cpy_map = malloc((map->width * map->height) * sizeof(char *));
	if (!map->cpy_map)
		return (close(fd), 1);
	if (cpy_map(map))
		return (1);
	if (fill_metadata(map))
		return (1);
	return (0);
}

// int skip_metadata(t_parse *data, t_maze_map *map)
// {
// 	if (map->map != data->C || map->map != data->F || map->map != data->NO \
// 		|| map->map != data->SO || map->map != data->WE || map->map != data->EA)
// 	{
// 	}
// }


// int get_map_size()
// {
// }

// int get_playable_map()
// {
// }
