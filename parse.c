/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:58:29 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/04 15:58:59 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int fill_texture(char *s, char *dir, char **d)
{
	char	**get_texture;

	if (ft_strncmp(s, dir, 2) == 0)
	{
		get_texture = ft_split(s, ' ');
		if (!get_texture)
			return (1);
		*d = get_texture[1];
		free(get_texture[0]);
		free(get_texture);
	}
	return (0);
}

int	check_if_filled(t_maze *maze, char *metadata)
{
	if (ft_strncmp(metadata, "NO", 2) == 0)
	{
		if (maze->map.parsed.no != NULL)
			return (ft_putendl_fd("Duplicate N metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "SO", 2) == 0)
	{
		if (maze->map.parsed.so != NULL)
			return (ft_putendl_fd("Duplicate S metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "WE", 2) == 0)
	{
		if (maze->map.parsed.we != NULL)
			return (ft_putendl_fd("Duplicate W metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "EA", 2) == 0)
	{
		if (maze->map.parsed.ea != NULL)
			return (ft_putendl_fd("Duplicate E metadata", 2), FAILURE);
	}
	return (SUCCESS);
}

static int	fill_metadata(t_maze *maze, char *metadata, int *i)
{
	char	*floor;
	char	*ceiling;
	
	floor = ft_strchr(metadata, 'F');
	ceiling = ft_strchr(metadata, 'C');
	if (floor)
	{
		if (maze->map.parsed.f != NULL)
			return (ft_putendl_fd("Duplicate F metadata", 2), FAILURE);
		maze->map.parsed.f = split_rgb(floor);
		if (maze->map.parsed.f == NULL && floor != NULL)
			return (ft_putendl_fd("Missing RGB Value", 2), FAILURE);
		if (maze->map.parsed.f == NULL)
			return(FAILURE);
		maze->map.parsed.rgb_floor = fill_rgb(maze->map.parsed.f);
		if (maze->map.parsed.rgb_floor == NULL)
			return (FAILURE);
	}
	else if (ceiling)
	{
		if (maze->map.parsed.c != NULL)
			return (ft_putendl_fd("Duplicate C metadata", 2), FAILURE);
		maze->map.parsed.c = split_rgb(ceiling);
		if (maze->map.parsed.c == NULL)
			return (1);
		maze->map.parsed.rgb_ceiling = fill_rgb(maze->map.parsed.c);
		if (maze->map.parsed.rgb_ceiling == NULL)
			return (FAILURE);
	}
	else if (ft_strncmp(metadata, "NO", 2) == 0
		|| ft_strncmp(metadata, "SO", 2) == 0
		|| ft_strncmp(metadata, "EA", 2) == 0
		|| ft_strncmp(metadata, "WE", 2) == 0)
	{
		if (check_if_filled(maze, metadata))
			return (FAILURE);
		if (fill_texture(metadata, "NO", &maze->map.parsed.no))
			return (free_rgb(maze), 1);
		if (fill_texture(metadata, "SO", &maze->map.parsed.so))
			return (free_rgb(maze), 1);
		if (fill_texture(metadata, "WE", &maze->map.parsed.we))
			return (free_rgb(maze), 1);
		if (fill_texture(metadata, "EA", &maze->map.parsed.ea))
			return (free_rgb(maze), 1);
	}
	else if (metadata[0] != '\n' && metadata[0] != '\0')
	{
		if (fill_rows(maze, metadata, i) == 1)
			return (FAILURE);
		(*i)++;
	}
	return (SUCCESS);
}

int	read_map(t_maze *maze)
{
	int		fd;
	char	*metadata;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	metadata = NULL;
	if (alloc_rows(maze) == 1)
		return (FAILURE);
	fd = open(maze->filename, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Map could not open", 2), FAILURE);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		metadata = ft_strtrim(line, "\n");
		if (!metadata)
			return (free(line), FAILURE);
		if (fill_metadata(maze, metadata, &i))
			return (free_tex(maze), free(line), free(metadata), FAILURE);
		free(metadata);
		free(line);
	}
	close (fd);
	if (maze->map.parsed.f == NULL || maze->map.parsed.c == NULL
		|| maze->map.parsed.no == NULL || maze->map.parsed.so == NULL
		|| maze->map.parsed.ea == NULL || maze->map.parsed.we == NULL)
		return (ft_putendl_fd("Texture or color could not be loaded", 2), 1);
	if (validate_texture(maze))
		return (FAILURE);
	if (validate_rgb(maze))
		return (FAILURE);
	if (validate_map(maze))
		return (FAILURE);
	return (SUCCESS);
}
