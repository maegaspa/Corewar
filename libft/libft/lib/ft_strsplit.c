/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:06 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static unsigned int	count_word(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static char			*strndup(const char *s, size_t n)
{
	char	*str;

	str = ft_memalloc(n + 1);
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	n;
	unsigned int	i;
	unsigned int	j;
	char			**tab;

	n = 0;
	j = 0;
	if (s == 0)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1))))
		return (NULL);
	while (s[n])
	{
		while (s[n] == c)
			n++;
		i = n;
		while (s[n] && s[n] != c)
			n++;
		if (n > i)
			tab[j++] = strndup(s + i, n - i);
	}
	tab[j] = NULL;
	return (tab);
}
