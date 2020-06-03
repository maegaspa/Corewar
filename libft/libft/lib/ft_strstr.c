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

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *h;
	const char *n;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h == *n && (*h && *n) != 0)
		{
			h++;
			n++;
		}
		if (!*n)
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
