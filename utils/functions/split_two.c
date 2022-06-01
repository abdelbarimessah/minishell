/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:34:32 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/31 19:50:20 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	words_count(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (i == 0 || s[i - 1] == c)
		{
			if (s[i] != c && s[i] != '\0')
				words++;
		}
		i++;
	}
	return (words);
}

static void	move_word(char *from, char *to, int start, int j)
{
	int	a;

	a = 0;
	while (j > 0)
	{
		to[a] = from[start];
		a++;
		start++;
		j--;
	}
	to[a++] = '/';
	to[a] = '\0';
}

void	ft_freeee(char **p, int a)
{
	while (a >= 0)
		free(p[--a]);
	free(p);
}

static void	ft_mallocnmove(char **p, char const *s, char c)
{
	int		i;
	int		len;
	int		a;

	i = 0;
	len = 0;
	a = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i + len] != c && s[i + len] != '\0')
			len++;
		if (len != 0)
		{
			p[a] = (char *)malloc(len + 2);
			if (p[a] == NULL)
				ft_freeee(p, a);
			move_word((char *)s, p[a], i, len);
			a++;
		}
		i = i + len;
	}
}

char	**ft_split_two(char *s, char c)
{
	int		i;
	int		len;
	char	**p;

	i = 0;
	if (!s)
		return (NULL);
	len = words_count((char *)s, c);
	p = (char **)malloc(sizeof(char *) * (len + 1));
	if (p == NULL)
	{
		ft_freeee(p, len);
		return (NULL);
	}
	ft_mallocnmove(p, s, c);
	p[len] = NULL;
	return (p);
}
