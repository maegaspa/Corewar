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

char	*ft_strtrim(char const *s)
{
	char	*d;
	int		i;
	int		j;
	int		tmp;

	i = 0;
	j = 0;
	if (s == 0)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (*s != 0)
		j = ft_strlen(s) - 1;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	j++;
	if (j - i < 0)
		i = 0;
	if (!(d = (char*)malloc(sizeof(char) * j - i + 1)))
		return (0);
	tmp = 0;
	while (i < j)
		d[tmp++] = s[i++];
	d[tmp] = '\0';
	return (d);
}
