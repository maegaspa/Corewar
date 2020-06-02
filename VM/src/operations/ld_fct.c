/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:23 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/27 01:05:20 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	get_4_val(t_war *war, t_chariot *chariot, int i)
{
	int				tmp;
	unsigned int	res;

	res = 0;
	tmp = i;
	while (i < tmp + 4)
	{
		res = res << 8;
		res = res + (unsigned char)war->arena[calc_addr(C_POS + i)];
		i++;
	}
	return (res);
}

int	ld_fct(t_war *war, t_chariot *chariot)
{
	int		cell_load;

	verbose(war, chariot);
	if (war->param[1] > 0 && war->param[1] <= 16)
	{
		if (war->rtype[0] == DIR_CODE)
			chariot->registres[war->param[1] - 1] = war->param[0];
		else
		{
			cell_load = ft_load(war, 4,
				calc_addr(C_POS + (war->param[0] % IDX_MOD)));
			chariot->registres[war->param[1] - 1] = cell_load;
		}
	}
	if (chariot->registres[war->param[1] - 1] == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
	return (0);
}
