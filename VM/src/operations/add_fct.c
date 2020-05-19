/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:04 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:35:00 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			add_fct(t_war *war, t_chariot *chariot)
{
	unsigned char reg1;
	unsigned char reg2;
	unsigned char reg3;
	int result;

	if (war->verbose[2] == 1)
        printf("P %4d | add r%d r%d r%d\n", (chariot->index + 1), (unsigned char)war->arena[chariot->start_pos + chariot->pc + 2], (unsigned char)war->arena[chariot->start_pos + chariot->pc + 3], (unsigned char)war->arena[chariot->start_pos + chariot->pc + 4]);
	get_bin_ocp(chariot, war);
	print_verbose_16(war, chariot, 5);
	if (war->rtype[0] == T_REG && war->rtype[1] == T_REG && war->rtype[2] == T_REG)
	{
		reg1 = (unsigned char)war->arena[chariot->start_pos + chariot->pc + 2];
		reg2 = (unsigned char)war->arena[chariot->start_pos + chariot->pc + 4];
		reg3 = (unsigned char)war->arena[chariot->start_pos + chariot->pc + 6];
		result = chariot->registres[reg1 - 1] + chariot->registres[reg2 - 1];
		//printf("ADD :: reg1 r%x[%d] / reg2 r%x[%d] / reg3 r%x[%d] ----- result : [%d]\n", reg1, chariot->registres[reg1 - 1], reg2, chariot->registres[reg2 - 1], reg3, chariot->registres[reg3 - 1], result);
		if (result == 0)
			chariot->carry = 1;
		else
			chariot->carry = 0;
		chariot->registres[reg3 - 1] = result;
		//printf("r%x[%d]\n", reg3, chariot->registres[reg3 - 1]);
	}
	//printf("ADD_FCT : index_chariot : %d\tto_die : %d\n", chariot->index, war->to_die);
	return (0);
}
