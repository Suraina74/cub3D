/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 12:44:51 by schabboe      #+#    #+#                 */
/*   Updated: 2026/02/17 15:23:58 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int			len_arg;
	char		*file_type;
	t_maze		maze;

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
	free (file_type);
	maze.filename = argv[1];
	if (cpy_map_size(&maze))
		return (1);
	maze.mlx = mlx_init(WIDTH, HEIGHT, "cubed", true);
	if (!maze.mlx)
		return(1);
	mlx_loop(maze.mlx);
	mlx_terminate(maze.mlx);
	//filled metadata in struct
	// printf("no: %s\n", maze.map.parsed.NO);
	// printf("so: %s\n", maze.map.parsed.SO);
	// printf("we: %s\n", maze.map.parsed.WE);
	// printf("ea: %s\n", maze.map.parsed.EA);
	printf("r: %i g: %i b: %i\n", maze.map.parsed.rgb_floor[0], maze.map.parsed.rgb_floor[1],maze.map.parsed.rgb_floor[2]);
	printf("r: %i g: %i b: %i\n", maze.map.parsed.rgb_ceiling[0],maze.map.parsed.rgb_ceiling[1],maze.map.parsed.rgb_ceiling[2]);
	return (0);
}
