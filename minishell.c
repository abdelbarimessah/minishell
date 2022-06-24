/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:29 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/24 22:30:50 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_initialize_one(char **env)
{
	g_glob = list_env(env);
	g_glob->point = malloc(sizeof(t_point));
	g_glob->point->content = NULL;
	g_glob->point->next = NULL;
	g_glob->index = 0;
	g_glob->index_env = 0;
	g_glob->g_pid = 0;
	incrument_shlvl();
	signal_handl();
}

void	ft_initialize_two(void)
{
	g_glob->status = 0;
	g_glob->sig = 0;
}

int	check_strr(char **str, char **env)
{
	if (!ft_strcmp((*str), "exit"))
		return (0);
	if (!check_syntax((*str)))
		free((*str));
	else
	{
		tokenizer(*str, env);
		g_glob->sig = 1;
	}
	return (1);
}

void	history(char *str)
{
	if (str[0] != '\0')
		add_history(str);
}

int	main(int ac, char **av, char **env)
{
	char	*input_str;
	char	**new_env;
	t_env	*list;

	(void)av;
	if (ac != 1)
		return (printf("program doesnt accepts args !"), 0);
	ft_initialize_one(env);
	// rl_catch_signals = 0;
	while (1)
	{
		ft_initialize_two();
		list = g_glob;
		new_env = new_env_function(list);
		input_str = readline("minishell$: ");
		utils_ctrl_d(input_str);
		if (!check_strr(&input_str, new_env))
			break ;
		history(input_str);
		free(input_str);
		ft_lstclearp(&g_glob->point);
	}
	ft_free(new_env);
	return (printf("exit\n"), 0);
}
