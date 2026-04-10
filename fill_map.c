/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 10:56:43 by schabboe          #+#    #+#             */
/*   Updated: 2026/04/10 18:01:35 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_top(char *line)
{
	char	*floor;
	char	*ceiling;

	floor = ft_strchr(line, 'F');
	ceiling = ft_strchr(line, 'C');
	if (floor || ceiling || ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || line[0] == '\n')
		return (1);
	return (0);
}

int	count_rows(t_maze *maze)
{
	char	*line;
	int		fd;

	maze->map.height = 0;
	line = NULL;
	fd = open(maze->filename, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Map could not open", 2), FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (skip_top(line) == 0)
			maze->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (SUCCESS);
}

int	alloc_rows(t_maze *maze)
{
	if (count_rows(maze) == 1)
		return (FAILURE);
	if (maze->map.height == 0)
		return (ft_putendl_fd("No map!", 2), FAILURE);
	maze->map.parsed.map_data = malloc((maze->map.height + 1) * sizeof(char *));
	if (maze->map.parsed.map_data == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	fill_rows(t_maze *maze, char *map_row, int *i)
{
	maze->map.parsed.map_data[*i] = ft_strdup(map_row);
	if (maze->map.parsed.map_data[*i] == NULL)
		return (FAILURE);
	if (*i == (maze->map.height - 1))
		maze->map.parsed.map_data[*i + 1] = NULL;
	return (SUCCESS);
}
