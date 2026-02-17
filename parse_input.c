/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 10:28:57 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/17 14:20:26 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*split_rgb(char *s)
{
	char	**split_spaces;

	split_spaces = ft_split(s, ' ');
	if (!split_spaces)
		return (NULL);
	return (split_spaces[1]);
}

int	*fill_rgb(char *s)
{
	char	**split_comma;

	split_comma = ft_split(s, ',');
	if (!split_comma)
		return (NULL);
	int *arr = malloc(3 * sizeof(int));
	if (!arr)
	{
		ft_d_free(split_comma);
		return (NULL);
	}
	arr[0] = ft_atoi(split_comma[0]);
	arr[1] = ft_atoi(split_comma[1]);
	arr[2] = ft_atoi(split_comma[2]);
	ft_d_free(split_comma);
	return (arr);
}

int	validate_rgb(t_maze *maze)
{
	if ((maze->map.parsed.rgb_floor[0] > 255 || maze->map.parsed.rgb_floor[0] < 0)
		|| (maze->map.parsed.rgb_floor[1] > 255 || maze->map.parsed.rgb_floor[1] < 0)
		|| (maze->map.parsed.rgb_floor[2] > 255 || maze->map.parsed.rgb_floor[2] < 0))
		return (ft_putendl_fd("Error: Floor RGB value not in 0-255 range", 2), 1);
	if ((maze->map.parsed.rgb_ceiling[0] > 255 || maze->map.parsed.rgb_ceiling[0] < 0)
		|| (maze->map.parsed.rgb_ceiling[1] > 255 || maze->map.parsed.rgb_ceiling[1] < 0)
		|| (maze->map.parsed.rgb_ceiling[2] > 255 || maze->map.parsed.rgb_ceiling[2] < 0))
		return (ft_putendl_fd("Error: Ceiling RGB value not in 0-255 range", 2), 1);
	return (0);
}
