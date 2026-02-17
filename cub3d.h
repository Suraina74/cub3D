/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:52:18 by schabboe          #+#    #+#             */
/*   Updated: 2026/02/17 17:14:58 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "LIBFT/libft.h"

# define WIDTH 320 // Means 320 rays to cast.
# define HEIGHT 200

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
	// int	start_grid_x;
	// int	start_grid_y;
	// int	start_pixel_x;
	// int	start_pixel_y;
	int	grid_pos_x;
	int	grid_pos_y;
	int	pixel_pos_x;
	int	pixel_pos_y;
	int	vof;
	int	height;
	int	viewing_angle;
}					t_player;

typedef struct	s_raycast
{
	int	ray_degree;
	int	angle_increment;
	int	distance_to_wall;
	int	x_grid_intersect;
	int	y_grid_intersect;
	int	pixel_x;
	int	pixel_y;
}				t_raycast;
				
typedef struct	s_projection
{
	// int	width;
	// int	length;
	// int	half_width;
	int	distance_to_plane;
}					t_projection;

typedef struct	s_maze
{
	char			*filename;
	t_map			map;
	mlx_t			*mlx;
	t_player		player;
	t_raycast		raycast;
	t_projection	projection_plane;
}					t_maze;

int		cpy_map_size(t_maze *map);
int		cpy_of_map(t_maze *map);
void	ft_d_free(char **arr);
int		validate_rgb(t_maze *maze);
char	*split_rgb(char *s);
int		*fill_rgb(char *s);
int		ft_digit_check(char *str);

#endif