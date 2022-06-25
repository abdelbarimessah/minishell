/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_token_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:23:15 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/25 21:13:23 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	spc_tok(char *str, t_list **node, t_vars *var)
{
	while (str[var->ct_i] == ' ')
		var->ct_i++;
	if (!str[var->ct_i])
		return (0);
	ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), WSPACE));
	var->ct_i--;
	return (1);
}

int	dol_tok_utils(char *str, t_list **node, t_vars *var)
{
	char	*str1;

	if (!str[var->ct_i + 1] || str[var->ct_i + 1] == ' '
		|| str[var->ct_i + 1] == '$')
	{
		ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WORD));
		var->ct_i++;
		return (var->ct_i);
	}
	else if (str[var->ct_i + 1] == '?')
	{
		str1 = ft_itoa(g_glob->exit_status);
		ft_lstadd_back(node, ft_lstnew
			(ft_strdup(str1), WORD));
		var->ct_i++;
		free(str1);
		return (var->ct_i);
	}
	else if (ft_isdigitt(str[var->ct_i + 1]))
	{
		var->ct_i++;
		var->ct_s = ft_substr(str, var->ct_i, var->ct_j - var->ct_i);
		if (var->ct_s)
			ft_lstadd_back(node, ft_lstnew(ft_strdup(var->ct_s), WORD));
		return (var->ct_i);
	}
	return (0);
}

int	dol_tok(char *str, t_list **node, t_vars *var)
{
	int		state;
	char	*strr;

	state = dol_tok_utils(str, node, var);
	if (state)
		return (state);
	else
	{
		var->ct_j = var->ct_i + 1;
		while (ft_isdigitt(str[var->ct_j])
			|| ft_isalphaa(str[var->ct_j]) || str[var->ct_j] == '_')
			var->ct_j++;
		strr = ft_substr(str, var->ct_i + 1, var->ct_j - (var->ct_i + 1));
		var->ct_s = get_from_env(var->ct_env1, strr);
		free(strr);
		if (var->ct_s)
			ft_lstadd_back(node, ft_lstnew(ft_strdup(var->ct_s), WORD));
		else if (str[var->ct_i + 1] == '/')
		{
			var->ct_st = ft_substr(str, var->ct_i, var->ct_j - var->ct_i);
			ft_lstadd_back(node, ft_lstnew(ft_strdup(var->ct_st), WORD));
			free(var->ct_st);
		}
		var->ct_i += (var->ct_j - var->ct_i);
	}
	return (var->ct_i);
}

int	herdoc_dquo(char *str, t_vars *var)
{
	if (str[var->ct_i] == '"' && str[var->ct_i + 1] == '"')
	{
		var->ct_sb = ft_strdup("");
		var->ct_i += 2;
		var->ct_j = 1;
	}
	else
	{
		var->ct_i++;
		var->ct_j = 0;
		while (str[var->ct_i] && str[var->ct_i] != '"')
		{
			var->ct_i++;
			var->ct_j++;
		}
		if (!str[var->ct_i])
			return (printf("double quotes not closed !\n"), 0);
		else
		{
			var->ct_sb = ft_substr(str, var->ct_i - var->ct_j, var->ct_j);
			var->ct_limiter = ft_strjoin(var->ct_limiter, var->ct_sb);
		}
		var->ct_i++;
	}
	return (var->ct_i);
}

int	herdoc_squo(char *str, t_vars *var)
{
	if (str[var->ct_i] == '\'' && str[var->ct_i + 1] == '\'')
	{
		var->ct_sb = ft_strdup("");
		var->ct_i += 2;
		var->ct_j = 1;
	}
	else
	{
		var->ct_i++;
		var->ct_j = 0;
		while (str[var->ct_i] && str[var->ct_i] != '\'')
		{
			var->ct_i++;
			var->ct_j++;
		}
		if (!str[var->ct_i])
			return (printf("single quotes not closed !\n"), 0);
		else
		{
			var->ct_sb = ft_substr(str, var->ct_i - var->ct_j, var->ct_j);
			var->ct_limiter = ft_strjoin(var->ct_limiter, var->ct_sb);
		}
		var->ct_i++;
	}
	return (var->ct_i);
}
