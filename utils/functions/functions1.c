/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:55:46 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/12 15:22:25 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(char *s)
{	
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*copie;
	char	*src1;

	src1 = (char *)src;
	i = 0;
	copie = malloc(sizeof(char) * (ft_strlen(src1) + 1));
	if (!(src) || (copie == NULL))
		return (NULL);
	while (src1[i] != '\0')
	{
		copie[i] = src1[i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

char	*ft_substr(char *s, int start, int len)
{
	int			lenght;
	int			x;
	char		*sub;

	x = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	lenght = ft_strlen(&s[start]);
	if (lenght >= len)
		lenght = len;
	sub = malloc(lenght + 1);
	if (!sub)
		return (NULL);
	while (s[start] && x < len)
		sub[x++] = s[start++];
	sub [x] = '\0';
	return (sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] != '\0' || str2[i] != '\0' ) && i < n)
	{
		if (s1[i] != s2[i])
			return ((str1[i] - str2[i]));
		i++;
	}
	return (0);
}

char	*movee(char *s1, char *s2, char *s)
{
	int		a;
	int		i;

	a = ft_strlen(s1);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
	}
	i = 0;
	while (s2[i])
	{
		s[a] = s2[i];
		a++;
		i++;
	}
	s[a] = '\0';
	return (s);
}

char	*ft_strjoin_nf(char *s1, char *s2)
{
	int		a;
	int		i;
	char	*s;

	i = 0;
	if (!s2)
		return (NULL);
	a = ft_strlen(s1);
	s = (char *)malloc(a + ft_strlen(s2) + 1);
	if (s == NULL)
		return (NULL);
	s = movee(s1, s2, s);
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		a;
	int		i;
	char	*s;

	i = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	a = ft_strlen(s1);
	s = (char *)malloc(a + ft_strlen(s2) + 1);
	if (s == NULL)
		return (NULL);
	s = movee(s1, s2, s);
	// free(s1);
	return (s);
}

int ft_skip_space(char *str, int i)
{
	while(str[i] == ' ')
		i++;
	return i;
}

int	ft_error(char *str, int retu)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (retu);
}

char	*ft_strchr(const char *str, int pos)
{
	int		i;
	char	*str1;
	char	c1;

	str1 = (char *)str;
	c1 = (char)pos;
	i = 0;
	if (c1 == '\0')
		return (str1 + ft_strlen(str1));
	while (str1[i] != '\0')
	{
		if (str1[i] == c1)
			return (str1 + i);
		i++;
	}
	return (NULL);
}