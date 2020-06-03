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
	if (chariot->carry == 1)
	{
		war->back_pc = 1;
		if (war->verbose[2] == 1)
			printf("P %4d | zjmp %d OK\n", (chariot->index + 1), war->param[0]);
		chariot->pc = calc_addr(chariot->pc + (war->param[0] % IDX_MOD));
		if (chariot->pc < 0)
			chariot->pc += MEM_SIZE;
	}
	else
	{
		war->back_pc = 0;
		if (war->verbose[2] == 1)
		{
			printf("P %4d | zjmp %d FAILED\n", (chariot->index + 1),
				war->param[0]);
		}
	}
	return (SUCCESS);
}
