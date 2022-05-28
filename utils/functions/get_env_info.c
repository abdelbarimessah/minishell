/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:28:18 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/27 17:36:29 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_from_env(char **str, char *to_find)
{
	int		i;
	int		j;
	int		x;

	i = -1;
	j = 0;
	while (str[++i])
	{
		j = 0;
		x = 0;
		while (str[i][j] == to_find[x] && str[i][j] != '=')
		{
			if (str[i][j + 1] == '=')
			{
				if(!ft_strncmp(str[i], to_find, ft_strlen(to_find)))
					return (&str[i][j + 2]);
			}
			x++;
			j++;
		}
	}
	return (NULL);
}
