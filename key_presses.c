/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_presses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:21:29 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/27 18:45:48 by schabboe         ###   ########.fr       */
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
	// double	temp_x;
	// double	temp_y;
	double	move_speed;

	maze = (t_maze *)param;
	move_speed = maze->move.frame_time * 2.0;
	// printf("movespeed: %f\n", move_speed);
	if (mlx_is_key_down(maze->mlx, MLX_KEY_W))
	{
		// temp_x = maze->player.pos_x - 0.2;
		if (maze->map.parsed.map_data[(int)maze->player.pos_y][(int)(maze->player.pos_x + maze->vector.dir_x * move_speed)] != '1')
		{
			// maze->player.pos_x -= 0.2;
			maze->player.pos_x += maze->vector.dir_x * move_speed;
			printf("pos_x: %f\n", maze->player.pos_x);
		}
		if (maze->map.parsed.map_data[(int)(maze->player.pos_y + maze->vector.dir_y * move_speed)][(int)maze->player.pos_x] != '1')
			maze->player.pos_y += maze->vector.dir_y * move_speed;
	}
	if (mlx_is_key_down(maze->mlx, MLX_KEY_S))
	{
		if (maze->map.parsed.map_data[(int)maze->player.pos_y][(int)(maze->player.pos_x - maze->vector.dir_x * move_speed)] != '1')
		{
			maze->player.pos_x -= maze->vector.dir_x * move_speed;
			printf("pos_x: %f\n", maze->player.pos_x);
		}
		if (maze->map.parsed.map_data[(int)(maze->player.pos_y - maze->vector.dir_y * move_speed)][(int)maze->player.pos_x] != '1')
			maze->player.pos_y -= maze->vector.dir_y * move_speed;
	}
	
	// if (mlx_is_key_down(maze->mlx, MLX_KEY_A))
	// {
	// 	if (maze->map.parsed.map_data[(int)maze->player.pos_y][(int)(maze->player.pos_x + maze->vector.dir_x * move_speed)] != '1')
	// 	{
	// 		maze->player.pos_x -= maze->vector.dir_x * move_speed;
	// 		printf("pos_x: %f\n", maze->player.pos_x);
	// 	}
	// 	if (maze->map.parsed.map_data[(int)(maze->player.pos_y + maze->vector.dir_y * move_speed)][(int)maze->player.pos_x] != '1')
	// 	{
	// 		maze->player.pos_y -= maze->vector.dir_y * move_speed;
	// 	}
	// 	//raycasting aanroepen.
	// }
	// if (mlx_is_key_down(maze->mlx, MLX_KEY_D) && (maze->map.parsed.player == 'S'))
	// {
	// 	temp_y = maze->player.pos_y - 0.2;
	// 	if (maze->map.parsed.map_data[(int)temp_y][(int)maze->player.pos_x] != '1')
	// 	{
	// 		mlx_delete_image(maze->mlx, maze->screen);
	// 		maze->screen = mlx_new_image(maze->mlx, WIDTH, HEIGHT);
	// 		mlx_image_to_window(maze->mlx, maze->screen, 0, 0);
	// 		maze->player.pos_y -= 0.2;
	// 		raycasting(maze);
	// 	}
	// 	//raycasting aanroepen.
	// }
	// if (mlx_is_key_down(maze->mlx, MLX_KEY_RIGHT))
	// {
	// 	//rotation matrix toepassen
	// 	//raycasting aanroepen.
	// }
	// if (mlx_is_key_down(maze->mlx, MLX_KEY_LEFT))
	// {
	// 	//rotation matrix toepassen
	// 	//raycasting aanroepen.
	// }
	mlx_delete_image(maze->mlx, maze->screen);
	maze->screen = mlx_new_image(maze->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(maze->mlx, maze->screen, 0, 0);
	raycasting(maze);
	gettimeofday(&maze->move.end_time, NULL);
	maze->move.end_sec = maze->move.end_time.tv_sec + maze->move.end_time.tv_usec/1000000.0;
	maze->move.frame_time = maze->move.end_sec - maze->move.begin_sec;
	maze->move.begin_sec = maze->move.end_sec;
}
