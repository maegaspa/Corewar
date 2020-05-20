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
	int pos;

	i = 3;
	pos = chariot->start_pos + chariot->pc;
//	printf("ST_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	get_bin_ocp(chariot, war);
//	int k = -1;
//    while (++k < 3)
//    	printf("[st] war->rtype[%d] = %d\n", k, war->rtype[k]);
	if (chariot->registres[0] == 0)
		chariot->carry = 1;
	if (war->rtype[1] == IND_CODE)
	{
		param = get_2_val(war, chariot, i);
		if (war->verbose[2] == 1)
        	printf("P %4d | st r%d %d\n", (chariot->index + 1), (unsigned char)war->arena[pos + 2], param);
        print_verbose_16(war, chariot, 6);
		war->arena[pos + (param % IDX_MOD)] = chariot->registres[war->arena[(pos + 1)] - 1];
	}
	else
		if (war->verbose[2] == 1)
        	printf("P %4d | st r%d %d\n", (chariot->index + 1), (unsigned char)war->arena[pos + 2], (unsigned char)war->arena[pos + 3]);
        print_verbose_16(war, chariot, 5);
		chariot->registres[war->arena[(pos + 2)] - 1] = chariot->registres[war->arena[(pos + 1)] - 1];
	return (0);
}
