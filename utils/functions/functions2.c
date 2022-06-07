/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:04:02 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/07 17:23:24 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	char	*s;

	s = 0;
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchrr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchrr(set, s1[end - 1]) && end > start)
			end--;
		s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (!s)
			return (NULL);
		ft_strlcpy(s, &s1[start], end - start + 1);
	}
	return (s);
}

char	*ft_strchrr(char *str, int c)
{
	int	i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == (char)c)
			return (&((char *)str)[i]);
		i++;
	}
	return (0);
}

int	ft_strlcpy(char *dest, char *src, int size)
{
	int	x;
	int	i;

	x = 0;
	while (src[x] != '\0')
	{
		x++;
	}
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}

static	int	ft_len(int n)
{
	int	a;
	int	len;

	a = n;
	len = 0;
	if (a <= 0)
		len++;
	while (a != 0)
	{
		a = a / 10;
		len++;
	}
	return (len);
}

static char	*ft_pos(int n)
{
	char	*p;
	int		a;
	int		len;

	a = n;
	len = ft_len(n);
	p = (char *) malloc (len + 1);
	if (p == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	while (n != 0)
	{
		len--;
		p[len] = (n % 10) + '0';
		n = n / 10;
	}
	p[ft_len(a)] = '\0';
	return (p);
}

static char	*ft_nega(int n)
{
	char	*p;
	int		a;
	int		len;

	a = n;
	len = ft_len(n);
	p = (char *) malloc (len + 1);
	if (p == NULL)
		return (NULL);
	p[0] = '-';
	if (n == 0)
		p[0] = '0';
	while (n != 0)
	{
		len--;
		p[len] = -(n % 10) + '0';
		n = n / 10;
	}
	p[ft_len(a)] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	if (n < 0)
		return (ft_nega(n));
	else
		return (ft_pos(n));
}