/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 12:52:18 by schabboe      #+#    #+#                 */
/*   Updated: 2026/02/17 12:24:24 by ksoedama      ########   odam.nl         */
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

# define WIDTH 640
# define HEIGHT 640

typedef struct	s_parse
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*C;
	char	*F;
	int		*rgb_floor;
	int		*rgb_ceiling;
	int		*wall;
	int		*floor;
	int		*empty;
}				t_parse;

typedef struct s_map
{
	char		**cpy_map;
	char		**map;
	size_t		cpy_width;
	size_t		cpy_height;
	size_t		width;
	size_t		height;
	t_parse		parsed;
}					t_map;

typedef struct	s_player 
{
	int	start_x;
	int	start_y;
	int	x_pos;
	int	y_pos;
	int	vof;
	int	viewing_angle;
}					t_player;

typedef struct	s_raycast
{
	int	ray_degree;
	int	angle_increment;
	int	distance_to_wall;
	int	x_intersect;
	int	y_intersect;
	int	x_grid_coordinate;
	int	y_grid_coordinate;
	
}					t_raycast;

typedef struct	s_projection
{
	int	width;
	int	length;
	int	half_width;
	int	player_to_projection_plane;
}					t_projection;

typedef struct	s_maze
{
	char		*filename;
	t_map		map;
	mlx_t		*mlx;
	t_player	player;
}					t_maze;

int		cpy_map_size(t_maze *map);
int		cpy_of_map(t_maze *map);
void	ft_d_free(char **arr);

#endif