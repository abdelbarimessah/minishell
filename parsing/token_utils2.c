/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:46:51 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 21:23:35 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	num_commande(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ret_free(char **cmd)
{
	ft_free(cmd);
	return (1);
}

int	check_cmd(char **cmd)
{
	if (!strcmp(cmd[0], "echo"))
		return (1);
	if (!strcmp(cmd[0], "cd"))
		return (1);
	if (!strcmp(cmd[0], "export"))
		return (1);
	if (!strcmp(cmd[0], "unset"))
		return (1);
	if (!strcmp(cmd[0], "pwd"))
		return (1);
	if (!strcmp(cmd[0], "env"))
		return (1);
	if (!strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

char	*ft_create_str(t_list **lst)
{
	char	*str;
	t_list	*head;

	str = ft_strdup("");
	head = *lst;
	while (head->token != END_TOK)
	{
		if (head->token == WSPACE)
			str = ft_strjoin(str, "\v");
		else if (head->token == OUTPUTE_REDI)
			break ;
		else if (head->token == INPUTE_REDI)
			break ;
		else if (head->token == OUTPUTE_HEREDOC)
			break ;
		else if (head->content)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	return (str);
}

int	ft_execute_builtins(t_list *node, char **env)
{
	t_list	*head;
	char	*str;
	char	**cmd;

	(void)env;
	head = node->next;
	str = ft_create_str(&head);
	if (!str[0])
		return (0);
	cmd = ft_split(str, '\v');
	free(str);
	if (check_cmd(cmd))
		ret_free(cmd);
	else
	{
		ft_free(cmd);
		return (0);
	}
	return (1);
}
