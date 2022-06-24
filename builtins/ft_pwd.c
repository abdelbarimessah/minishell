/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:03:43 by amessah           #+#    #+#             */
/*   Updated: 2022/06/24 20:22:59 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcpy(char *s1)
{
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char *) * (ft_strlen(s1) + 1));
	str[ft_strlen(s1)] = '\0';
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}

void	ft_pwd(void)
{
	char	path[PATH_MAX + 1];

	path[PATH_MAX] = '\0';
	if (!getcwd(path, sizeof(path)))
		g_glob->exit_status = 0;
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}
