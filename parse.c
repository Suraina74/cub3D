/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/13 12:43:17 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_texture(t_maze_map *map)
{
	mlx_load_png(map->parsed.NO);
	mlx_load_png(map->parsed.SO);
	mlx_load_png(map->parsed.EA);
	mlx_load_png(map->parsed.WE);
	if (!map->parsed.NO || !map->parsed.SO || !map->parsed.EA \
	|| !map->parsed.WE)
		return (ft_putendl_fd("texture failed", 2), 1);
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

	i = 0;
	while (map->cpy_map[i])
	{
		if (ft_strncmp(map->cpy_map[i], "NO", 2) || ft_strncmp(map->cpy_map[i], "SO", 2) \
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
		// printf("in struct SO: %s", map->parsed.SO);
		// printf("in struct WE: %s", map->parsed.WE);
		// printf("in struct EA: %s", map->parsed.EA);
	if (validate_texture(map))
		return (1);
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
	if (cpy_of_map(map))
		return (free(map->cpy_map), 1);
	if (fill_metadata(map))
		return (1);
	return (0);
}
