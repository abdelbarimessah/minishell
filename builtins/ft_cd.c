/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:32:46 by amessah           #+#    #+#             */
/*   Updated: 2022/06/24 20:20:37 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_home_path(char **str)
{
	int		i;
	char	**cmd;

	i = 0;
	while (str[i])
	{
		cmd = ft_split(str[i], '=');
		if (!ft_strcmp(cmd[0], "HOME"))
			return (cmd[1]);
		ft_free(cmd);
		i++;
	}
	return (NULL);
}

void	old_pwd(t_env *list)
{
	char	path[1024];
	char	*old;

	if (!getcwd(path, 1024))
		g_glob->exit_status = 0;
	old = ft_strjoin("OLDPWD=", path);
	list = search_and_replce_oldpwd(g_glob, old);
}

void	cd_pwd(t_env *list)
{
	char	path[1024];
	char	*pwd;

	if (!getcwd(path, 1024))
	{
		perror("cd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
		return ;
	}
	pwd = ft_strjoin("PWD=", path);
	list = search_and_replce_pwd(g_glob, pwd);
}

char	*path_oldpwd(t_env *list)
{
	char	**str;
	t_env	*tmp;

	tmp = list;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(tmp->value, "OLDPWD", 6))
		{
			str = ft_split(tmp->value, '=');
			printf("%s\n", str[1]);
			return (str[1]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_cd(char **args)
{
	t_env	*list;
	int		a;

	a = 0;
	list = g_glob;
	if (args[1] != NULL && !ft_strcmp(args[1], "-"))
		a = ft_cd_utils(args, a);
	old_pwd(list);
	if (args[1] == NULL || !ft_strcmp(args[1], "--")
		|| !ft_strcmp(args[1], "~"))
		ft_cd_home(list, args);
	if (chdir(args[1]) == -1 && a == 0 && args[1])
	{
		g_glob->exit_status = 1;
		ft_putstr_3("cd: ", args[1], ": No such file or directory\n");
		ft_free(args);
	}
	else if (chdir(args[1]) != -1)
		g_glob->index++;
	cd_pwd(list);
	ft_lstadd_backp(&g_glob->point, (ft_lstnewp((void *)args)));
}
