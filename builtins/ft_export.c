/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:39:36 by amessah           #+#    #+#             */
/*   Updated: 2022/05/31 02:10:55 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_export(char **env)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    while(env[i])
        i++;
    while( j < i)
    {
        if(ft_strcmp(env[j], env[j + 1]) > 0 && env[j + 1])
        {
			tmp = env[j];
			env[j] = env[j + 1];
			env[j + 1] = tmp;
			j = -1;
		}
		j++;
    }
    i = 0;
    while(env[i])
    {
       ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
        i++;
    }
}