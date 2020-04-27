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
	int i;
    int param1;
    int param2;
    int r;

    i = 2;
    param2 = 0;
    get_bin_ocp(chariot, war);
    if (war->rtype[0] == T_DIR)
    {
    	param1 = get_4_val(war, chariot, i);
    	r = war->arena[chariot->start_pos + chariot->pc + i + 4];
    	printf("param1 = %d et param2 = %d\n", param1, r);
    	chariot->registres[r - 1] = param1;
    }
    if (war->rtype[0] == T_IND)
    {
    	param1 = get_2_val(war, chariot, i);
    	param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1) % MEM_SIZE] << 24;
    	param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 1) % MEM_SIZE] << 16;
    	param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 2) % MEM_SIZE] << 8;
    	param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 3) % MEM_SIZE];
    	r = war->arena[chariot->start_pos + chariot->pc + i + 2];
    	printf("param1 = %d et param2 = %d et r = %d\n", param1, param2, r);
    	chariot->registres[r - 1] = param1;
    }
    if (param1 == 0)
       	chariot->carry = 1;
    else
    	chariot->carry = 0;
    printf("LLD_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	return (0);
}
