/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:32:13 by amessah           #+#    #+#             */
/*   Updated: 2022/06/12 00:19:24 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	ft_isalpha(int c)
{
	if ((c > 'Z' && c < 'a') || c > 'z' || c < 'A')
	{
		return (0);
	}
	return (1);
}

int	ft_isalnum1(int c)
{
	if (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
		return (0);
	return (1);
}

void deleteNode_from_env(t_env *list, char *str, int len)
{
    t_env *tmp;

    if(!ft_strncmp(list->value,str,len))
    {
        g_glob = g_glob->next;
        free(g_glob->value);
        free(g_glob->export_value);
    }
    else
    {
        while(list)
        {
            tmp = list->next;
            if(!ft_strncmp(tmp->value,str,len))
                break ;
            list = list->next;
        }
        list->next = tmp->next;
    }
}

void deleteNode_from_export(t_env *list, char *str,int len)
{
    t_env *tmp;

    if(!list)
        return ;
    list = list->next;
    while(list)
    {
        if(!ft_strncmp(list->export_value, str, len) && list->export_value)
        {
            tmp = list;
            list = list->next;
            free(tmp->export_value);
            // free(tmp);
            return ;
        }
        list = list->next;  
    }
}

int	check_arg(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (ft_isalpha(arg[i]) || arg[i] == '_')
	{
		while (arg[++i])
			if (!(ft_isalnum1(arg[i]) || arg[i] == '_'))
				return (0);
		return (1);
	}
	return (0);
}

void    ft_unset(char **str)
{
    int i;
    t_env *list;
    t_env *tmp;
    int len;
    
    list = g_glob;
    tmp = g_glob;
    i = 1;
    len = 0;
    while(str[i])
    {
        if(!check_arg(str[i]))
        {
            ft_putstr_fd("unset: `",2);
            ft_putstr_fd(str[i],2);
            ft_putstr_fd("': not a valid identifier\n",2);
        }
        else
        {
            len = ft_strlen(str[i]);
            deleteNode_from_env(list,str[i],len);
        }
        i++;
    }
}