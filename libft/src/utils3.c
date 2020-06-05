/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:06 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*octa_zero(char *seg)
{
	seg = ft_strnew(1);
	seg[0] = 48;
	return (seg);
}

int		ret_int(unsigned long long n, int base)
{
	int		j;

	j = 0;
	while (n != 0)
	{
		n = n / base;
		j++;
	}
	return (j);
}

int		ft_is_in_string(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o'
			|| c == 'u' || c == 'x' || c == 'X' || c == 'f'
			|| c == '%' || c == '-' || c == '+' || c == '.'
			|| (c >= 48 && c <= 57) || c == ' ' || c == '#' || c == 'l'
			|| c == 'h' || c == 'L')
		return (1);
	return (0);
}

void	put_free(long long digit, t_flags flags, t_check_digit *c_dig)
{
	digit_lower_0(digit, c_dig, flags, 0);
	ft_putncaract('0', (flags.precision - ft_strlen(c_dig->negnum)));
	ft_putstr(c_dig->negnum);
	free_digit(digit, c_dig);
}

int		ret_digit_no_op(long long digit, t_flags flags, t_check_digit c_dig)
{
	if (c_dig.yn && (flags.width > c_dig.len) && flags.precision < flags.width)
		return (flags.width + flags.space);
	if (digit < 0 && c_dig.len < flags.precision)
		return (flags.precision + 1);
	if (c_dig.len < flags.precision)
		return (flags.precision);
	else if (digit < 0)
		return (c_dig.len + 1);
	return (c_dig.len);
}
