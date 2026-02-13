/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 12:44:51 by schabboe      #+#    #+#                 */
/*   Updated: 2026/02/13 16:08:50 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int			i;
	int			len_arg;
	char		*file_type;
	t_maze		maze;

	if (argc < 2)
		return (write(2, "Map is not provided!\n", 21), 1);
	if (argc > 2)
		return (write(2, "Too many arguments!\n", 20), 1);
	len_arg = ft_strlen(argv[1]);
	i = len_arg;
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
	return (0);
}
