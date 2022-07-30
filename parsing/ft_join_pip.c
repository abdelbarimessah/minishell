/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:40:43 by amessah           #+#    #+#             */
/*   Updated: 2022/06/25 22:50:32 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_outherdc(t_list **head)
{
	(*head) = (*head)->next;
	while ((*head)->token == WSPACE && (*head)->token != END_TOK)
		(*head) = (*head)->next;
}

void	skip_outredi(t_list **head)
{
	(*head) = (*head)->next;
	while ((*head)->token == WSPACE && (*head)->token != END_TOK)
		(*head) = (*head)->next;
}

char	*loop_pip(t_list **head, char *str)
{
	while ((*head))
	{
		if ((*head)->token == PIP)
			str = ft_strjoin(str, "|");
		else if ((*head)->token == OUTPUTE_HEREDOC)
			skip_outherdc(head);
		else if ((*head)->token == INTPUTE_HEREDOC)
			(*head) = (*head)->next;
		else if ((*head)->token == OUTPUTE_REDI)
			skip_outredi(head);
		else if ((*head)->token == INPUTE_REDI)
		{
			(*head) = (*head)->next;
			while ((*head)->token == WSPACE && (*head)->token != END_TOK)
				(*head) = (*head)->next;
		}
		else if ((*head)->token == WSPACE)
			str = ft_strjoin(str, "\v");
		else if ((*head)->token == NUL)
			str = ft_strjoin(str, ft_strdup(" "));
		else if ((*head)->token == WORD)
			str = ft_strjoin(str, (*head)->content);
		(*head) = (*head)->next;
	}
	return (str);
}

void	ft_join_pipe(t_list *node, char **env)
{
	t_list	*head;
	char	*str;
	char	**str_split;
	int		num_com;

	str = ft_strdup("");
	head = node->next;
	str = loop_pip(&head, str);
	str_split = ft_split(str, '|');
	num_com = num_commande(str_split);
	free(str);
	main_pipe(num_com, str_split, env, node);
	exit(1);
}
