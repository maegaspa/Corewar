/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:00:44 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		is_conform_3(t_war *war)
{
	war->rtype[war->i_ocp] = IND_CODE;
	war->jump += 2;
	war->i_ocp++;
}

void		is_conform_2(t_chariot *chariot, t_war *war)
{
	war->rtype[war->i_ocp] = DIR_CODE;
	war->i_ocp++;
	if (g_op_tab[chariot->ope - 1].label_size)
		war->jump += T_DIR_TWO;
	else
		war->jump += T_DIR_FOUR;
}

void		is_conform_1(t_war *war)
{
	war->rtype[war->i_ocp] = REG_CODE;
	war->jump += 1;
	war->i_ocp++;
}

int			is_conform(unsigned char ocp, t_chariot *chariot, t_war *war)
{
	if (ocp == 0)
		return (FAILURE);
	if (ocp == 1 && get_val(war, chariot, war->jump) > 0 &&
				get_val(war, chariot, war->jump) <= 16 && (0x01 &
				g_op_tab[chariot->ope - 1].params_type[war->i_ocp]))
	{
		is_conform_1(war);
		return (SUCCESS);
	}
	if (ocp == 2 && (0x02 &
				g_op_tab[chariot->ope - 1].params_type[war->i_ocp]))
	{
		is_conform_2(chariot, war);
		return (SUCCESS);
	}
	if (ocp == 3 && (0x04 &
				g_op_tab[chariot->ope - 1].params_type[war->i_ocp]))
	{
		is_conform_3(war);
		return (SUCCESS);
	}
	return (FAILURE);
}

int			calc_addr(int addr)
{
	addr %= MEM_SIZE;
	while (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}
