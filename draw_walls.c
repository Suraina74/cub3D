/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:47:42 by schabboe          #+#    #+#             */
/*   Updated: 2026/04/10 18:00:57 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	where_ray_hit_tex(t_maze *maze)
{
	double	wall_hit;

	if (maze->raycast.side == 0)
		wall_hit = maze->player.pos_y + maze->raycast.distance_to_wall \
* maze->vector.ray_dir_y;
	else
		wall_hit = maze->player.pos_x + maze->raycast.distance_to_wall \
* maze->vector.ray_dir_x;
	wall_hit = wall_hit - floor (wall_hit);
	maze->draw.tex_x = wall_hit * TEX_WIDTH;
}

void	convert_to_mlx_color(t_maze *maze, int tex_y, uint32_t *color)
{
	int				index;
	mlx_texture_t	*tex;

	tex = NULL;
	if (maze->raycast.side == 0 && maze->vector.ray_dir_x > 0)
		tex = maze->txtr.east;
	else if (maze->raycast.side == 0 && maze->vector.ray_dir_x < 0)
		tex = maze->txtr.west;
	else if (maze->raycast.side == 1 && maze->vector.ray_dir_y > 0)
		tex = maze->txtr.south;
	else if (maze->raycast.side == 1 && maze->vector.ray_dir_y < 0)
		tex = maze->txtr.north;
	index = (tex_y * TEX_WIDTH + maze->draw.tex_x) * 4;
	maze->colors.r = tex->pixels[index + 0];
	maze->colors.g = tex->pixels[index + 1];
	maze->colors.b = tex->pixels[index + 2];
	maze->colors.a = tex->pixels[index + 3];
	*color = (maze->colors.r << 24) | (maze->colors.g << 16) | \
(maze->colors.b << 8) | maze->colors.a;
}

void	draw_line(t_maze *maze, int x)
{
	uint32_t	y;
	double		step;
	double		tex_pos;

	maze->draw.start = HEIGHT / 2 - maze->draw.line_height / 2;
	if (maze->draw.start < 0)
		maze->draw.start = 0;
	maze->draw.end = maze->draw.line_height / 2 + HEIGHT / 2;
	if (maze->draw.end >= HEIGHT)
		maze->draw.end = HEIGHT - 1;
	step = 1.0 * TEX_HEIGHT / maze->draw.line_height;
	tex_pos = (maze->draw.start - HEIGHT / 2 + \
maze->draw.line_height / 2) * step;
	where_ray_hit_tex(maze);
	y = maze->draw.start;
	while (y < maze->draw.end)
	{
		maze->draw.tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		convert_to_mlx_color(maze, maze->draw.tex_y, &maze->draw.color);
		tex_pos += step;
		mlx_put_pixel(maze->screen, x, y, maze->draw.color);
		y++;
	}
}
