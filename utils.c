/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/13 09:57:18 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/02/13 09:59:13 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_d_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}
