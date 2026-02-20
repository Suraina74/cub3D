/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/07 12:50:38 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/20 18:51:41 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cpy_of_map(t_maze *maze)
{
	int		col;

	int		fd;
	char	*line;

	col = 0;
	fd = open(maze->filename, O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		maze->map.cpy_map[col] = line;
		// j = 0;
		// while (line[j])
		// {
		// 	if (line[j] == '\n')
		// 		line[j] = '\0';
		// 	j++;
		// }
		col++;
	}
	maze->map.cpy_map[col] = NULL;
	return (0);
}
