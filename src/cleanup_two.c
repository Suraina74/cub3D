/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:34:30 by schabboe          #+#    #+#             */
/*   Updated: 2026/04/10 18:35:02 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_everything(t_maze *maze)
{
	free_c_f(maze);
	free_rgb(maze);
	free_tex(maze);
	ft_d_free(maze->map.parsed.map_data);
	delete_tex(maze);
	mlx_terminate(maze->mlx);
}
