/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:06 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_octa_else(unsigned long dec, t_flags flags, t_check_octa *c_octa)
{
	if (flags.hashtag && ((c_octa->surplus != 1 && dec != 0) || flags.point))
		put_init("0", c_octa);
	c_octa->nb = 0;
	if ((dec != 0) || (dec == 0 && !flags.point))
		ft_putstro(c_octa->str, flags);
	if (dec != 0)
		c_octa->nb = ft_strlen(c_octa->str) + c_octa->surplus;
	if (dec == 0 && !flags.point)
		c_octa->nb = ft_strlen(c_octa->str) - flags.hashtag;
	return (c_octa->nb);
}
