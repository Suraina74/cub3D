/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 12:52:18 by schabboe      #+#    #+#                 */
/*   Updated: 2026/02/07 14:57:20 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "LIBFT/libft.h"

typedef struct	s_parse
{
	char	NO;
	char	SO;
	char	WE;
	char	EA;
	char	C;
	char	F;
	int		wall;
	int		floor;
	int		empty;
}				t_parse;

typedef struct	s_maze_map
{
	char			*filename;
	char			**map;
	size_t			width;
	size_t			height;
	t_parse			parsed;
}				t_maze_map;

typedef struct	s_player 
{
	int			dir_x;
	int			dir_y;
}				t_player;

int	get_map_size(t_maze_map *map);
int	cpy_map(t_maze_map *map);

#endif