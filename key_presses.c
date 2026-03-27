/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_presses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:21:29 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/27 15:22:03 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	press_esc(void *param)
{
	t_maze	*maze;

	maze = (t_maze *)param;
	if (mlx_is_key_down(maze->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(maze->mlx);
}

void	movement(void *param)
{
	t_maze	*maze;

	maze = (t_maze *)param;
	if (mlx_is_key_down(maze->mlx, MLX_KEY_A) && (maze->map.parsed.player == 'S'))
	{
		if (maze->map.parsed.map_data[(int)maze->player.pos_y][(int)(maze->player.pos_x - 0.5)] != '1')
		{
			mlx_delete_image(maze->mlx, maze->screen);
			maze->screen = mlx_new_image(maze->mlx, WIDTH, HEIGHT);
			mlx_image_to_window(maze->mlx, maze->screen, 0, 0);
			maze->player.pos_x -= 0.5;
			raycasting(maze);
		}
		//raycasting aanroepen.
	}
	if (mlx_is_key_down(maze->mlx, MLX_KEY_D)&& (maze->map.parsed.player == 'S'))
	{
		if (maze->map.parsed.map_data[(int)maze->player.pos_y][(int)(maze->player.pos_x + 0.5)] != '1')
		{
			mlx_delete_image(maze->mlx, maze->screen);
			maze->screen = mlx_new_image(maze->mlx, WIDTH, HEIGHT);
			mlx_image_to_window(maze->mlx, maze->screen, 0, 0);
			maze->player.pos_x += 0.5;
			raycasting(maze);
		}
		//raycasting aanroepen.
	}
	if (mlx_is_key_down(maze->mlx, MLX_KEY_W))
	{
		maze->player.pos_y -= 1;
		//raycasting aanroepen.
	}
	if (mlx_is_key_down(maze->mlx, MLX_KEY_S))
	{
		maze->player.pos_y += 1;
		//raycasting aanroepen.
	}
	if (mlx_is_key_down(maze->mlx, MLX_KEY_RIGHT))
	{
		//rotation matrix toepassen
		//raycasting aanroepen.
	}
	if (mlx_is_key_down(maze->mlx, MLX_KEY_LEFT))
	{
		//rotation matrix toepassen
		//raycasting aanroepen.
	}
}
