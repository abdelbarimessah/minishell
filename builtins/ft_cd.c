/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:32:40 by amessah           #+#    #+#             */
/*   Updated: 2022/06/05 16:57:25 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *check_home_path(char **str)
{
    int i;
    char **cmd;

    i = 0;
    while(str[i])
    {
        cmd = ft_split(str[i], '=');
        if(!ft_strcmp(cmd[0], "HOME"))
            return (cmd[1]);
        // ft_free(cmd);
        i++;
    }
    return (NULL);
}

char    *check_oldpwd_path(char **str)
{
    int i;
    char **cmd;

    i = 0;
    while(str[i])
    {
        cmd = ft_split(str[i], '=');
        if(!ft_strcmp(cmd[0], "OLDPWD"))
            return (cmd[1]);
        // ft_free(cmd);
        i++;
    }
    return (NULL);
}

void    old_pwd(void)
{
    char path[1024];
    char *old;

    getcwd(path, 1024);
    old = ft_strjoin("OLDPWD=", path);
    g_glob = add_to_list(g_glob, old);
}

void cd_pwd(void)
{
    char	path[1024];
    char *pwd;

	if (!getcwd(path, 1024))
	{
		perror("cd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
		return ;
	}
    pwd = ft_strjoin("PWD=", path);
    g_glob = add_to_list(g_glob, pwd);
}

void ft_cd(char **args)
{
    char *str;
    char **cm;
    t_env *list;

    list = g_glob;
    old_pwd();
    if(!args[1] || !ft_strcmp(args[1], "--") || !ft_strcmp(args[1], "~"))
    {
        cm = new_env_function(list);
        str = check_home_path(cm);
        if(!str)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
        }
        args[1] = str;
    }
    else if(!ft_strcmp(args[1],"-"))
    {
        cm = new_env_function(list);
        str = check_oldpwd_path(cm);
        if(!str)
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
        else
            args[1] = str;
    }
    if(chdir(args[1]) == -1)
    {
        ft_putstr_fd("cd: ",1);
        ft_putstr_fd(args[1],1);
        ft_putstr_fd(": No such file or directory\n",1);
    }
    cd_pwd();
}