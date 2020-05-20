/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:35 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:37:55 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			lldi_fct(t_war *war, t_chariot *chariot)
{
	int i;
   	int param1;
   	int param2;
   	int p3;
   	int r;

    i = 2;
    get_bin_ocp(chariot, war);
//    int k = -1;
//    	while (++k < 3)
//    		printf("[lldi] war->rtype[%d] = %d\n", k, war->rtype[k]);
    if (war->rtype[0] == IND_CODE)
    {
    	param1 = get_2_val(war, chariot, i);
        param2 = read_arena(war, param1);
        if (war->rtype[1] == REG_CODE)
        {
        	r = war->arena[chariot->start_pos + chariot->pc + i + 3];
            if (war->verbose[2] == 1)
                printf("P %4d | lldi %d %s r%d\n", (chariot->index + 1), param1, "a trouver", r);
        }
        if (war->rtype[1] == DIR_CODE)
        {
           	r = war->arena[chariot->start_pos + chariot->pc + i + 4];
            if (war->verbose[2] == 1)
                printf("P %4d | lldi %d %s r%d\n", (chariot->index + 1), param1, "a trouver", r);
        }
    }
    if (war->rtype[0] == REG_CODE)
    {
    	param1 = war->arena[chariot->start_pos + chariot->pc + i];
    	if (war->rtype[1] == REG_CODE)
    	{
    		param2 = war->arena[chariot->start_pos + chariot->pc + i + 1];
    		r = war->arena[chariot->start_pos + chariot->pc + i + 2];
            if (war->verbose[2] == 1)
                printf("P %4d | lldi %d %d r%d\n", (chariot->index + 1), param1, param2, r);
            print_verbose_16(war, chariot, 5);
    	}
    	if (war->rtype[1] == DIR_CODE)
    	{
    		param2 = get_2_val(war, chariot, i + 1);
    		r = war->arena[chariot->start_pos + chariot->pc + i + 3];
            if (war->verbose[2] == 1)
                printf("P %4d | lldi %d %d r%d\n", (chariot->index + 1), param1, param2, r);
            print_verbose_16(war, chariot, 6);
    	}
    }
    if (war->rtype[0] == DIR_CODE)
    {
    	param1 = get_2_val(war, chariot, i);
    	if (war->rtype[1] == DIR_CODE)
    	{
    		param2 = get_2_val(war, chariot, i + 2);
            r = war->arena[chariot->start_pos + chariot->pc + i + 4];
            if (war->verbose[2] == 1)
                printf("P %4d | lldi %d %d r%d\n", (chariot->index + 1), param1, param2, r);
            print_verbose_16(war, chariot, 7);
    	}
    	if (war->rtype[1] == REG_CODE)
    	{
    		param2 = war->arena[chariot->start_pos + chariot->pc + i + 2];
            r = war->arena[chariot->start_pos + chariot->pc + i + 3];
            if (war->verbose[2] == 1)
                printf("P %4d | lldi %d %d r%d\n", (chariot->index + 1), param1, param2, r);
            print_verbose_16(war, chariot, 6);
    	}
    }
    p3 = ((param1 + param2) % IDX_MOD);
    p3 = ((chariot->start_pos - i + p3) % MEM_SIZE);
    if (p3 == 0)
    	chariot->carry = 1;
    else
    	chariot->carry = 0;
    chariot->registres[r - 1] = p3;
//    printf("LLDI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
