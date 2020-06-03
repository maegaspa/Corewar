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

int			st_fct(t_war *war, t_chariot *chariot)
{
	unsigned int	val;

	verbose(war, chariot);
	if (war->rtype[1] == REG_CODE)
		chariot->registres[war->param[1] - 1] =
			chariot->registres[war->param[0] - 1];
	else
	{
		val = chariot->registres[war->param[0] - 1];
		write_on_arena(war, val,
			calc_addr(C_POS + (war->param[1] % IDX_MOD)), 4);
	}
	return (0);
}
