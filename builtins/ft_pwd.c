/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:03:43 by amessah           #+#    #+#             */
/*   Updated: 2022/05/28 13:15:38 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd()
{
	char path[PATH_MAX + 1];

	path[PATH_MAX] = '\0';
	getcwd(path,sizeof(path));
	ft_putstr_fd(path,1);
	ft_putstr_fd("\n",1);
}