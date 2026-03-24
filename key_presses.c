/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_presses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:21:29 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/24 14:44:04 by schabboe         ###   ########.fr       */
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
	if (mlx_is_key_down(maze->mlx, MLX_KEY_A))
	{
		maze->player.pos_x -= 1;
		//raycasting aanroepen.
	}
	if (mlx_is_key_down(maze->mlx, MLX_KEY_D))
	{
		maze->player.pos_x += 1;
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
