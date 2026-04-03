/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksoedama <ksoedama@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/03 14:36:29 by ksoedama      #+#    #+#                 */
/*   Updated: 2026/04/03 14:36:44 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char **line, char *buffer)
{
	char	*new;

	if (*line == NULL)
	{
		new = malloc(ft_strlen(buffer) + 1);
		if (new == NULL)
			return (NULL);
		ft_strlcpy(new, buffer, ft_strlen(buffer) + 1);
		return (new);
	}
	new = malloc(ft_strlen(*line) + ft_strlen(buffer) + 1);
	if (new == NULL)
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	ft_strlcpy(new, *line, ft_strlen(*line) + 1);
	ft_strlcpy(new + ft_strlen(*line), buffer, ft_strlen(buffer) + 1);
	free(*line);
	*line = NULL;
	return (new);
}