/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:49 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:39:41 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"



int			zjmp_fct(t_war *war, t_chariot *chariot)
{
	int next_pos;
	int param;
	int i;

	param = 0;
	i = 1;
	next_pos = 0;
	printf("ZJMP_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, (chariot->start_pos + chariot->pc));
//	if (chariot->carry == 1)
//	{
//		param = get_2_val(war, chariot, i);
//		param = (param % IDX_MOD);
//		printf("param = %d \n", param);
//		chariot->pc = ((/*chariot->start_pos + */chariot->pc - i + param) % MEM_SIZE);
//		if (chariot->start_pos + chariot->pc < 0)
//			chariot->pc += MEM_SIZE;
//		//printf("param = %d et next_pos = %d\n", param, next_pos);
//		printf("pour le zjmp chariot->pc = %d\n", chariot->pc);
//	}
	return (SUCCESS);
}
