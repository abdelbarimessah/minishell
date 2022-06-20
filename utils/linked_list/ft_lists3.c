/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:38:38 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/20 15:36:08 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstclearp(t_point **lst)
{
	t_point	*head;

	if (!lst)
		return ;
	while (*lst)
	{
		head = *lst;
		*lst = (*lst)->next;
		if (head->content)
			free(head->content);
		free(head);
	}
	*lst = NULL;
}

t_point	*ft_lstnewp(void *content)
{
	t_point	*new;

	new = malloc(sizeof(t_point));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_point	*ft_lstlastp(t_point *lst)
{
	t_point	*last;

	last = lst;
	if (!last)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_lstadd_backp(t_point **lst, t_point *new)
{
	t_point	*elem;

	if (*lst)
	{
		elem = *lst;
		elem = ft_lstlastp(*lst);
		elem->next = new;
	}
	*lst = new;
}
