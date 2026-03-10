/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:58:29 by ksoedama          #+#    #+#             */
/*   Updated: 2026/03/10 20:10:45 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_texture(char *s, char *dir, char **d)
{
	char	**get_texture;

	if (ft_strncmp(s, dir, 2) == 0)
	{
		get_texture = ft_split(s, ' ');
		*d = get_texture[1];
	}
}

static int	fill_map(t_maze *maze, char *metadata, int fd)
{
	size_t	index_end;
	size_t	map_end;
	ssize_t	tmp;
	char	buff[1024];

	ft_strlcpy(buff, metadata, ft_strlen(metadata) + 1);
	map_end = ft_strlcat(buff, "\n", 1024);
	tmp = read(fd, buff + ft_strlen(buff), 1024);
	index_end = map_end + tmp;
	buff[index_end] = '\0';
	maze->map.parsed.map_data = ft_split(buff, '\n');
	if (!maze->map.parsed.map_data)
		return (FAILURE);
	return (SUCCESS);
}

static int	fill_metadata(t_maze *maze, char *metadata,
	int fd, int *track_metadata)
{
	char	*floor;
	char	*ceiling;

	floor = ft_strchr(metadata, 'F');
	ceiling = ft_strchr(metadata, 'C');
	if (floor)
	{
		maze->map.parsed.F = split_rgb(floor);
		if (fill_rgb(maze->map.parsed.F) == NULL)
			return (FAILURE);
		maze->map.parsed.rgb_floor = fill_rgb(maze->map.parsed.F);
		(*track_metadata)++;
	}
	else if (ceiling)
	{
		maze->map.parsed.C = split_rgb(ceiling);
		if (fill_rgb(maze->map.parsed.C) == NULL)
			return (FAILURE);
		maze->map.parsed.rgb_ceiling = fill_rgb(maze->map.parsed.C);
		(*track_metadata)++;
	}
	else if (ft_strncmp(metadata, "NO", 2) == 0
		|| ft_strncmp(metadata, "SO", 2) == 0
		|| ft_strncmp(metadata, "EA", 2) == 0
		|| ft_strncmp(metadata, "WE", 2) == 0)
	{
		fill_texture(metadata, "NO", &maze->map.parsed.NO);
		fill_texture(metadata, "SO", &maze->map.parsed.SO);
		fill_texture(metadata, "WE", &maze->map.parsed.WE);
		fill_texture(metadata, "EA", &maze->map.parsed.EA);
		(*track_metadata)++;
	}
	else if (metadata[0] != '\n' && metadata[0] != '\0')
	{
		if (fill_map(maze, metadata, fd))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	read_map(t_maze *maze)
{
	int		fd;
	char	*metadata;
	char	*line;
	int		track_metadata;

	track_metadata = 0;
	line = NULL;
	metadata = NULL;
	fd = open(maze->filename, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Map doesn't exist", 2), FAILURE);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		metadata = ft_strtrim(line, "\n");
		if (fill_metadata(maze, metadata, fd, &track_metadata))
			return (FAILURE);
		free(line);
	}
	if (maze->map.parsed.F == NULL || maze->map.parsed.C == NULL
		|| maze->map.parsed.NO == NULL || maze->map.parsed.SO == NULL
		|| maze->map.parsed.EA == NULL || maze->map.parsed.WE == NULL)
		return (ft_putendl_fd("Texture or color could not be loaded", 2), 1);
	if (track_metadata != 6)
		return (ft_putendl_fd("Duplicate metadata", 2), 1);
	if (validate_texture(maze))
		return (FAILURE);
	if (validate_rgb(maze))
		return (FAILURE);
	if (validate_map(maze))
		return (FAILURE);
	return (SUCCESS);
}
