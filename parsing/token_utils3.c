/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:03:50 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/20 21:54:32 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_expd_utils(t_list **lst, char *s, int i)
{
	if (s[i + 1] == '"' || s[i + 1] == ' ' || s[i + 1] == '$')
		return (ft_lstadd_back(lst, ft_lstnew(ft_strdup("$"), WORD)), 2);
	else if (s[i + 1] == '?')
		return (ft_lstadd_back(lst, ft_lstnew
				(ft_strdup(ft_itoa(g_glob->exit_status)), WORD)), 2);
	else if (!ft_isalphaa(s[i + 1]) && !ft_isdigitt(s[i + 1]))
		return (ft_lstadd_back(lst, ft_lstnew(ft_strdup(""), WORD)), 2);
	else if (ft_isdigitt(s[i + 1]))
		return (2);
	return (-1);
}

int	ft_expd_dquot(t_list **lst, char *s, char **env, int i)
{
	int		j;
	char	*str;
	int		k;
	int		ret;

	k = i;
	str = NULL;
	ret = ft_expd_utils(lst, s, i);
	if (ret != -1)
		return (ret);
	else
	{
		if (s[i + 1] == '/' || s[i + 1] == '=')
		{
			str = ft_substr(str, k, i - k);
			return (ft_lstadd_back(lst, ft_lstnew(ft_strdup(str), WORD)), 0);
		}
		j = i++;
		while (ft_isdigitt(s[i]) || ft_isalphaa(s[i]) || s[i] == '_')
			i++;
		str = get_from_env(env, ft_substr(s, j + 1, i - (j + 1)));
		if (str)
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(str), WORD));
		return (i - j);
	}
}

int	expd_dquot_utils(char *s, int i, char **env, t_list **node)
{
	int	j;
	int	x;
	int	c;

	j = i;
	j = skip_dquo(s, j);
	i++;
	x = i;
	c = i - 1;
	while (++c < j)
	{
		if (s[c] == '$')
		{
			if (c - x)
				ft_lstadd_back(node, ft_lstnew(ft_substr(s, x, c - x), WORD));
			c += ft_expd_dquot(node, s, env, c);
			x = c;
		}
	}
	return (c);
}

int	ft_checker1(t_list **node, char *str, int i, char **env)
{
	t_vars	var;

	var.ck_j = i;
	if (str[var.ck_j] == '"' && str[var.ck_j + 1] == '"')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), NUL)), 0);
	var.ck_j = skip_dquo(str, var.ck_j);
	if (str[var.ck_j] == '"')
	{
		i++;
		var.ck_stri = ft_substr(str, i, var.ck_j - i);
		var.ck_x = i;
		if (ft_strchr(str, '$'))
		{
			var.ck_c = i - 1;
			var.ck_x = expd_dquot_utils(str, var.ck_c, env, node);
			if (var.ck_j - var.ck_x)
				ft_lstadd_back(node, ft_lstnew
					(ft_substr(str, var.ck_x, var.ck_j - var.ck_x), WORD));
		}
		else
			ft_lstadd_back(node, ft_lstnew(var.ck_stri, WORD));
		return (var.ck_j - i + 1);
	}
	return (printf("double quotes not closed !\n"), -1);
}

int	ft_checker2(t_list **node, char *str, int i)
{
	int	j;

	j = i;
	if (str[j] == '\'' && str[j + 1] == '\'')
	{
		ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), NUL));
		return (0);
	}
	while (str[++j])
	{
		if (str[j] == '\'')
			break ;
	}
	if (str[j] == '\'')
	{
		i++;
		ft_lstadd_back(node, ft_lstnew(ft_substr(str, i, j - i), WORD));
		return (j - i + 1);
	}
	return (-1);
}
