/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/23 13:58:29 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/04/09 21:28:53 by ksoedama      ########   odam.nl         */
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
		if (ft_strlen(get_texture[0]) != 2)
			return (ft_d_free(get_texture), ft_putendl_fd("Texture error", 2), 1);
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
			return (free(maze->map.parsed.map_data), ft_putendl_fd("Duplicate N metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "SO", 2) == 0)
	{
		if (maze->map.parsed.so != NULL)
			return (free(maze->map.parsed.map_data), ft_putendl_fd("Duplicate S metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "WE", 2) == 0)
	{
		if (maze->map.parsed.we != NULL)
			return (free(maze->map.parsed.map_data), ft_putendl_fd("Duplicate W metadata", 2), FAILURE);
	}
	if (ft_strncmp(metadata, "EA", 2) == 0)
	{
		if (maze->map.parsed.ea != NULL)
			return (free(maze->map.parsed.map_data), ft_putendl_fd("Duplicate E metadata", 2), FAILURE);
	}
	return (SUCCESS);
}

static int	fill_metadata(t_maze *maze, char *metadata, int *i)
{
	int		*arr;

	if (ft_strncmp(metadata, "F", 1) == 0)
	{
		if (maze->map.parsed.f != NULL)
			return (free_c_f(maze), free(maze->map.parsed.map_data), ft_putendl_fd("Duplicate F metadata", 2), FAILURE);
		maze->map.parsed.f = split_rgb(metadata);
		if (maze->map.parsed.f == NULL)
			return (free(maze->map.parsed.map_data), ft_putendl_fd("RGB value could not be loaded", 2), FAILURE);
		if (maze->map.parsed.f == NULL)
			return(FAILURE);
		if (fill_rgb(maze->map.parsed.f, &arr) == 1)
			return(free_c_f(maze), free(maze->map.parsed.map_data), FAILURE);
		maze->map.parsed.rgb_floor = arr;
	}
	else if (ft_strncmp(metadata, "C", 1) == 0)
	{
		if (maze->map.parsed.c != NULL)
			return (free_c_f(maze), free(maze->map.parsed.map_data), ft_putendl_fd("Duplicate C metadata", 2), FAILURE);
		maze->map.parsed.c = split_rgb(metadata);
		if (maze->map.parsed.c == NULL)
			return (free(maze->map.parsed.map_data), ft_putendl_fd("RGB value could not be loaded", 2), FAILURE);
		if (fill_rgb(maze->map.parsed.c, &arr) == 1)
			return(free_c_f(maze), free(maze->map.parsed.map_data), FAILURE);
		maze->map.parsed.rgb_ceiling = arr;
	}
	else if (ft_strncmp(metadata, "NO", 2) == 0
		|| ft_strncmp(metadata, "SO", 2) == 0
		|| ft_strncmp(metadata, "EA", 2) == 0
		|| ft_strncmp(metadata, "WE", 2) == 0)
	{
		if (check_if_filled(maze, metadata))
			return (FAILURE);
		if (fill_texture(metadata, "NO", &maze->map.parsed.no))
			return (free(maze->map.parsed.map_data), free_rgb(maze), 1);
		if (fill_texture(metadata, "SO", &maze->map.parsed.so))
			return (free(maze->map.parsed.map_data), free_rgb(maze), 1);
		if (fill_texture(metadata, "WE", &maze->map.parsed.we))
			return (free(maze->map.parsed.map_data), free_rgb(maze), 1);
		if (fill_texture(metadata, "EA", &maze->map.parsed.ea))
			return (free(maze->map.parsed.map_data), free_rgb(maze), 1);
	}
	else if (metadata[0] != '\n' && metadata[0] != '\0')
	{
		if (maze->map.parsed.f == NULL || maze->map.parsed.c == NULL
		|| maze->map.parsed.no == NULL || maze->map.parsed.so == NULL
		|| maze->map.parsed.ea == NULL || maze->map.parsed.we == NULL)
			return (free(maze->map.parsed.map_data), free_c_f(maze), ft_putendl_fd("Texture or color could not be loaded", 2), 1);
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
	if (validate_texture(maze))
		return (ft_d_free(maze->map.parsed.map_data), free_c_f(maze), free_tex(maze), FAILURE);
	if (validate_rgb(maze))
		return (ft_d_free(maze->map.parsed.map_data), free_c_f(maze), free_tex(maze), FAILURE);
	if (validate_map(maze))
		return (ft_d_free(maze->map.parsed.map_data), free_c_f(maze), free_tex(maze), FAILURE);
	return (SUCCESS);
}
