/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:57:18 by ksoedama          #+#    #+#             */
/*   Updated: 2026/04/08 21:32:21 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

int	ft_digit_check(char *str)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		return (ft_putendl_fd("Value cannot be negative", 2), -1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (INT_MAX - (str[i] - '0')) / 10)
			return (ft_putendl_fd("Overflow", 2), -1);
		res = (res * 10) + (str[i++] - '0');
	}
	return (res);
}
