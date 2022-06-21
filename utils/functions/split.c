/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:02:35 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 21:08:43 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cleari(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (0);
}

static int	counter(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			count++;
		}
		else
			s++;
	}
	return (count);
}

static char	*create_word(const char *s, int start, int end)
{
	char	*word;
	int		i;
	int		word_len;

	i = 0;
	word_len = end - start;
	word = (char *)malloc(sizeof(char) * word_len + 1);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	filler(char **str, const char *s, char c)
{
	int		start;
	int		end;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			end = i;
			str[k] = create_word(s, start, end);
			if ((str[k]) == NULL)
				return (cleari(str, k));
			k++;
		}
		else
			i++;
	}
	str[k] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		checker;

	checker = 1;
	if (!s)
		return (NULL);
	str = (char **)malloc(((counter(s, c) + 1) * (sizeof(char *))));
	if (str == NULL)
		return (NULL);
	checker = filler(str, s, c);
	if (checker == 0)
		return (NULL);
	return (str);
}
