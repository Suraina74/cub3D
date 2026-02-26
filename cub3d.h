/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 12:52:18 by schabboe      #+#    #+#                 */
/*   Updated: 2026/02/26 13:58:53 by ksoedama      ########   odam.nl         */
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

# define SUCCESS 0
# define FAILURE 1

typedef struct	s_parse
{
	char	**map_data;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*C;
	char	*F;
	int		*rgb_floor;
	int		*rgb_ceiling;
	char	player;
}				t_parse;

typedef struct s_map
{
	int		width;
	int		height;
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

//UTILS
void	ft_d_free(char **arr);

//RGB
int		validate_rgb(t_maze *maze);
char	*split_rgb(char *s);
int		*fill_rgb(char *s);
int		ft_digit_check(char *str);

//Parse
int		read_map(t_maze *maze);
int		validate_map(t_maze *maze);
int 	validate_texture(t_maze *maze);
// void	flood_fill(t_maze *maze, int x, int y);
int	flood_fill(t_maze *maze, int  x, int y);

#endif