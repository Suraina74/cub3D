/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: schabboe <schabboe@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 22:29:13 by schabboe      #+#    #+#                 */
/*   Updated: 2026/04/02 14:52:32 by ksoedama      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strrchr(set, s1[end]))
		end--;
	str = ft_substr(s1, start, end - start + 1);
	if (str == NULL)
		return (NULL);
	return (str);
}