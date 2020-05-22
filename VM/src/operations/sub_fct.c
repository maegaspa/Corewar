/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:44 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:37:13 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			sub_fct(t_war *war, t_chariot *chariot)
{
	//printf("SUB_FCT : index_chariot : %d\tto_die : %d\n", chariot->index, war->to_die);
	unsigned char 	reg1;
	unsigned char 	reg2;
	unsigned char 	reg3;
	int		result;

	get_bin_ocp(chariot, war);
	if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE && war->rtype[2] == REG_CODE)
	{
		reg1 = (unsigned char)war->arena[chariot->start_pos + chariot->pc + 2];
		reg2 = (unsigned char)war->arena[chariot->start_pos + chariot->pc + 4];
		reg3 = (unsigned char)war->arena[chariot->start_pos + chariot->pc + 6];
		if (war->verbose[2] == 1)
        	ft_printf("P %4d | sub r%d r%d r%d\n", (chariot->index + 1), reg1, reg2, reg3);
        print_verbose_16(war, chariot, 5);
		result = chariot->registres[reg1 - 1] - chariot->registres[reg2 - 1];
		if (result == 0)
			chariot->carry = 1;
		else
			chariot->carry = 0;
		chariot->registres[reg3 - 1] = result;
	}
	return (0);
}
