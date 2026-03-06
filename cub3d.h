/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:52:18 by schabboe          #+#    #+#             */
/*   Updated: 2026/03/06 17:47:08 by schabboe         ###   ########.fr       */
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
	double	pos_x; // position vector of player, x component (where player is at)
	double	pos_y; // position vector of player, y component (where player is at)
	int		height;
}				t_player;

typedef struct	s_vector
{
	double	dir_x; // direction vector, x component
	double	dir_y; // direction vector, y component
	double	ray_dir_x; // ray direction vector, x component
	double	ray_dir_y; // ray direction vector, y component
	double	plane_x; // camera plane vector, x component
	double	plane_y; // camera plane vector, y component
}					t_vector;

typedef struct	s_raycast
{	
	double	camera_x; // x-coordinate in camera space
	int		grid_x; // In welk vakje van de grid we zitten, x component
	int		grid_y; // In welk vakje van de grid we zitten, y component
	double	dist_from_start_x; // The distance the ray has to travel from its start position to the first x-side
	double	dist_from_start_y; // The distance the ray has to travel from its start position to the first y-side
	double	delta_dist_x; // The distance the ray has to travel to go from 1 x-side to the next x-side
	double	delta_dist_y; // The distance the ray has to travel to go from 1 y-side to the next y-side
	int		step_x; // Jump a square in x-direction
	int		step_y; // Jump a square in y-direction
}						t_raycast;

typedef struct	s_maze
{
	char			*filename;
	t_map			map;
	mlx_t			*mlx;
	t_player		player;
	t_vector		vector;
	t_raycast		raycast;
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