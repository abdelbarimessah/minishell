/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:11:22 by amessah           #+#    #+#             */
/*   Updated: 2022/06/09 00:10:45 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalnum(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
int ft_exit(char **str)
{
	int exit_nb;

	exit_nb = 0;
	
	if(str[0] && !str[1])
	{
		ft_putstr_fd("exit\n",1);
		exit(exit_nb);
	}
	else
	{
		if(ft_isalnum(str[1]) == 0)
		{
			ft_putstr_fd("exit\nminishell: exit: ",2);
			ft_putstr_fd(str[1],2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_nb = 255;
		}
		else
		{
			ft_putstr_fd("exit\n",1);
			exit_nb = ft_atoi(str[1]);
		}
		exit(exit_nb);
	}
	return (0);
}