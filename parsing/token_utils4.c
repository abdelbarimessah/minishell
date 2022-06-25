/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:53:23 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/25 18:22:30 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_dquo(char *s, int i)
{
	while (s[++i])
	{
		if (s[i] == '"')
			break ;
	}
	return (i);
}

void	init_vars(t_vars *var, char *str, char  **env)
{

	var->ct_i = 0;
	var->ct_j = 1;
	var->ct_env1 = env;
	while (str[var->ct_i] == ' ')
		var->ct_i++;
}
