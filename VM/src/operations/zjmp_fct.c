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
	int k = -1;
	//printf("ZJMP_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	if (chariot->carry == 1)
	{
		param = get_2_val(war, chariot, i);
		if (war->verbose[2] == 1)
        	printf("P %4d | zjmp %d\n", (chariot->index + 1), param);
		next_pos = (chariot->start_pos + chariot->pc - i + param) % MEM_SIZE; // obtenir pos actuelle, rajout ?
		if (chariot->start_pos + chariot->pc < 0)
			next_pos += MEM_SIZE;
		printf("param = %d et next_pos = %d\n", param, next_pos);
	}
	return (SUCCESS);
}
