/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 22:29:13 by schabboe      #+#    #+#                 */
/*   Updated: 2026/03/06 17:42:23 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	length;
	size_t	start;
	char	*trimmed;

	start = 0;
	if (s1[0] == '\0')
		return (ft_strdup(""));
	length = ft_strlen(s1);
	while (start < length && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (ft_strchr(set, s1[length]) != NULL && length != 0)
		length--;
	if (length == 0)
		return (ft_strdup(""));
	length = length - start + 1;
	trimmed = (char *) malloc(length + 1);
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, length + 1);
	return (trimmed);
}
