/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:35:36 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/10 17:39:21 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_texture(t_maze *maze)
{
	maze->txtr.north = mlx_load_png(maze->map.parsed.no);
	if (!maze->txtr.north)
		return (ft_putendl_fd("North texture error", 2), FAILURE);
	maze->txtr.south = mlx_load_png(maze->map.parsed.so);
	if (!maze->txtr.south)
		return (ft_putendl_fd("South texture error", 2), FAILURE);
	maze->txtr.east = mlx_load_png(maze->map.parsed.ea);
	if (!maze->txtr.east)
		return (ft_putendl_fd("East texture error", 2), FAILURE);
	maze->txtr.west = mlx_load_png(maze->map.parsed.we);
	if (!maze->txtr.west)
		return (ft_putendl_fd("East texture error", 2), FAILURE);
	return (SUCCESS);
}

static int	inner_valid_map(t_maze *maze, int *col, int *row, int *p_cnt)
{
	char	c;

	while (maze->map.parsed.map_data[*row][*col])
	{
		c = maze->map.parsed.map_data[*row][*col];
		if (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'W'
			|| c == 'S' || c == ' ' || c == '\n' || 'c' == '\0')
		{
			if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
			{
				maze->map.parsed.player = c;
				maze->player.pos_x = *col + 0.5;
				maze->player.pos_y = *row + 0.5;
				(*p_cnt)++;
			}
			(*col)++;
		}
		else
			return (ft_putendl_fd("Invalid character in map", 2), FAILURE);
	}
	return (SUCCESS);
}

static int	valid_map_character(t_maze *maze)
{
	int	row;
	int	col;
	int	p_cnt;

	p_cnt = 0;
	row = 0;
	while (maze->map.parsed.map_data[row])
	{
		col = 0;
		if (inner_valid_map(maze, &col, &row, &p_cnt))
			return (FAILURE);
		row++;
		maze->map.width = col;
		maze->map.height = row;
	}
	if (!maze->map.parsed.player)
		return (ft_putendl_fd("Map needs to have one player", 2), FAILURE);
	if (p_cnt > 1)
		return (ft_putendl_fd("Map can only have one player", 2), FAILURE);
	return (SUCCESS);
}

int	check_enclosed(t_maze *maze)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	while (i < maze->map.height)
	{
		j = 0;
		width = (int)ft_strlen(maze->map.parsed.map_data[i]);
		while (maze->map.parsed.map_data[i][j] != '\0')
		{
			if (maze->map.parsed.map_data[i][0] == '0' || maze->map.parsed.map_data[i][width - 1] == '0')
				return (ft_putendl_fd("Map is not enclosed", 2), FAILURE);
			if (i == 0 && maze->map.parsed.map_data[i][j] == '0')
				return (ft_putendl_fd("Map is not enclosed", 2), FAILURE);
			if (i == maze->map.height - 1)
			{
				// if (maze->map.parsed.map_data[i][j] == ' ' && (maze->map.parsed.map_data[i][j + 1] == '0' || maze->map.parsed.map_data[i][j - 1] == '0'))
				if (maze->map.parsed.map_data[i][j] == '0')
					return (ft_putendl_fd("Map is not enclosed", 2), FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	validate_map(t_maze *maze)
{
	if (valid_map_character(maze))
		return (FAILURE);
	if (check_enclosed(maze))
		return (FAILURE);
	if (flood_fill(maze, maze->player.pos_y, maze->player.pos_x))
	{
		ft_putendl_fd("Map is not enclosed", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
