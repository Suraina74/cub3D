/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:44:51 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/10 20:08:42 by schabboe         ###   ########.fr       */
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
	
	raycasting(&maze);
	// mlx_loop_hook(maze.mlx, &movement, &maze);
	mlx_loop_hook(maze.mlx, &press_esc, &maze);
	mlx_loop(maze.mlx);
	mlx_terminate(maze.mlx);
	return (0);
}
