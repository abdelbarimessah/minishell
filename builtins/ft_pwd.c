/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:03:43 by amessah           #+#    #+#             */
/*   Updated: 2022/06/23 01:29:40 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	path[PATH_MAX + 1];

	path[PATH_MAX] = '\0';
	if (!getcwd(path, sizeof(path)))
		g_glob->exit_status = 0;
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}
