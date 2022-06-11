/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:32:46 by amessah           #+#    #+#             */
/*   Updated: 2022/06/11 21:39:53 by amessah          ###   ########.fr       */
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

void    old_pwd(t_env *list)
{
    char path[1024];
    char *old;

    getcwd(path, 1024);
    old = ft_strjoin("OLDPWD=", path);
    list = search_and_replce_OLDPWD(g_glob, old);
}

void cd_pwd(t_env *list)
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
    list = search_and_replce_PWD(g_glob, pwd);
}

char *path_OLDPWD(t_env *list)
{
    char **str;
    t_env *tmp;

    tmp = list;
    if(!tmp)
        return (NULL);
    while(tmp)
    {
        if(!ft_strncmp(tmp->value,"OLDPWD",6))
        {
            str = ft_split(tmp->value, '=');
            printf("%s\n",str[1]);
            return (str[1]);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

void ft_cd(char **args)
{
    char *str;
    char **cm;
    t_env *list;
    int a;

    a = 0;
    list = g_glob;
    if(args[1] != NULL && !ft_strcmp(args[1],"-"))
    {  
        if(g_glob->index == 0)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
        }
        else
        {
            args[1] = path_OLDPWD(g_glob);
            if(chdir(args[1]) == -1)
            {
                ft_putstr_fd("cd: ",1);
                ft_putstr_fd(args[1],1);
                ft_putstr_fd(": No such file or directory\n",1);
            }
        }
        a++;
    }
    old_pwd(list);
    if(args[1] == NULL || !ft_strcmp(args[1],"--") || !ft_strcmp(args[1],"~"))
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
    if(chdir(args[1]) == -1 && a == 0 && args[1])
    {
        ft_putstr_fd("cd: ",1);
        ft_putstr_fd(args[1],1);
        ft_putstr_fd(": No such file or directory\n",1);
    }
    cd_pwd(list);
    g_glob->index++;
}