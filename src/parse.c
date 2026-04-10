/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:58:29 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/10 19:09:52 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_texture(char *s, char *dir, char **d)
{
	char	**get_texture;

	if (ft_strncmp(s, dir, 2) == 0)
	{
		get_texture = ft_split(s, ' ');
		if (!get_texture)
			return (1);
		if (ft_strlen(get_texture[0]) != 2)
			return (ft_d_free(get_texture), \
ft_putendl_fd("Texture error", 2), 1);
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
			return (free(maze->map.parsed.map_data), \
ft_putendl_fd("Duplicate N metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "SO", 2) == 0)
	{
		if (maze->map.parsed.so != NULL)
			return (free(maze->map.parsed.map_data), \
ft_putendl_fd("Duplicate S metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "WE", 2) == 0)
	{
		if (maze->map.parsed.we != NULL)
			return (free(maze->map.parsed.map_data), \
ft_putendl_fd("Duplicate W metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "EA", 2) == 0)
	{
		if (maze->map.parsed.ea != NULL)
			return (free(maze->map.parsed.map_data), \
ft_putendl_fd("Duplicate E metadata", 2), FAILURE);
	}
	return (SUCCESS);
}

static int	fill_metadata(t_maze *maze, char *metadata, int *i)
{
	if (ft_strncmp(metadata, "F", 1) == 0)
	{
		if (fill_metadata_floor(maze, metadata))
			return (FAILURE);
	}
	else if (ft_strncmp(metadata, "C", 1) == 0)
	{
		if (fill_metadata_ceiling(maze, metadata))
			return (FAILURE);
	}
	else if (ft_strncmp(metadata, "NO", 2) == 0
		|| ft_strncmp(metadata, "SO", 2) == 0
		|| ft_strncmp(metadata, "EA", 2) == 0
		|| ft_strncmp(metadata, "WE", 2) == 0)
	{
		if (fill_metadata_tex(maze, metadata) == 1)
			return (FAILURE);
	}
	else if (metadata[0] != '\n' && metadata[0] != '\0')
	{
		if (fill_metadata_map(maze, metadata, i))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	gnl_map(t_maze *maze, int fd)
{
	int		i;
	char	*line;
	char	*metadata;

	i = 0;
	line = NULL;
	metadata = NULL;
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
	return (SUCCESS);
}

int	read_map(t_maze *maze)
{
	int		fd;

	if (alloc_rows(maze) == 1)
		return (FAILURE);
	fd = open(maze->filename, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Map could not open", 2), FAILURE);
	if (gnl_map(maze, fd))
		return (FAILURE);
	close (fd);
	if (validate_texture(maze))
		return (ft_d_free(maze->map.parsed.map_data), \
free_c_f(maze), free_tex(maze), FAILURE);
	if (validate_rgb(maze))
		return (ft_d_free(maze->map.parsed.map_data), \
free_c_f(maze), free_tex(maze), FAILURE);
	if (validate_map(maze))
		return (ft_d_free(maze->map.parsed.map_data), \
free_c_f(maze), free_tex(maze), FAILURE);
	return (SUCCESS);
}
