/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 15:15:21 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/23 16:55:08 by ksoedama      ########   odam.nl         */
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
