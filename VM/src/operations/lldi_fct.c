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
    if (war->rtype[0] == IND_CODE)
    {
    	param1 = get_2_val(war, chariot, i);
        param2 = read_arena(war, param1);
        if (war->rtype[1] == REG_CODE)
        {
        	r = war->arena[calc_addr(chariot->addr + i + 3)];
            war->tmp = war->arena[calc_addr(chariot->addr + i + 2)];
            if (war->verbose[2] == 1 && r > 0 && r <= 16)
            {
                printf("P %4d | lldi %hd %d r%d\n", (chariot->index + 1), param1, war->tmp, r);
                printf("       | -> load to  %hd + %d = %d (with pc and mod %d)\n", param1, war->tmp, param1 + war->tmp, (chariot->pc + ((param1 + war->tmp) % IDX_MOD)));
            }
            print_verbose_16(war, chariot, 6);
        }
        if (war->rtype[1] == DIR_CODE)
        {
           	r = war->arena[calc_addr(chariot->addr + i + 4)];
            war->tmp = get_2_val(war, chariot, i + 2);
            if (war->verbose[2] == 1 && r > 0 && r <= 16)
            {
                printf("P %4d | lldi %d %hd r%d\n", (chariot->index + 1), param1, war->tmp, r);
                printf("       | -> load to  %d + %hd = %d (with pc and mod %d)\n", param1, war->tmp, param1 + war->tmp, (chariot->pc + ((param1 + war->tmp) % IDX_MOD)));
            }
            if (r > 16 || r <= 0)
            {
            	print_verbose_16(war, chariot, 7);
            	return (FAILURE);
            }
            else
            	print_verbose_16(war, chariot, 7);
        }
    }
    if (war->rtype[0] == REG_CODE)
    {
    	param1 = war->arena[calc_addr(chariot->addr + i)];
    	if (war->rtype[1] == REG_CODE)
    	{
    		param2 = war->arena[calc_addr(chariot->addr + i + 1)];
    		r = war->arena[calc_addr(chariot->addr + i + 2)];
            if (war->verbose[2] == 1 && r > 0 && r <= 16)
            {
                printf("P %4d | lldi %d %d r%d\n", (chariot->index + 1), param1, param2, r);
                printf("       | -> load to %d + %d = %d (with pc and mod %d)\n", param1, param2, param1 + param2, (chariot->pc + ((param1 + param2) % IDX_MOD)));
            }
            if (r > 16 || r <= 0)
            {
            	print_verbose_16(war, chariot, 5);
            	return (FAILURE);
            }
            else
            	print_verbose_16(war, chariot, 5);
    	}
    	if (war->rtype[1] == DIR_CODE)
    	{
    		param2 = get_2_val(war, chariot, i + 1);
    		r = war->arena[calc_addr(chariot->addr + i + 3)];
            if (war->verbose[2] == 1 && r > 0 && r <= 16)
            {
                printf("P %4d | lldi %d %hd r%d\n", (chariot->index + 1), param1, param2, r);
                printf("       | -> load to %d + %hd = %d (with pc and mod %d)\n", param1, param2, param1 + param2, (chariot->pc + ((param1 + param2) % IDX_MOD)));
            }
            if (r > 16 || r <= 0)
           	{
            	print_verbose_16(war, chariot, 6);
            	return (FAILURE);
            }
            else
            	print_verbose_16(war, chariot, 6);
    	}
    }
    if (war->rtype[0] == DIR_CODE)
    {
    	param1 = get_2_val(war, chariot, i);
    	if (war->rtype[1] == DIR_CODE)
    	{
    		param2 = get_2_val(war, chariot, i + 2);
            r = war->arena[calc_addr(chariot->addr + i + 4)];
            if (war->verbose[2] == 1 && r > 0 && r <= 16)
            {
                printf("P %4d | lldi %hd %d r%hd\n", (chariot->index + 1), param1, param2, r);
                printf("       | -> load to %hd + %hd = %d (with pc and mod %d)\n", param1, param2, param1 + param2, (chariot->pc + ((param1 + param2) % IDX_MOD)));
            }
            if (r > 16 || r <= 0)
            {
            	print_verbose_16(war, chariot, 7);
            	return (FAILURE);
            }
            else
            	print_verbose_16(war, chariot, 7);
    	}
    	if (war->rtype[1] == REG_CODE)
    	{
    		param2 = war->arena[calc_addr(chariot->addr + i + 2)];
            r = war->arena[calc_addr(chariot->addr + i + 3)];
            if (war->verbose[2] == 1 && r > 0 && r <= 16)
            {
                printf("P %4d | lldi %hd %d r%d\n", (chariot->index + 1), param1, param2, r);
                printf("       | -> load to %hd + %d = %d (with pc and mod %d)\n", param1, param2, param1 + param2, (chariot->pc + ((param1 + param2) % IDX_MOD)));
            }
            if (r > 16 || r <= 0)
            {
            	print_verbose_16(war, chariot, 6);
            	return (FAILURE);
            }
            else
            	print_verbose_16(war, chariot, 6);
    	}
    }
    p3 = ((param1 + param2) % IDX_MOD);
    p3 = ((calc_addr(chariot->start_pos - i + p3)) % MEM_SIZE);
    if (p3 == 0)
    	chariot->carry = 1;
    else
    	chariot->carry = 0;
    if (r > 0 && r <= 16)
    	chariot->registres[r - 1] = p3;
//    printf("LLDI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
