/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:09:08 by schabboe          #+#    #+#             */
/*   Updated: 2026/04/10 19:11:11 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_metadata_tex(t_maze *maze, char *metadata)
{
	if (check_if_filled(maze, metadata))
		return (FAILURE);
	if (fill_texture(metadata, "NO", &maze->map.parsed.no))
		return (free(maze->map.parsed.map_data), free_rgb(maze), FAILURE);
	if (fill_texture(metadata, "SO", &maze->map.parsed.so))
		return (free(maze->map.parsed.map_data), free_rgb(maze), FAILURE);
	if (fill_texture(metadata, "WE", &maze->map.parsed.we))
		return (free(maze->map.parsed.map_data), free_rgb(maze), FAILURE);
	if (fill_texture(metadata, "EA", &maze->map.parsed.ea))
		return (free(maze->map.parsed.map_data), free_rgb(maze), FAILURE);
	return (SUCCESS);
}

int	fill_metadata_floor(t_maze *maze, char *metadata)
{
	int		*arr;

	if (maze->map.parsed.f != NULL)
		return (free_c_f(maze), free(maze->map.parsed.map_data), \
ft_putendl_fd("Duplicate F metadata", 2), FAILURE);
	maze->map.parsed.f = split_rgb(metadata);
	if (maze->map.parsed.f == NULL)
		return (free_c_f(maze), free(maze->map.parsed.map_data), \
ft_putendl_fd("RGB value could not be loaded", 2), FAILURE);
	if (maze->map.parsed.f == NULL)
		return (FAILURE);
	if (fill_rgb(maze->map.parsed.f, &arr) == 1)
		return (free_c_f(maze), free(maze->map.parsed.map_data), FAILURE);
	maze->map.parsed.rgb_floor = arr;
	return (SUCCESS);
}

int	fill_metadata_ceiling(t_maze *maze, char *metadata)
{
	int		*arr;

	if (maze->map.parsed.c != NULL)
		return (free_c_f(maze), free(maze->map.parsed.map_data), \
ft_putendl_fd("Duplicate C metadata", 2), FAILURE);
	maze->map.parsed.c = split_rgb(metadata);
	if (maze->map.parsed.c == NULL)
		return (free_c_f(maze), free(maze->map.parsed.map_data), \
ft_putendl_fd("RGB value could not be loaded", 2), FAILURE);
	if (fill_rgb(maze->map.parsed.c, &arr) == 1)
		return (free_c_f(maze), free(maze->map.parsed.map_data), FAILURE);
	maze->map.parsed.rgb_ceiling = arr;
	return (SUCCESS);
}

int	fill_metadata_map(t_maze *maze, char *metadata, int *i)
{
	if (maze->map.parsed.f == NULL || maze->map.parsed.c == NULL
		|| maze->map.parsed.no == NULL || maze->map.parsed.so == NULL
		|| maze->map.parsed.ea == NULL || maze->map.parsed.we == NULL)
		return (free(maze->map.parsed.map_data), free_c_f(maze), \
ft_putendl_fd("Texture or color could not be loaded", 2), 1);
	if (fill_rows(maze, metadata, i) == 1)
		return (FAILURE);
	(*i)++;
	return (SUCCESS);
}
