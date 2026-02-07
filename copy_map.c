/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/07 12:50:38 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/07 14:25:29 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cpy_map(t_maze_map *map)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map->cpy_map[i] = line;
		// printf("%s", map->cpy_map[i]);
	}
	map->cpy_map = NULL;
	return (0);
}
