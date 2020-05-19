/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:08 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:39:03 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			and_fct(t_war *war, t_chariot *chariot)
{
	int i;
	int param1;
	int param2;
	int r;

	get_bin_ocp(chariot, war);
	if (war->rtype[0] == 1)//REG
	{
		param1 = chariot->registres[(unsigned char)war->arena[chariot->start_pos + chariot->pc + 2]];
		i = 3;
	}
	if (war->rtype[0] == 2)//IND
	{
		param1 = get_2_val(war, chariot, 2);
		param1 %= IDX_MOD;
		i = 4;
	}
	if (war->rtype[0] == 4)//DIR
	{
		param1 = get_4_val(war, chariot, 2);
		i = 6;
	}


	if (war->rtype[1] == 1)
	{
		param2 = chariot->registres[(unsigned char)war->arena[chariot->start_pos + chariot->pc + i]];

		i++;
	}
	if (war->rtype[1] == 2)
	{
		param2 = get_2_val(war, chariot, i);
		param2 %= IDX_MOD;
		i += 2;
	}
	if (war->rtype[1] == 4)
	{
		param2 = get_4_val(war, chariot, i);
		i += 4;
	}
	r = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i];
	chariot->registres[r - 1] = param1 & param2;
	printf("AND_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	return (0);
}
