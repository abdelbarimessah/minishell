/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:21:54 by amessah           #+#    #+#             */
/*   Updated: 2022/06/07 22:05:54 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/minishell.h"

void test_builtins(t_list *node,char **env)
{
    t_list *head;
    char *str;
    char **cmd;
    int c;

    str = ft_strdup("");
    head = node->next;
    c = 0;
    while(head->token != END_TOK)
    {
        if(head->token == SPACE)
            str = ft_strjoin(str, "\v");
        else if (head->content)
            str = ft_strjoin(str, head->content);
        head = head->next;
    }
    cmd = ft_split(str, '\v');
    if(ft_strcmp(cmd[0], "echo") == 0)
        ft_echo(cmd);
    else if(ft_strcmp(cmd[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(cmd[0], "exit") == 0)
        ft_exit(cmd);
    else if (ft_strcmp(cmd[0], "env") == 0)
        ft_env(env);
    else if(ft_strcmp(cmd[0], "export") == 0)
        ft_export(cmd);
    else if(ft_strcmp(cmd[0], "cd") == 0)
        ft_cd(cmd);
    free(str);
    ft_free(cmd);
}