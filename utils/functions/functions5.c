/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:14:38 by amessah           #+#    #+#             */
/*   Updated: 2022/06/25 21:42:09 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		a;
	char	*s;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = ft_strdup("");
		i = 1;
	}
	if (!s2)
		return (NULL);
	a = ft_strlen(s1);
	s = (char *)malloc(a + ft_strlen(s2) + 1);
	if (s == NULL)
		return (NULL);
	s = movee(s1, s2, s);
	if (i == 1)
		free(s1);
	return (s);
}

char    *ft_strjoin3(char *s1, char *s2)
{
	int		a;
	char	*s;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!s1)
	{
		s1 = ft_strdup("");
		i = 1;
	}
	if (!s2)
		return (NULL);
	a = ft_strlen(s1);
	s = (char *)malloc(a + ft_strlen(s2) + 1);
	if (s == NULL)
		return (NULL);
	if (s1 && s2)
	{
		while (s1[i])
			s[k++] = s1[i++];
		i = 0;
		while (s2[i])
			s[k++] = s2[i++];
		free((char *)s1);
		s[k] = '\0';
		return (s);
	}
	if (i == 1)
		free(s1);
	return (s);
}
