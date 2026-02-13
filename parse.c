/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/13 16:06:23 by ksoedama      ########   odam.nl         */
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
		return (ft_putendl_fd("North texture is wrong", 2), 1);
	south = mlx_load_png(maze->map.parsed.SO);
	if (!south)
		return (ft_putendl_fd("South texture is wrong", 2), 1);
	east = mlx_load_png(maze->map.parsed.EA);
	if (!east)
		return (ft_putendl_fd("East texture is wrong", 2), 1);
	west = mlx_load_png(maze->map.parsed.WE);
	if (!west)
		return (ft_putendl_fd("West texture is wrong", 2), 1);

	// mlx_image_t	*img_north = mlx_texture_to_image(maze->mlx, north);
	// mlx_image_t	*img_south = mlx_texture_to_image(maze->mlx, south);
	// mlx_image_t	*img_east = mlx_texture_to_image(maze->mlx, east);
	// mlx_image_t	*img_west = mlx_texture_to_image(maze->mlx, west);
	// if (!img_north || !img_south || !img_east || !img_west)
	// 	return (ft_putendl_fd("Img convert went wrong", 2), 1);
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

int	fill_metadata(t_maze *maze)
{
	int	i;

	i = 0;
	while (maze->map.cpy_map[i])
	{
		if (ft_strncmp(maze->map.cpy_map[i], "NO", 2) || ft_strncmp(maze->map.cpy_map[i], "SO", 2) \
			|| ft_strncmp(maze->map.cpy_map[i], "EA", 2) || ft_strncmp(maze->map.cpy_map[i], "WE", 2))
		{
			fill_texture(maze->map.cpy_map[i], "NO", &maze->map.parsed.NO);
			fill_texture(maze->map.cpy_map[i], "SO", &maze->map.parsed.SO);
			fill_texture(maze->map.cpy_map[i], "WE", &maze->map.parsed.WE);
			fill_texture(maze->map.cpy_map[i], "EA", &maze->map.parsed.EA);
		}
		else if (ft_strchr(maze->map.cpy_map[i], 'F') || ft_strchr(maze->map.cpy_map[i], 'C'))
		{
			char *help = ft_strchr(maze->map.cpy_map[i], 'F');
			printf("heres the floor: %s", help);
		}
		else
			return (ft_putendl_fd("Error: Texture missing", 2), 1);
		i++;
	}
	if (validate_texture(maze))
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
		return (1);
	return (0);
}
