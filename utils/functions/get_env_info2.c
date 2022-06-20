/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:31:42 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/20 15:33:13 by ntanjaou         ###   ########.fr       */
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
				if (!ft_strncmp(str[i], to_find, ft_strlen(to_find)))
					return (&str[i][j + 2]);
			}
			x++;
			j++;
		}
	}
	return (NULL);
}

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

char	*ft_strconcatinate(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s3)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	i = 0;
	while (s3[i])
		str[j++] = s3[i++];
	str[j] = '\0';
	return (str);
}

void	ft_freee(char **tabo, char *cmd)
{
	int	i;

	i = 0;
	while (tabo[i])
	{
		free(tabo[i]);
		i++;
	}
	if (tabo)
		free(tabo);
	free(cmd);
}

char	*get_cmd(char *path, char **av, int i)
{
	char	**mypaths;
	char	**mycmd;
	char	*cmd;

	mypaths = ft_split(path, ':');
	mycmd = ft_split(*av, ' ');
	if (access(mycmd[0], X_OK) == 0)
		return (mycmd[0]);
	else
	{	
		while (mypaths[++i])
		{
			cmd = ft_strconcatinate(mypaths[i], "/", mycmd[0]);
			if (access(cmd, X_OK) == 0)
			{
				ft_freee(mypaths, NULL);
				ft_freee(mycmd, NULL);
				return (cmd);
			}
			free(cmd);
		}
	}
	ft_is_erreur(mycmd, mypaths);
	return (NULL);
}
