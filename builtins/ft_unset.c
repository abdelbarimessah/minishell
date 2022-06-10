/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:32:13 by amessah           #+#    #+#             */
/*   Updated: 2022/06/10 03:38:53 by amessah          ###   ########.fr       */
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


void deleteNode_from_env(t_env **head_ref, char *str)
{
    t_env *temp ;
    t_env *prev;
    
    temp = *head_ref;
    if (temp != NULL && !ft_strcmp(temp->value,str)) 
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && ft_strcmp(temp->value,str)) 
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

void deleteNode_from_export(t_env **head_ref, char *str)
{
    t_env *temp ;
    t_env *prev;
    
    temp = *head_ref;
    if (temp != NULL && !ft_strcmp(temp->export_value,str)) 
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && ft_strcmp(temp->export_value,str)) 
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
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
    
    list = g_glob;
    tmp = g_glob;
    i = 1;
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
            deleteNode_from_env(&list,str[i]);
            // deleteNode_from_export(&tmp,str[i]);
        }
        i++;
    }
}