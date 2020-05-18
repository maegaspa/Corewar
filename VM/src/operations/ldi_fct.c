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
	printf("LDI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	get_bin_ocp(chariot, war);
	if (war->rtype[0] == T_IND)
	{
		param1 = get_2_val(war, chariot, i);
        param1 = (param1 % IDX_MOD);
        param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1) % MEM_SIZE] << 24;
       	param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 1) % MEM_SIZE] << 16;
       	param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 2) % MEM_SIZE] << 8;
       	param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 3) % MEM_SIZE];
       	if (war->rtype[1] == T_REG)
       		r = war->arena[chariot->start_pos + chariot->pc + i + 3];
       	if (war->rtype[1] == T_DIR)
       		r = war->arena[chariot->start_pos + chariot->pc + i + 4];
	}
	if (war->rtype[0] == T_REG)
	{
		param1 = war->arena[chariot->start_pos + chariot->pc + i];
		if (war->rtype[1] == T_REG)
		{
			param2 = war->arena[chariot->start_pos + chariot->pc + i + 1];
			r = war->arena[chariot->start_pos + chariot->pc + i + 2];
		}
		if (war->rtype[1] == T_DIR)
		{
			param2 = get_2_val(war, chariot, i + 1);
			r = war->arena[chariot->start_pos + chariot->pc + i + 3];
		}
	}
	if (war->rtype[0] == T_DIR)
	{
		param1 = get_2_val(war, chariot, i);
		if (war->rtype[1] == T_DIR)
		{
			param2 = get_2_val(war, chariot, i + 2);
			r = war->arena[chariot->start_pos + chariot->pc + i + 4];
		}
		if (war->rtype[1] == T_REG)
		{
			param2 = war->arena[chariot->start_pos + chariot->pc + i + 2];
			r = war->arena[chariot->start_pos + chariot->pc + i + 3];
		}
	}
	p3 = ((param1 + param2) % IDX_MOD);
	p3 = ((chariot->start_pos - i + p3) % MEM_SIZE);
	chariot->registres[r - 1] = p3;
	return (0);
}
