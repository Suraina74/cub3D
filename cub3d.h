/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:52:18 by schabboe          #+#    #+#             */
/*   Updated: 2026/04/10 19:12:43 by schabboe         ###   ########.fr       */
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
#include <limits.h>

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
	int		*rgb_floor;
	int		*rgb_ceiling;
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
	double	pos_x;
	double	pos_y;
	int		height;
}				t_player;

typedef struct s_vector
{
	double	dir_x;
	double	dir_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	plane_x;
	double	plane_y;
}					t_vector;

typedef struct s_raycast
{
	double	camera_x;
	int		grid_x;
	int		grid_y;
	double	ray_len_x;
	double	ray_len_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
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
int		fill_rgb(char *s, int **arr);
int		ft_digit_check(char *str);
void	draw_c_f(t_maze *maze);

//Parse
int		read_map(t_maze *maze);
int		validate_map(t_maze *maze);
int		validate_texture(t_maze *maze);
int		alloc_rows(t_maze *maze);
int		fill_rows(t_maze *maze, char *map_row, int *i);
int		flood_fill(t_maze *maze, int x, int y);
int		fill_metadata_tex(t_maze *maze, char *metadata);
int		fill_metadata_floor(t_maze *maze, char *metadata);
int		fill_metadata_ceiling(t_maze *maze, char *metadata);
int		fill_metadata_map(t_maze *maze, char *metadata, int *i);
int		fill_texture(char *s, char *dir, char **d);
int		check_if_filled(t_maze *maze, char *metadata);

// MLX functions
void	press_esc(void *param);
void	movement(void *param);

// Raycasting
void	raycasting(t_maze *maze);
void	init_vectors(t_maze *maze);
void	draw_line(t_maze *maze, int x);

// Cleanup
void	delete_tex(t_maze *maze);
void	free_tex(t_maze *maze);
void	free_c_f(t_maze *maze);
void	free_rgb(t_maze *maze);
void	free_everything(t_maze *maze);

#endif