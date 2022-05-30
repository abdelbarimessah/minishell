/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:32:13 by amessah           #+#    #+#             */
/*   Updated: 2022/05/30 14:14:18 by amessah          ###   ########.fr       */
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
	list->next = noued;
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
		list = add_to_list(list,env[i]);
		list = add_to_list(list,"\n");
		i++;
	}
		list = add_to_list(list,"\n");
	return (head);
}

void	ft_env(char **env)
{
	t_env *list;

	list = list_env(env);
	while(list->next)
	{
		ft_putstr_fd(list->value,2);
		// ft_putstr_fd("\n",2);
		list = list->next;
	}
}