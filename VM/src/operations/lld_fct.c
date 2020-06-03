/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:33 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:39:27 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			lld_fct(t_war *war, t_chariot *chariot)
{
	int		cell_load;

	verbose(war, chariot);
	if (war->param[1] >= 0 && war->param[1] < 16)
	{
		if (war->rtype[0] == DIR_CODE)
			chariot->registres[war->param[1] - 1] = war->param[0];
		else
		{
			cell_load = ft_load(war, 4, calc_addr(C_POS + war->param[0]));
			chariot->registres[war->param[1] - 1] = cell_load;
		}
	}
	if (chariot->registres[war->param[1] - 1] == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
	return (0);
}
