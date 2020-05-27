/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:40 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/27 22:01:14 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			st_fct(t_war *war, t_chariot *chariot)
{
	int i;
	int param;

	i = 3;
//	if (war->cycles > 23300)
//    	printf("dans st chariot->start_pos = %d\n", chariot->start_pos);
	get_bin_ocp(chariot, war);
//	if (chariot->registres[0] == 0)
//		chariot->carry = 1;
	if (war->rtype[1] == IND_CODE)
	{
		param = get_2_val(war, chariot, i);
		if (war->verbose[2] == 1)
        	printf("P %4d | st r%d %hd\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], param);
        print_verbose_16(war, chariot, 5);
		write_on_arena(war, chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 2)] - 1], (calc_addr(chariot->addr) + (param % IDX_MOD)), 4);
	}
	else
	{
		if (war->verbose[2] == 1)
        	printf("P %4d | st r%d %d\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], (unsigned char)war->arena[calc_addr(chariot->addr + 3)]);
        print_verbose_16(war, chariot, 4);
		chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 3)] - 1] = chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 2)] - 1];
	}
	return (0);
}
