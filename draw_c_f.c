/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_c_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:21:59 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/10 18:00:28 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_c_f(t_maze *maze)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	color_ceiling;
	uint32_t	color_floor;

	i = 0;
	maze->colors.r = (uint8_t)maze->map.parsed.rgb_ceiling[0];
	maze->colors.g = (uint8_t)maze->map.parsed.rgb_ceiling[1];
	maze->colors.b = (uint8_t)maze->map.parsed.rgb_ceiling[2];
	maze->colors.a = 255;
	color_ceiling = (maze->colors.r << 24) | (maze->colors.g << 16) | \
(maze->colors.b << 8) | maze->colors.a;
	while (i < WIDTH)
	{
		j = 0;
		while (j < (HEIGHT / 2))
		{
			mlx_put_pixel(maze->screen, i, j, color_ceiling);
			j++;
		}
		i++;
	}
	maze->colors.r = (uint8_t)maze->map.parsed.rgb_floor[0];
	maze->colors.g = (uint8_t)maze->map.parsed.rgb_floor[1];
	maze->colors.b = (uint8_t)maze->map.parsed.rgb_floor[2];
	maze->colors.a = 255;
	color_floor = (maze->colors.r << 24) | (maze->colors.g << 16) | \
(maze->colors.b << 8) | maze->colors.a;
	i = 0;
	while (i < WIDTH)
	{
		j = (HEIGHT / 2);
		while (j < HEIGHT)
		{
			mlx_put_pixel(maze->screen, i, j, color_floor);
			j++;
		}
		i++;
	}
}
