/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/13 10:26:11 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//cpy map to a 1d array -> done ✅
//what makes a valid map?
	//if the meta data is the first thing and the map comes second
	//if the NO SO EA WE C F textures/colors are at the top of the map
	//if there ARE NO SO WE EA textures at the top
	//if all the textures are there then fill metadata struct ✅
	//theres ONLY spaces in the map NO tabs
	//if the map used 1s and 0s and a N E W S point for the player start
//loop over map to skip metadata
//once we are SURE that the map is validated we put the map into a 2d array
//find width and height of the actual playable map
//split 1d array map into cols/rows and add it into map->map from map->cpy_map
//change gnl to not remove \n

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
	return (0);
}

int	valid_character(t_maze_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->cpy_map[i][j] == ' ')
		j++;
	while (map->cpy_map[i])
	{
		if (map->cpy_map[i][j] == '1' || map->cpy_map[i][j] == '0' \
		|| map->cpy_map[i][j] == ' ' || map->cpy_map[i][j] == 'N' \
		|| map->cpy_map[i][j] == 'S' || map->cpy_map[i][j] == 'W' \
		|| map->cpy_map[i][j] == 'E')
			printf("valid map\n");
		else
			return (ft_putendl_fd("Error: Invalid character in map", 2), 1);
		i++;
	}
	return (0);
}

static void fill_texture(char *s, char *texture, char **d)
{
	char **get_texture;

	if (ft_strncmp(s, texture, 2) == 0)
	{
		get_texture = ft_split(s, ' ');
		*d = get_texture[1];	
	}
}

int	fill_metadata(t_maze_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->cpy_map[i][j] == ' ')
		j++;
	while (map->cpy_map[i])
	{
		if (ft_strncmp(map->cpy_map[i], "NO", 2) ||ft_strncmp(map->cpy_map[i], "SO", 2) \
			|| ft_strncmp(map->cpy_map[i], "EA", 2) || ft_strncmp(map->cpy_map[i], "WE", 2))
			{
				fill_texture(map->cpy_map[i], "NO", &map->parsed.NO);
				fill_texture(map->cpy_map[i], "SO", &map->parsed.SO);
				fill_texture(map->cpy_map[i], "WE", &map->parsed.WE);
				fill_texture(map->cpy_map[i], "EA", &map->parsed.EA);
			}
		else
			return (ft_putendl_fd("Error: Texture missing", 2), 1);
		i++;
	}
		printf("in struct NO: %s", map->parsed.NO);
		printf("in struct SO: %s", map->parsed.SO);
		printf("in struct WE: %s", map->parsed.WE);
		printf("in struct EA: %s", map->parsed.EA);
	return (0);
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
		map->cpy_width = ft_strlen(line);
		map->cpy_height++;
	}
	map->cpy_map = malloc((map->cpy_width * map->cpy_height) * sizeof(char *));
	if (!map->cpy_map)
		return (close(fd), 1);
	if (cpy_map(map))
		return (1);
	if (fill_metadata(map))
		return (1);

	return (0);
}

// int validate_rgb(t_maze_map *map)
// {
// 	ft_atoi(map->parsed.F[0]);
// 	if (map->parsed.F[0] > 255 || map->parsed.F[0] < 0)
// 		return (ft_putendl_fd("RGB value not in 0-255 range", 2), 1);
// }

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
