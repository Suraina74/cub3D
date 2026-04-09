/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 12:44:51 by schabboe      #+#    #+#                 */
/*   Updated: 2026/04/09 22:18:52 by ksoedama      ########   odam.nl         */
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
		return (free(file_type), write(2, "Invalid map!\n", 13), 1);
	free(file_type);
	maze.filename = argv[1];
	if (read_map(&maze))
		return (free_rgb(&maze), delete_tex(&maze), FAILURE);
	maze.mlx = mlx_init(WIDTH, HEIGHT, "cubed", true);
	if (!maze.mlx)
		return (free_c_f(&maze), free_rgb(&maze), free_tex(&maze), ft_d_free(maze.map.parsed.map_data), delete_tex(&maze), FAILURE);
	maze.screen = mlx_new_image(maze.mlx, WIDTH, HEIGHT);
	if (!maze.screen || mlx_image_to_window(maze.mlx, maze.screen, 0, 0) < 0)
		return (mlx_terminate(maze.mlx), free_c_f(&maze), free_rgb(&maze), free_tex(&maze), \
ft_d_free(maze.map.parsed.map_data), delete_tex(&maze), write(2, "Error displaying image\n", 23), FAILURE);
	gettimeofday(&maze.move.begin_time, NULL);
	maze.move.begin_sec = maze.move.begin_time.tv_sec + maze.move.begin_time.tv_usec/1000000.0;
	draw_c_f(&maze);
	init_vectors(&maze);
	raycasting(&maze);
	gettimeofday(&maze.move.end_time, NULL);
	maze.move.end_sec = maze.move.end_time.tv_sec + maze.move.end_time.tv_usec/1000000.0;
	maze.move.frame_time = maze.move.end_sec - maze.move.begin_sec;
	maze.move.begin_sec = maze.move.end_sec;
	mlx_loop_hook(maze.mlx, &movement, &maze);
	mlx_loop_hook(maze.mlx, &press_esc, &maze);
	mlx_loop(maze.mlx);
	mlx_terminate(maze.mlx);
	free_tex(&maze);
	free_c_f(&maze);
	free_rgb(&maze);
	ft_d_free(maze.map.parsed.map_data);
	delete_tex(&maze);
	return (0);
}
