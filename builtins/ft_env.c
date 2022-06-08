/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:32:13 by amessah           #+#    #+#             */
/*   Updated: 2022/06/08 16:02:34 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *init_env(void *data)
{
	t_env *list;
	
	list = malloc(sizeof(t_env));
	if(!list)
		return (NULL);
	list->next = NULL;
	list->value = ft_strdup(data);
	return (list);
}
t_env *add_to_list(t_env *list,void *data)
{
	t_env *noued;
	
	if(!list || !data)
		return (NULL);
	while(list->next)
		list = list->next;
	if(!(noued = malloc(sizeof(t_env))))
		return (NULL);
	noued->next = NULL;
	noued->value = ft_strdup(data);
	noued->export_value = ft_strdup(data);
	list->next = noued;
	return (list);
}

t_env *search_and_replce_OLDPWD(t_env *list, void *data)
{
	if(!list || !data)
		return (NULL);
	while (list)
	{
		if(!ft_strncmp(list->value, "OLDPWD", 6))
		{
			list->value = data;
		}
		list = list->next;
	}
	return (list);
}

t_env *search_and_replce_PWD(t_env *list, void *data)
{
	if(!list || !data)
		return (NULL);
	while (list)
	{
		if(!ft_strncmp(list->value, "PWD", 3))
		{
			list->value = data;
		}
		list = list->next;
	}
	return (list);
}

t_env	*list_env(char **env)
{
	t_env *list;
	t_env *head;
	int i;
	
	i = 1;
	list = init_env(env[0]);
	head = list;
	while(env[i])
	{
		// if(!ft_strncmp(env[i], "OLDPWD", 6))
		// 	i++;
		list = add_to_list(list,env[i]);
		i++;
	}
	return (head);
}

int check_for_equal(char *str)
{
	int cont;
	int i;
	
	cont = 0;
	i = 0;
	if(!str)
		return(0);
	while(str[i])
	{
		if(str[i] == '=')
			cont++;
		i++;
	}
	if(cont != 0)
		return (1);
	return (0);
}

void	ft_env(void)
{
	t_env *tmp;
	
	tmp = g_glob;
	while(tmp)
	{
		if(!ft_strncmp(tmp->value, "OLDPWD",6) && g_glob->index == 0 )
			tmp = tmp->next;
		if(check_for_equal(tmp->value) != 0)
		{
			ft_putstr_fd(tmp->value,1);
			ft_putstr_fd("\n",1);
		}
		tmp = tmp->next;
	}
}
