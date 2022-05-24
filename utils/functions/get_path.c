/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:28:18 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/24 12:13:52 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(char **envp)
{
	char	*path;
	int		i;
	int		len;

	if (!envp[0])
		return (NULL);
	len = ft_strlen("PATH=");
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], len - 1) == 0)
		{
			path = ft_substr(envp[i], len, ft_strlen(envp[i]) - len);
			return (path);
		}
		i++;
	}
	return (0);
}
