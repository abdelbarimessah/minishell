/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:30:27 by amessah           #+#    #+#             */
/*   Updated: 2022/06/12 02:46:26 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\f'
		||str[i] == '\v' || str[i] == '\r')
		i++;
	if (str[i] == '-' )
		s = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return (r * s);
}

char	**new_env_function(t_env *list)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(10000);
	if (!list)
		return (NULL);
	while (list)
	{
		env[i] = list->value;
		list = list->next;
		i++;
	}
	return (env);
}
