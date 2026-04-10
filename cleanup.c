/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:41:41 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/10 17:55:52 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_d_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

void	free_tex(t_maze *maze)
{
	if (maze->map.parsed.no)
		free(maze->map.parsed.no);
	if (maze->map.parsed.so)
		free(maze->map.parsed.so);
	if (maze->map.parsed.ea)
		free(maze->map.parsed.ea);
	if (maze->map.parsed.we)
		free(maze->map.parsed.we);
}

void	free_c_f(t_maze *maze)
{
	if (maze->map.parsed.f)
		free(maze->map.parsed.f);
	if (maze->map.parsed.c)
		free(maze->map.parsed.c);
}

void	free_rgb(t_maze *maze)
{
	if (maze->map.parsed.rgb_floor)
		free(maze->map.parsed.rgb_floor);
	if (maze->map.parsed.rgb_ceiling)
		free(maze->map.parsed.rgb_ceiling);
}

void	delete_tex(t_maze *maze)
{
	if (maze->txtr.north)
		mlx_delete_texture(maze->txtr.north);
	if (maze->txtr.south)
		mlx_delete_texture(maze->txtr.south);
	if (maze->txtr.west)
		mlx_delete_texture(maze->txtr.west);
	if (maze->txtr.east)
		mlx_delete_texture(maze->txtr.east);
}
