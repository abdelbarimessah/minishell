/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:03:43 by amessah           #+#    #+#             */
/*   Updated: 2022/06/21 15:09:59 by ntanjaou         ###   ########.fr       */
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
