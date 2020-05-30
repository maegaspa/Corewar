/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:25 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:38:32 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			ldi_fct(t_war *war, t_chariot *chariot)
{
	int i;
	int param1;
	int param2;
	int p3;
	int r;

	i = 2;
//	printf("LDI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	//get_bin_ocp(chariot, war);
//	int k = -1;
//    	while (++k < 3)
//    		printf("[ldi] war->rtype[%d] = %d\n", k, war->rtype[k]);
	if (war->rtype[0] == IND_CODE)
	{
		param1 = get_2_val(war, chariot, i);
        param2 = read_arena(war, param1);
       	if (war->rtype[1] == REG_CODE)
       	{
       		war->tmp = (unsigned char)war->arena[calc_addr(chariot->addr + i + 2)];
       		r = war->arena[calc_addr(chariot->addr + i + 3)];
       		if (war->verbose[2] == 1)
			{
				printf("P %4d | ldi %hd %d r%d\n", (chariot->index + 1), param1, war->tmp, r);
				printf("       | -> load to  %hd + %d = %d (with pc and mod %d)\n", param1, war->tmp, param1 + war->tmp, calc_addr(chariot->addr + ((param1 + war->tmp) % IDX_MOD)));
			}
			print_verbose_16(war, chariot, 6);
       	}
       	else if (war->rtype[1] == DIR_CODE)
       	{
       		war->tmp = get_2_val(war, chariot, i + 2);
       		r = war->arena[calc_addr(chariot->addr + i + 4)];
       		if (war->verbose[2] == 1)
       		{
				printf("P %4d | ldi %hd %hd r%d\n", (chariot->index + 1), param1, war->tmp, r);
				printf("       | -> load to  %d + %d = %d (with pc and mod %d)\n", param1, war->tmp, param1 + war->tmp, calc_addr(chariot->addr + ((param1 + war->tmp) % IDX_MOD)));
			}
			print_verbose_16(war, chariot, 7);
       	}
	}
	else if (war->rtype[0] == REG_CODE)
	{
		param1 = war->arena[calc_addr(chariot->addr + i)];
		if (war->rtype[1] == REG_CODE)
		{
			param2 = war->arena[calc_addr(chariot->addr + i + 1)];
			r = war->arena[calc_addr(chariot->addr + i + 2)];
			if (war->verbose[2] == 1)
			{
				printf("P %4d | ldi %d %d r%d\n", (chariot->index + 1), chariot->registres[param1 - 1], chariot->registres[param2 - 1], r);
				printf("       | -> load to  %d + %d = %d (with pc and mod %d)\n", chariot->registres[param1 - 1], chariot->registres[param2 - 1], chariot->registres[param1 - 1] + chariot->registres[param2 - 1], ((chariot->registres[param1 - 1] + chariot->registres[param2 - 1]) % IDX_MOD));
			}
			print_verbose_16(war, chariot, 5);
		}
		else if (war->rtype[1] == DIR_CODE)
		{
			param2 = get_2_val(war, chariot, i + 1);
			r = war->arena[calc_addr(chariot->addr + i + 3)];
			if (war->verbose[2] == 1)
			{
				printf("P %4d | ldi %d %hd r%d\n", (chariot->index + 1), param1, param2, r);
				printf("       | -> load to  %d + %hd = %d (with pc and mod %d)\n", param1, param2, param1 + param2, calc_addr(chariot->addr + ((param1 + param2) % IDX_MOD)));
			}
			print_verbose_16(war, chariot, 6);

		}
	}
	else if (war->rtype[0] == DIR_CODE)
	{
		param1 = get_2_val(war, chariot, i);
		if (war->rtype[1] == DIR_CODE)
		{
			param2 = get_2_val(war, chariot, i + 2);
			r = war->arena[calc_addr(chariot->addr + i + 4)];
			if (war->verbose[2] == 1)
			{
				printf("P %4d | ldi %hd %d r%hd\n", (chariot->index + 1), param1, param2, r);
				printf("       | -> load to  %hd + %hd = %hd (with pc and mod %d)\n", param1, param2, param1 + param2, calc_addr(chariot->addr + ((param1 + param2) % IDX_MOD)));
			}
			print_verbose_16(war, chariot, 7);
		}
		else if (war->rtype[1] == REG_CODE)
		{
			param2 = war->arena[calc_addr(chariot->addr + i + 2)];
			r = war->arena[calc_addr(chariot->addr + i + 3)];
			if (war->verbose[2] == 1)
			{
				printf("P %4d | ldi %hd %d r%d\n", (chariot->index + 1), param1, param2, r);
				printf("       | -> load to  %hd + %d = %d (with pc and mod %d)\n", param1, param2, param1 + param2, calc_addr(chariot->addr + ((param1 + param2) % IDX_MOD)));
			}
			print_verbose_16(war, chariot, 6);
		}
	}
	p3 = read_arena(war, (param1 + param2) % IDX_MOD + chariot->addr);
//	p3 = ((param1 + param2) % IDX_MOD);
//	p3 = ((chariot->start_pos - i + p3) % MEM_SIZE);
	chariot->registres[(unsigned char)r - 1] = p3;
	return (0);
}
