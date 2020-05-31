/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitwhitspace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:49 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:31 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static unsigned int	count_word(const char *s)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s != '\0')
			i++;
		while (*s && *s != ' ' && *s != '\t')
			s++;
	}
	return (i);
}

static unsigned int	count_word2(const char *s)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t' || *s == SEPARATOR_CHAR)
			s++;
		if (*s != '\0')
			i++;
		while (*s && *s != ' ' && *s != '\t' && *s != SEPARATOR_CHAR)
			s++;
	}
	return (i);
}

void				ft_split_norm(t_file *file, char const *s)
{
	if (file->free_cnt == 1)
		file->len1 = file->n;
	if (file->free_cnt == 2)
		file->len2 = file->n;
	while (s[file->n] && s[file->n] != ' ' && s[file->n] != '\t')
		file->n++;
}

char				**ft_strsplitwsp(char const *s, t_file *file)
{
	unsigned int	i;
	unsigned int	j;
	char			**tab;

	file->n = 0;
	j = 0;
	if (s == 0)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_word(s) + 1))))
		return (NULL);
	while (s[file->n])
	{
		while (s[file->n] == ' ' || s[file->n] == '\t')
			file->n++;
		i = file->n;
		ft_split_norm(file, s);
		if (file->n > i)
			tab[j++] = strndup(s + i, file->n - i);
		if (file->n > i)
			file->free_cnt += 1;
	}
	tab[j] = NULL;
	return (tab);
}

char				**ft_strsplit2(char const *s)
{
	unsigned int	n;
	unsigned int	i;
	unsigned int	j;
	char			**tab;

	n = 0;
	j = 0;
	if (s == 0)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_word2(s) + 1))))
		return (NULL);
	while (s[n])
	{
		while (s[n] == ' ' || s[n] == '\t' || s[n] == SEPARATOR_CHAR)
			n++;
		i = n;
		while (s[n] && s[n] != ' ' && s[n] != '\t' && s[n] != SEPARATOR_CHAR)
			n++;
		if (n > i)
			tab[j++] = strndup(s + i, n - i);
	}
	tab[j] = NULL;
	return (tab);
}
