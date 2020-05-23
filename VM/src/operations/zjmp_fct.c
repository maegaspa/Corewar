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
	int param;
	int i;

	param = 0;
	i = 1;
	if (chariot->carry == 1)
	{
		war->back_pc = 1;
		param = ((short)get_2_val(war, chariot, i));
		param = param % IDX_MOD;
        if (war->verbose[2] == 1 && chariot->carry == 1)
        	ft_printf("P %4d | zjmp %d OK\n", (chariot->index + 1), param);
        else if (war->verbose[2] == 1)
        {
        	ft_printf("P %4d | zjmp %d FAILED\n", (chariot->index + 1), param);
		}
		chariot->pc = ((chariot->pc + param) % MEM_SIZE);
		if (chariot->pc < 0)
			chariot->pc += MEM_SIZE;
		printf("ZJMP chariot pc = %d\n", chariot->pc);
	}
	else
		war->back_pc = 0;
 	return (SUCCESS);
}
