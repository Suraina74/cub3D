/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/20 13:58:18 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_texture(t_maze *maze)
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;

	north = mlx_load_png(maze->map.parsed.NO);
	if (!north)
		return (ft_putendl_fd("North texture error", 2), 1);
	south = mlx_load_png(maze->map.parsed.SO);
	if (!south)
		return (ft_putendl_fd("South texture error", 2), 1);
	east = mlx_load_png(maze->map.parsed.EA);
	if (!east)
		return (ft_putendl_fd("East texture error", 2), 1);
	west = mlx_load_png(maze->map.parsed.WE);
	if (!west)
		return (ft_putendl_fd("West texture error", 2), 1);
	return (0);
}

static void fill_texture(char *s, char *dir, char **d)
{
	char **get_texture;
	
	if (ft_strncmp(s, dir, 2) == 0)
	{
		get_texture = ft_split(s, ' ');
		*d = get_texture[1];
	}
}

int	fill_metadata(t_maze *maze)
{
	int		i;
	char	*floor;
	char	*ceiling;

	i = 0;
	while (maze->map.cpy_map[i])
	{
		floor = ft_strchr(maze->map.cpy_map[i], 'F');
		ceiling = ft_strchr(maze->map.cpy_map[i], 'C');
		if (floor)
		{
			maze->map.parsed.F = split_rgb(floor);
			if (fill_rgb(maze->map.parsed.F) == NULL)
				return (1);
			maze->map.parsed.rgb_floor = fill_rgb(maze->map.parsed.F);
		}
		if (ceiling)
		{
			maze->map.parsed.C = split_rgb(ceiling);
			if (fill_rgb(maze->map.parsed.C) == NULL)
				return (1);
			maze->map.parsed.rgb_ceiling = fill_rgb(maze->map.parsed.C);
		}
		if (ft_strncmp(maze->map.cpy_map[i], "NO", 2) || ft_strncmp(maze->map.cpy_map[i], "SO", 2) \
			|| ft_strncmp(maze->map.cpy_map[i], "EA", 2) || ft_strncmp(maze->map.cpy_map[i], "WE", 2))
		{
			fill_texture(maze->map.cpy_map[i], "NO", &maze->map.parsed.NO);
			fill_texture(maze->map.cpy_map[i], "SO", &maze->map.parsed.SO);
			fill_texture(maze->map.cpy_map[i], "WE", &maze->map.parsed.WE);
			fill_texture(maze->map.cpy_map[i], "EA", &maze->map.parsed.EA);
		}
		else
			return (ft_putendl_fd("Error: Texture missing", 2), 1);
		i++;
	}
	if (maze->map.parsed.rgb_floor == NULL || maze->map.parsed.rgb_ceiling == NULL || maze->map.parsed.NO == NULL || maze->map.parsed.SO == NULL || maze->map.parsed.EA == NULL || maze->map.parsed.WE == NULL)
		return (ft_putendl_fd("Texture or color missing", 2), 1);
	if (validate_texture(maze))
		return (1);
	if (validate_rgb(maze))
		return (1);
	return (0);
}


int	cpy_map_size(t_maze *maze)
{
	int			fd;
	char		*line;

	maze->map.height = 0;
	fd = open(maze->filename, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Map doesn't exist", 2), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		maze->map.cpy_width = ft_strlen(line);
		maze->map.cpy_height++;
	}
	maze->map.cpy_map = malloc((maze->map.cpy_width * maze->map.cpy_height) * sizeof(char *));
	if (!maze->map.cpy_map)
		return (close(fd), 1);
	if (cpy_of_map(maze))
		return (free(maze->map.cpy_map), 1);
	if (fill_metadata(maze))
		return (free(maze->map.cpy_map), 1);
	return (0);
}
