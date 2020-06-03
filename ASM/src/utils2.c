/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:09:21 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:09:21 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/asm.h"

char		*strndup(const char *s, size_t n)
{
	char	*str;

	str = ft_memalloc(n + 1);
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

void		*ft_realloc(void *old, size_t old_size, size_t new_size)
{
	void	*new;
	size_t	cpy_size;

	if (!(new = ft_memalloc(new_size)))
		return (NULL);
	cpy_size = (old_size < new_size) ? old_size : new_size;
	if (old && cpy_size)
		ft_memcpy(new, old, cpy_size);
	if (old)
		free(old);
	return (new);
}

char	**get_file(char *filename)
{
	char	**res;
	int		i;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	res = ft_memalloc(sizeof(*res) * (2));
	i = -1;
	while (res && get_next_line(fd, &res[++i]))
		res = ft_realloc(res, sizeof(*res) * (i + 1), sizeof(*res) * (i + 2));
	res[i] = NULL;
	close(fd);
	return (res);
}

int	get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}
