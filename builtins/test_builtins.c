/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:21:54 by amessah           #+#    #+#             */
/*   Updated: 2022/05/30 17:49:22 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/minishell.h"

void test_builtins(char *str,char **env)
{
    char **str1;

    str1 = ft_split(str, ' ');
    if(ft_strcmp(str1[0], "echo") == 0)
        ft_echo(str1);
    else if(ft_strcmp(str1[0], "pwd") == 0)
        ft_pwd();
    else if(!ft_strcmp(str1[0], "exit"))
        ft_exit(str1);
    else if (!ft_strcmp(str1[0], "env"))
        ft_env(env);
}