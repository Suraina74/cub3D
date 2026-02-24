/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 09:35:36 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/24 14:47:55 by ksoedama      ########   odam.nl         */
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

int	valid_map_character(t_maze *maze)
{
	int	row;
	int	col;
	char c;

	col = 0;
	while (maze->map.cpy_map[col])
	{
		row = 0;
		c = maze->map.cpy_map[col][row];
		while (maze->map.cpy_map[col][row])
		{
			printf("%c", maze->map.cpy_map[col][row]);
			if (c == '0' || c == '1' || c == 'E' || c == 'N' || c == 'S' || c == 'W' || c == ' ' || c == '\n')
				row++;
			else
				return (ft_putendl_fd("Invalid character in map", 2), 1);
		}
		col++;
	}
	if (maze->map.parsed.player == 0)
		printf("no player found\n");
	return (0);
}
