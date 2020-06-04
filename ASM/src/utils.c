/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:56 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:33 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*gettohexa(int n)
{
	int temp;
	int tmp;
	int len;
	int i;
	int neg;
	char *hex;

	i = 0;
	len = 0;
	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	tmp = n;
	while (tmp /= 10)
		len++;
	if (!(hex = ft_strnew(len + neg)))
		return (NULL);
	while(n != 0) 
	{
		temp = n % 16; 
		if (temp < 10) 
		{ 
			hex[i] = temp + 48; 
			i++; 
		} 
		else
		{
			hex[i] = temp + 87; 
			i++; 
		} 
		n = n/16; 
	}
	hex[i] = '\0';
	return (ft_strrev(hex));
}

int			get_base_length(char *base)
{
	int	base_length;
	int	j;

	base_length = 0;
	while (base[base_length])
	{
		if (base[base_length] == '-' || base[base_length] == '+')
			return (0);
		j = base_length + 1;
		while (base[j])
		{
			if (base[base_length] == base[j])
				return (0);
			++j;
		}
		++base_length;
	}
	if (base_length < 2)
		return (0);
	return (base_length);
}

int			ft_atoi_base(char *str, char *base)
{
	int	s;
	int	i;
	int	res;
	int	negative;
	int	base_length;

	if (!(base_length = get_base_length(base)) || !check_errors(str, base))
		return (0);
	s = 0;
	while (str[s] != '\0' && (str[s] == ' ' || str[s] == '\t'))
		s++;
	i = s - 1;
	res = 0;
	negative = 1;
	while (str[++i] && (((str[i] == '-' || str[i] == '+') && i == s) ||
				(str[i] != '-' && str[i] != '+')))
	{
		if (str[i] == '-')
			negative = -1;
		else if (str[i] != '+')
			res = (res * base_length) + (get_nb(str[i], base));
	}
	return (res * negative);
}
