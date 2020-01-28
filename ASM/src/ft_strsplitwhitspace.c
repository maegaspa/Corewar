#include "../includes/asm.h"
#include <stdio.h>

void 			free_split(t_file *file)
{
	int i;

	i = -1;
	while (++i <= file->free_cnt)
		free(file->split[i]);
	free(file->split);
}

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

char				**ft_strsplitwsp(char const *s, t_file *file)
{
	unsigned int	n;
	unsigned int	i;
	unsigned int	j;
	char			**tab;

	n = 0;
	j = 0;
	if (s == 0)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_word(s) + 1))))
		return (NULL);
	while (s[n])
	{
		while (s[n] == ' ' || s[n] == '\t')
			n++;
		i = n;
		if (file->free_cnt == 1)
			file->len1 = n;
		if (file->free_cnt == 2)
			file->len2 = n;
		while (s[n] && s[n] != ' ' && s[n] != '\t')
			n++;
		if (n > i)
			tab[j++] = strndup(s + i, n - i);
		if (n > i)
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