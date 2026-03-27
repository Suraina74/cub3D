/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:44:51 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/27 18:18:18 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int				len_arg;
	char			*file_type;
	static t_maze	maze;

	if (argc < 2)
		return (write(2, "Map is not provided!\n", 21), 1);
	if (argc > 2)
		return (write(2, "Too many arguments!\n", 20), 1);
	len_arg = ft_strlen(argv[1]);
	file_type = ft_substr(argv[1], (len_arg - 4), 4);
	if (file_type == NULL)
		return (1);
	if (ft_strncmp(file_type, ".cub", 4) != 0)
		return (write(2, "Invalid map!\n", 13), 1);
	free(file_type);
	maze.filename = argv[1];
	if (read_map(&maze))
		return (FAILURE);
	int i = 0;
	while (maze.map.parsed.map_data[i])
	{
		printf("%s\n", maze.map.parsed.map_data[i]);
		i++;
	}
	maze.mlx = mlx_init(WIDTH, HEIGHT, "cubed", true);
	if (!maze.mlx)
		return(1);
	maze.screen = mlx_new_image(maze.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(maze.mlx, maze.screen, 0, 0);
	// maze.mini_map = mlx_new_image(maze.mlx, 200, 100);
	// mlx_image_to_window(maze.mlx, maze.mini_map, 0, 0);
	gettimeofday(&maze.move.begin_time, NULL);
	maze.move.begin_sec = maze.move.begin_time.tv_sec + maze.move.begin_time.tv_usec/1000000.0;
	raycasting(&maze);
	// draw_mini_map(&maze);
	gettimeofday(&maze.move.end_time, NULL);
	maze.move.end_sec = maze.move.end_time.tv_sec + maze.move.end_time.tv_usec/1000000.0;
	maze.move.frame_time = maze.move.end_sec - maze.move.begin_sec;
	maze.move.begin_sec = maze.move.end_sec;
	mlx_loop_hook(maze.mlx, &movement, &maze);
	mlx_loop_hook(maze.mlx, &press_esc, &maze);
	mlx_loop(maze.mlx);
	mlx_terminate(maze.mlx);
	return (0);
}
