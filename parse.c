/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/06 15:36:27 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_cpy(t_maze_map *map, char *filename)
{
	int			fd;
	char		*line;
	size_t		count_width;
	size_t		count_height;

	count_width = 0;
	count_height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count_width = ft_strlen(line);
		map->width = count_width;
		count_height++;
	}
	map->height = count_height;
	map->map = malloc((map->width * map->height) * sizeof(char));
	if (!map->map)
	{
		close(fd);
		return (NULL);
	}
}