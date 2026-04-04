/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:52:18 by schabboe          #+#    #+#             */
/*   Updated: 2026/04/04 15:54:18 by schabboe         ###   ########.fr       */
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
# include <stdbool.h>
# include "LIBFT/libft.h"
# include <sys/time.h>

# define WIDTH 1024
# define HEIGHT 640
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define SUCCESS 0
# define FAILURE 1

typedef struct s_colors
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}			t_colors;

typedef struct s_txtrs
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}					t_txtrs;

typedef struct s_parse
{
	char	**map_data;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
	uint8_t	*rgb_floor;
	uint8_t	*rgb_ceiling;
	char	player;
}				t_parse;

typedef struct s_map
{
	int			width;
	int			height;
	t_parse		parsed;
}					t_map;

typedef struct s_player
{
	double	pos_x; // position vector of player, x component (where player is at)
	double	pos_y; // position vector of player, y component (where player is at)
	int		height;
}				t_player;

typedef struct s_vector
{
	double	dir_x; // direction vector, x component
	double	dir_y; // direction vector, y component
	double	ray_dir_x; // ray direction vector, x component
	double	ray_dir_y; // ray direction vector, y component
	double	plane_x; // camera plane vector, x component
	double	plane_y; // camera plane vector, y component
}					t_vector;

typedef struct s_raycast
{
	double	camera_x; // x-coordinate in camera space
	int		grid_x; // In welk vakje van de grid we zitten, x component
	int		grid_y; // In welk vakje van de grid we zitten, y component
	double	ray_len_x; // Length of ray from start position to the next x-intersection
	double	ray_len_y; // Length of ray from start position to the next y-intersection
	double	delta_dist_x; // Length of ray from 1 x-intersect to the next x-intersect
	double	delta_dist_y; // Length of ray from 1 y-intersect to the next y-intersect
	int		step_x; // Jump a square in x-direction
	int		step_y; // Jump a square in y-direction
	double	distance_to_wall;
	int		side;
}						t_raycast;

typedef struct s_draw
{
	int			line_height;
	double		start;
	double		end;
	int			tex_x;
	int			tex_y;
	uint32_t	color;
}				t_draw;

typedef struct s_frame
{
	struct timeval	begin_time;
	struct timeval	end_time;
	double			frame_time;
	double			begin_sec;
	double			end_sec;
}				t_frame;

typedef struct s_maze
{
	char			*filename;
	t_map			map;
	mlx_t			*mlx;
	t_player		player;
	t_vector		vector;
	t_raycast		raycast;
	t_txtrs			txtr;
	mlx_image_t		*screen;
	t_colors		colors;
	t_draw			draw;
	t_frame			move;
}					t_maze;

//UTILS
void	ft_d_free(char **arr);

//RGB
int		validate_rgb(t_maze *maze);
char	*split_rgb(char *s);
uint8_t	*fill_rgb(char *s);
uint8_t		ft_digit_check(char *str);
void	draw_c_f(t_maze *maze);

//Parse
int		read_map(t_maze *maze);
int		validate_map(t_maze *maze);
int		validate_texture(t_maze *maze);
int		alloc_rows(t_maze *maze);
int		fill_rows(t_maze *maze, char *map_row, int *i);
int		flood_fill(t_maze *maze, int x, int y);

// MLX functions
void	press_esc(void *param);
void	movement(void *param);

// Raycasting
void	raycasting(t_maze *maze);
void	init_vectors(t_maze *maze);
void	draw_line(t_maze *maze, int x);
void	delete_tex(t_maze *maze);
void	free_tex(t_maze *maze);
void	free_c_f(t_maze *maze);
void	free_rgb(t_maze *maze);

#endif