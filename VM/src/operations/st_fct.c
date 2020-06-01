/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:40 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/27 22:01:14 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			bytecode_to_int(t_war *war, int addr, int size)
{
	int		result;
	int		sign;
	int			i;

	result = 0;
	sign = (war->arena[calc_addr(addr)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((war->arena[calc_addr(addr + size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += (war->arena[calc_addr(addr + size - 1)] << (i++ * 8));
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

void		int_to_bytecode(t_war *war, int addr, int value, int size)
{
	char i;

	i = 0;
	while (size)
	{
		war->arena[calc_addr(addr + size - 1)] = (unsigned char)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

unsigned char		*itoo(int nb)
{
	unsigned char	*tab;

	tab = malloc(sizeof(unsigned char) * 4);
	tab[0] = (nb & 0xFF000000) >> 24;
	tab[1] = (nb & 0xFF0000) >> 16;
	tab[2] = (nb & 0xFF00) >> 8;
	tab[3] = (nb & 0xFF);
	return (tab);
}

int			st_fct(t_war *war, t_chariot *chariot)
{
	unsigned int val;
	unsigned char *tab;
	int i;

	i = -1;
	verbose(war, chariot);
	if (war->rtype[1] == REG_CODE)
		chariot->registres[war->param[1] - 1] = chariot->registres[war->param[0] - 1];
	else
	{
		val = chariot->registres[war->param[0] - 1];
		write_on_arena(war, val, calc_addr(C_POS + (war->param[1] % IDX_MOD)), 4);
	}
	return (0);
}
