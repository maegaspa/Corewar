/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_float_param2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:06 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_width_noprec_nopoint(t_flags flags, int pre)
{
	if (pre == 1)
		ft_putncaract(' ', flags.width - 8 - flags.plus);
	ft_putncaract('+', flags.plus);
	if (pre == 2)
		ft_putncaract('0', flags.width - 8 - flags.plus);
	ft_putstr("0.000000");
	if (pre == 3)
		ft_putncaract(' ', flags.width - 8 - flags.plus);
}

void	print_width_noprec_point_nul(t_flags flags)
{
	if (!flags.minus && !flags.zero)
		ft_putncaract(' ', flags.width - flags.hashtag - 1);
	ft_putncaract('+', flags.plus);
	if (flags.hashtag && !flags.minus)
		ft_putncaract('0', flags.width - flags.hashtag - flags.plus - 1);
	ft_putchar('0');
	ft_putncaract('.', flags.hashtag);
	if (flags.minus == 1)
		ft_putncaract(' ', flags.width - flags.hashtag - 1);
}

int		width_noprec_point_nul(t_flags flags)
{
	if (!flags.minus && !flags.zero)
	{
		ft_putncaract(' ', flags.width - 1 - flags.plus - flags.hashtag);
		width_noprec_point_nul(flags);
	}
	else if (flags.minus)
	{
		width_noprec_point_nul(flags);
		ft_putncaract(' ', flags.width - 1 - flags.plus - flags.hashtag);
	}
	else if (flags.zero)
	{
		ft_putncaract('+', flags.plus);
		if (flags.width == 2)
			ft_putncaract('0', flags.width - flags.plus - flags.hashtag + 1);
		else if (flags.width == 1)
			ft_putncaract('0', flags.width - flags.plus - flags.hashtag + 2);
		else
			ft_putncaract('0', flags.width - flags.plus - flags.hashtag);
		ft_putncaract('.', flags.hashtag);
	}
	return (flags.width);
}

int		str_find(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	if (str[i] == c)
		return (1);
	return (0);
}

void	dec_arround(t_check_float *c_float, long double dec, t_flags flags)
{
	int		i;
	char	*tmp;

	i = 0;
	while (c_float->decstr[i] == '.')
		i++;
	if (c_float->decstr[i] >= '5')
	{
		if (c_float->nbstr[c_float->nblen - 1] == '9')
		{
			tmp = ft_ftoa(dec + 1, flags.precision);
			c_float->nbstr2 = ft_strsubfree(tmp, 0, c_float->nblen + 1);
			c_float->nblen++;
		}
		else
		{
			tmp = ft_ftoa(dec + 1, flags.precision);
			c_float->nbstr2 = ft_strsubfree(tmp, 0, c_float->nblen);
		}
		if (c_float->yes)
			ft_strdel(&c_float->nbstr);
		c_float->nbstr = c_float->nbstr2;
		ft_strdel(&c_float->nbstr2);
	}
}
