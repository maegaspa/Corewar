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
//    int k = -1;
//    	while (++k < 3)
//    		printf("[lld] war->rtype[%d] = %d\n", k, war->rtype[k]);
    if (war->rtype[0] == DIR_CODE)
    {
    	r = war->arena[calc_addr(chariot->addr + i + 4)];
    	param1 = get_4_val(war, chariot, i);
        if (war->verbose[2] == 1 && r > 0 && r <= 16)
            printf("P %4d | lld %d r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[calc_addr(chariot->addr + 6)]);
       	if (r > 16 || r <= 0)
       	{
       		print_verbose_16(war, chariot, 7);
       		return (FAILURE);
       	}
       	else
       		print_verbose_16(war, chariot, 7);
    	chariot->registres[r - 1] = param1;
    }
    if (war->rtype[0] == IND_CODE)
    {
    	r = war->arena[calc_addr(chariot->addr + i + 2)];
    	param1 = get_2_val(war, chariot, i);
        if (war->verbose[2] == 1 && r > 0 && r <= 16)
            printf("P %4d | lld %hd r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[calc_addr(chariot->addr + 4)]);
        if (r > 16 || r <= 0)
        {
        	print_verbose_16(war, chariot, 5);
        	return (FAILURE);
        }
        else
        	print_verbose_16(war, chariot, 5);
    	param2 = read_arena(war, param1);
    	chariot->registres[r - 1] = param2;
    }
    if (param1 == 0)
       	chariot->carry = 1;
    else
    	chariot->carry = 0;
//    printf("LLD_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
