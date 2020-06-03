/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:06 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		check_p_w_percent(t_flags flags)
{
	if (flags.width)
	{
		if (flags.minus)
		{
			ft_putchar('%');
			if (flags.zero)
				ft_putncaract('0', flags.width - 1);
			else
				ft_putncaract(' ', flags.width - 1);
			return (flags.width);
		}
		else
		{
			if (flags.zero)
				ft_putncaract('0', flags.width - 1);
			else
				ft_putncaract(' ', flags.width - 1);
			ft_putchar('%');
			return (flags.width);
		}
	}
	else
		ft_putchar('%');
	return (1);
}
