/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:44:51 by schabboe          #+#    #+#             */
/*   Updated: 2026/02/05 13:42:57 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		len_arg;
	int		i;
	char	*file_type;

	if (argc < 2)
		return (write(2, "Map is not provided!\n", 21));
	if (argc > 2)
		return (write(2, "Too many arguments!\n", 20));
	len_arg = ft_strlen(argv[1]);
	i = len_arg;
	file_type = ft_substr(argv[1], (len_arg - 4), 4);
	if (file_type == NULL)
		return (1);
	if (ft_strncmp(file_type, ".cube", 4) != 0)
		return (write(2, "Invalid map!\n", 13));
	free (file_type);
	// Bij openen van map kijken of het een map is die bestaat.

	return (0);
}
