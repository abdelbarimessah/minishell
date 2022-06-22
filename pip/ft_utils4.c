/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:16:02 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/20 14:19:24 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	status_child(void)
{
	if (WIFEXITED(g_glob->g_pid))
		g_glob->exit_status = WEXITSTATUS(g_glob->g_pid);
	if (WIFSIGNALED(g_glob->g_pid))
	{
		g_glob->exit_status = WTERMSIG(g_glob->g_pid);
		if (g_glob->exit_status != 131)
			g_glob->exit_status += 128;
	}
}

void	printf_list_z(t_env *lst)
{
	while (lst)
	{
		printf("%s\n", lst->value);
		lst = lst->next;
	}
	puts("");
}

char	*get_shlvl(void)
{
	t_env	*list;
	char	*str;
	char	**num;
	char	*tmp;

	list = g_glob;
	while (list)
	{
		if (!ft_strncmp(list->value, "SHLVL", 5))
		{
			str = list->value;
			break ;
		}
		list = list->next;
	}
	num = ft_split(str, '=');
	tmp = ft_strdup(num[1]);
	ft_free(num);
	return (tmp);
}

void	incrument_shlvl(void)
{
	char	**str;
	int		len;
	char	*tmp;
	char	*tmp1;
	char	**str1;

	tmp1 = get_shlvl();
	g_glob->shlvl_val = ft_atoi(tmp1);
	if (g_glob->shlvl_val < 0)
		g_glob->shlvl_val = 0;
	else
		g_glob->shlvl_val++;
	tmp = ft_itoa(g_glob->shlvl_val);
	len = ft_strlen(tmp);
	str = malloc(sizeof(char *) * (len + 2));
	str1 = malloc(sizeof(char *) * (len + 2));
	str[0] = ft_strdup("export");
	str1[0] = ft_strdup("unset");
	str[1] = ft_strjoin("SHLVL=", tmp);
	str1[1] = ft_strjoin("SHLVL", tmp);
	ft_unset(str1);
	ft_export(str);
	free(tmp);
	free(tmp1);
}
