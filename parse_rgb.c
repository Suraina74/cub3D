/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rgb.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 10:28:57 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/24 15:09:34 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*split_rgb(char *s)
{
	char	**split_spaces;
	char	*result;

	split_spaces = ft_split(s, ' ');
	if (!split_spaces)
		return (NULL);
	if (!split_spaces[1])
		return (ft_d_free(split_spaces), NULL);
	result = ft_strdup(split_spaces[1]);
	return (ft_d_free(split_spaces), result);
}

int	*fill_rgb(char *s)
{
	char	**split_comma;
	int		*arr;

	split_comma = ft_split(s, ',');
	if (!split_comma)
		return (NULL);
	arr = malloc(3 * sizeof(int));
	if (!arr)
		return (ft_d_free(split_comma), NULL);
	arr[0] = ft_digit_check(split_comma[0]);
	arr[1] = ft_digit_check(split_comma[1]);
	arr[2] = ft_digit_check(split_comma[2]);
	return (ft_d_free(split_comma), arr);
}

int	validate_rgb(t_maze *maze)
{
	int i = 0;
	while (i < 3)
	{
		if (maze->map.parsed.rgb_floor[i] > 255 || maze->map.parsed.rgb_floor[i] < 0)
			return (ft_putendl_fd("Error: Floor RGB value not in 0-255 range", 2), 1);
		if (maze->map.parsed.rgb_ceiling[i] > 255 || maze->map.parsed.rgb_ceiling[i] < 0)
			return (ft_putendl_fd("Error: Ceiling RGB value not in 0-255 range", 2), 1);
		i++;
	}
	return (0);
}
