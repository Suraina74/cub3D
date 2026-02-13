/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:50:38 by ksoedama          #+#    #+#             */
/*   Updated: 2026/02/13 15:57:04 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cpy_of_map(t_maze *maze)
{
	int		i;
	int		j;
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
	j = 0;
	while (line[j])
	{
		if (line[j] == '\n')
			line[j] = '\0';
		j++;
	}
		maze->map.cpy_map[i] = line;
		i++;
	}
	return (0);
}
