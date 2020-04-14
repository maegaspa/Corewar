/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:40 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:37:42 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			st_fct(t_war *war, t_chariot *chariot)
{
	int i;
	int param;

	i = 3;
	printf("ST_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	get_bin_ocp(chariot, war);
	if (chariot->registres[0] == 0)
		chariot->carry = 1;
	if (war->rtype[1] == T_IND)
	{
		param = get_2_val(war, chariot, i);
		war->arena[chariot->start_pos + chariot->pc + (param % IDX_MOD)] = chariot->registres[0];
	}
	else
		chariot->registres[1] = chariot->registres[0];
	return (0);
}
