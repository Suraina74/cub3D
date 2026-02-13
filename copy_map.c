/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/07 12:50:38 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/13 13:02:39 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cpy_of_map(t_maze *maze)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(maze->filename, O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		maze->map.cpy_map[i] = line;
		i++;
	}
	return (0);
}
