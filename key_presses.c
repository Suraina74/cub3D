/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_presses.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/10 18:21:29 by schabboe      #+#    #+#                 */
/*   Updated: 2026/04/02 13:34:49 by ksoedama      ########   odam.nl         */
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

void	move_up_down(t_maze *maze, double move_speed)
{
	if (mlx_is_key_down(maze->mlx, MLX_KEY_W))
	{
		if (maze->map.parsed.map_data[(int)maze->player.pos_y]\
[(int)(maze->player.pos_x + maze->vector.dir_x * (move_speed))] != '1')
			maze->player.pos_x += maze->vector.dir_x * move_speed;
		if (maze->map.parsed.map_data[(int)(maze->player.pos_y + \
maze->vector.dir_y * (move_speed))][(int)maze->player.pos_x] != '1')
			maze->player.pos_y += maze->vector.dir_y * move_speed;
	}
	else if (mlx_is_key_down(maze->mlx, MLX_KEY_S))
	{
		if (maze->map.parsed.map_data[(int)maze->player.pos_y]\
[(int)(maze->player.pos_x - maze->vector.dir_x * (move_speed))] != '1')
			maze->player.pos_x -= maze->vector.dir_x * move_speed;
		if (maze->map.parsed.map_data[(int)(maze->player.pos_y - \
maze->vector.dir_y * (move_speed))][(int)maze->player.pos_x] != '1')
			maze->player.pos_y -= maze->vector.dir_y * move_speed;
	}
}

void	move_left_right(t_maze *maze, double move_speed)
{
	if (mlx_is_key_down(maze->mlx, MLX_KEY_A))
	{
		if (maze->map.parsed.map_data[(int)maze->player.pos_y]\
[(int)(maze->player.pos_x - maze->vector.plane_x * (move_speed))] != '1')
			maze->player.pos_x -= maze->vector.plane_x * move_speed;
		if (maze->map.parsed.map_data[(int)(maze->player.pos_y - \
maze->vector.plane_y * (move_speed))][(int)maze->player.pos_x] != '1')
			maze->player.pos_y -= maze->vector.plane_y * move_speed;
	}
	else if (mlx_is_key_down(maze->mlx, MLX_KEY_D))
	{
		if (maze->map.parsed.map_data[(int)maze->player.pos_y]\
[(int)(maze->player.pos_x + maze->vector.plane_x * (move_speed))] != '1')
			maze->player.pos_x += maze->vector.plane_x * move_speed;
		if (maze->map.parsed.map_data[(int)(maze->player.pos_y + \
maze->vector.plane_y * (move_speed))][(int)maze->player.pos_x] != '1')
			maze->player.pos_y += maze->vector.plane_y * move_speed;
	}
}

void	rotate(t_maze *maze, double rotate_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(maze->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = maze->vector.dir_x;
		maze->vector.dir_x = maze->vector.dir_x * cos(-rotate_speed) - \
maze->vector.dir_y * sin(-rotate_speed);
		maze->vector.dir_y = old_dir_x * sin(-rotate_speed) + \
maze->vector.dir_y * cos(-rotate_speed);
		old_plane_x = maze->vector.plane_x;
		maze->vector.plane_x = maze->vector.plane_x * cos(-rotate_speed) - \
maze->vector.plane_y * sin(-rotate_speed);
		maze->vector.plane_y = old_plane_x * sin(-rotate_speed) + \
maze->vector.plane_y * cos(-rotate_speed);
	}
	else if (mlx_is_key_down(maze->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = maze->vector.dir_x;
		maze->vector.dir_x = maze->vector.dir_x * cos(rotate_speed) - \
maze->vector.dir_y * sin(rotate_speed);
		maze->vector.dir_y = old_dir_x * sin(rotate_speed) + \
maze->vector.dir_y * cos(rotate_speed);
		old_plane_x = maze->vector.plane_x;
		maze->vector.plane_x = maze->vector.plane_x * cos(rotate_speed) - \
maze->vector.plane_y * sin(rotate_speed);
		maze->vector.plane_y = old_plane_x * sin(rotate_speed) + \
maze->vector.plane_y * cos(rotate_speed);
	}
}

void	movement(void *param)
{
	t_maze	*maze;
	double	move_speed;
	double	rotate_speed;

	maze = (t_maze *)param;
	move_speed = maze->move.frame_time * 5.0;
	rotate_speed = maze->move.frame_time * 3.0;
	move_up_down(maze, move_speed);
	move_left_right(maze, move_speed);
	rotate(maze, rotate_speed);
	mlx_delete_image(maze->mlx, maze->screen);
	maze->screen = mlx_new_image(maze->mlx, WIDTH, HEIGHT);
	if (!maze->screen || mlx_image_to_window(maze->mlx, maze->screen, 0, 0) < 0)
	{
		write(2, "Error displaying image\n", 23);
		exit(1);
	}
	draw_c_f(maze);
	raycasting(maze);
	gettimeofday(&maze->move.end_time, NULL);
	maze->move.end_sec = maze->move.end_time.tv_sec + \
maze->move.end_time.tv_usec / 1000000.0;
	maze->move.frame_time = maze->move.end_sec - maze->move.begin_sec;
	maze->move.begin_sec = maze->move.end_sec;
}
