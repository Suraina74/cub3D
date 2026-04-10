/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:28:57 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/10 18:03:57 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*split_rgb(char *s)
{
	char	**split_spaces;
	char	*result;
	int		element_cntr;
	int		i;

	i = 0;
	element_cntr = 1;
	split_spaces = ft_split(s, ' ');
	if (!split_spaces)
		return (NULL);
	while (split_spaces[element_cntr])
		element_cntr++;
	if (element_cntr != 2)
		return (ft_d_free(split_spaces), NULL);
	if (ft_strlen(split_spaces[0]) != 1)
		return (ft_d_free(split_spaces), NULL);
	if (!split_spaces[1])
		return (ft_d_free(split_spaces), NULL);
	result = ft_strdup(split_spaces[1]);
	return (ft_d_free(split_spaces), result);
}

int	fill_rgb(char *s, int **arr)
{
	char	**split_comma;
	int		i;
	int		rgb_cntr;

	if (s == NULL)
		return (ft_putendl_fd("RGB value is empty", 2), 1);
	i = 0;
	while (s[i])
	{
		if (s[0] == ',')
			return (ft_putendl_fd("RGB error", 2), 1);
		if (s[i] == ',' && (!ft_isdigit(s[i + 1]) || !ft_isdigit(s[i - 1])))
			return (ft_putendl_fd("RGB error", 2), 1);
		i++;
	}
	split_comma = ft_split(s, ',');
	rgb_cntr = 1;
	while (split_comma[rgb_cntr])
		rgb_cntr++;
	if (rgb_cntr != 3)
		return (ft_d_free(split_comma), \
ft_putendl_fd("Amount of RGB values not correct", 2), 1);
	if (!split_comma)
		return (1);
	if (!split_comma[0] || !split_comma[1] || !split_comma[2])
		return (ft_d_free(split_comma), \
ft_putendl_fd("RGB: color value missing", 2), 1);
	*arr = malloc(3 * sizeof(int));
	if (!(*arr))
		return (ft_d_free(split_comma), 1);
	(*arr)[0] = ft_digit_check(split_comma[0]);
	if ((*arr)[0] == -1)
		return (free(*arr), ft_d_free(split_comma), 1);
	(*arr)[1] = ft_digit_check(split_comma[1]);
	if ((*arr)[1] == -1)
		return (free(*arr), ft_d_free(split_comma), 1);
	(*arr)[2] = ft_digit_check(split_comma[2]);
	if ((*arr)[2] == -1)
		return (free(*arr), ft_d_free(split_comma), 1);
	return (ft_d_free(split_comma), 0);
}

int	validate_rgb(t_maze *maze)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (maze->map.parsed.rgb_floor[i] > 255
			|| maze->map.parsed.rgb_floor[i] < 0)
		{
			ft_putendl_fd("Error: Floor RGB value not in 0-255 range", 2);
			return (FAILURE);
		}
		if (maze->map.parsed.rgb_ceiling[i] > 255
			|| maze->map.parsed.rgb_ceiling[i] < 0)
		{
			ft_putendl_fd("Error: Ceiling RGB value not in 0-255 range", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
