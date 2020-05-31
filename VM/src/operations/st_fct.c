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
	verbose(war, chariot);
	if (war->rtype[1] == REG_CODE)
	{
		print_verbose_16(war, chariot, war->jump);
		chariot->registres[war->param[1] - 1] = chariot->registres[war->param[0] - 1];//war->param[1];
	}
	else
	{
		write_on_arena(war, chariot->registres[war->param[0] - 1], calc_addr(chariot->pc + chariot->start_pos + (war->param[1] % IDX_MOD)), 4);
		//printf("chariot->registres[war->param[0]] = %d\n", chariot->registres[war->param[0] - 1]);
		print_verbose_16(war, chariot, war->jump);
	}
	return (0);
}
/*
int			st_fct(t_war *war, t_chariot *chariot)
{
	int i;
	int param;
	int r;

	i = 3;
	get_bin_ocp(chariot, war);
	if (war->rtype[1] == IND_CODE)
	{
		r = war->arena[calc_addr(chariot->addr + 2)];
		param = get_2_val(war, chariot, i);
		if (war->verbose[2] == 1 && r > 0 && r <= 16)
        	printf("P %4d | st r%d %hd\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], param);
        if (r > 16 || r <= 0)
        {
        	print_verbose_16(war, chariot, 5);
        	return (FAILURE);
        }
        else
        {
      		write_on_arena(war, chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 2)] - 1], (chariot->addr) + (param % IDX_MOD), 4);
        	print_verbose_16(war, chariot, 5);
		}
//		write_on_arena(war, chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 2)] - 1], calc_addr((chariot->addr) + (param % IDX_MOD)), 4); //essayer en remettant start + pc?
	}
	else
	{
	 	r = war->arena[calc_addr(chariot->addr + 2)];
		if (war->verbose[2] == 1 && r > 0 && r <= 16)
        	printf("P %4d | st r%d %d\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], (unsigned char)war->arena[calc_addr(chariot->addr + 3)]);
        if (r > 16 || r <= 0)
        {
        	print_verbose_16(war, chariot, 4);
        	return (FAILURE);
		}
		else
		{
			print_verbose_16(war, chariot, 4);
			chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 3)] - 1] = chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 2)] - 1];
		}
	}
	return (0);
}*/
