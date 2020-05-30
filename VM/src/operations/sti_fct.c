/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 16:06:28 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

short		get_2_val(t_war *war, t_chariot *chariot, int i)
{
	unsigned short	res;
	int 			tmp;

	res = 0;
	tmp = i;
	while (i < tmp + 2)
	{
		res = res << 8;
		res = res + (unsigned char)war->arena[calc_addr(chariot->pc + chariot->start_pos + i)];
		i++;
	}
	return (res);
}

int			sti_fct(t_war *war, t_chariot *chariot)
{
	verbose(war, chariot);
	//printf("pc %d, p1 %d, p2 %d, p1+p2 %d\n", chariot->pc, ft_load(war, 4, calc_addr(chariot->pc + war->param[1] % IDX_MOD)), (short)war->param[2], calc_addr(chariot->pc + chariot->start_pos + ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + war->param[1] % IDX_MOD)) + (short)war->param[2]) % IDX_MOD);
	//printf("GAY %d\n", calc_addr(chariot->pc + chariot->start_pos + ((chariot->registres[war->param[1]- 1] + chariot->registres[war->param[2] - 1]) % IDX_MOD)));
	if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE && war->rtype[2] == REG_CODE)
		write_on_arena(war, chariot->registres[war->param[0] - 1], calc_addr(chariot->pc + chariot->start_pos + ((chariot->registres[war->param[1]- 1] + chariot->registres[war->param[2] - 1]) % IDX_MOD)), 4);
	else if (war->rtype[1] == IND_CODE && war->rtype[2] != REG_CODE)
    	write_on_arena(war, chariot->registres[war->param[0] - 1],  calc_addr(chariot->pc + chariot->start_pos + ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + war->param[1] % IDX_MOD)) + (short)war->param[2]) % IDX_MOD, 4);
	else if (war->rtype[1] == IND_CODE && war->rtype[2] == REG_CODE)
		write_on_arena(war, chariot->registres[war->param[0] - 1],  calc_addr(chariot->pc + chariot->start_pos + ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + war->param[1] % IDX_MOD)) + chariot->registres[war->param[2] - 1]) % IDX_MOD, 4);
	else if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE && war->rtype[2] != REG_CODE)
    	write_on_arena(war, chariot->registres[war->param[0] - 1], calc_addr(chariot->pc + chariot->start_pos + ((chariot->registres[war->param[1]- 1] + war->param[2]) % IDX_MOD)), 4);
    else if (war->rtype[0] == REG_CODE && war->rtype[1] != REG_CODE && war->rtype[2] == REG_CODE)
    	write_on_arena(war, chariot->registres[war->param[0] - 1], calc_addr(chariot->pc + chariot->start_pos + ((war->param[1] + chariot->registres[war->param[2] - 1]) % IDX_MOD)), 4);
	else
		write_on_arena(war, chariot->registres[war->param[0] - 1], calc_addr(chariot->pc + chariot->start_pos + ((war->param[1] + war->param[2]) % IDX_MOD)), 4);
	return (0);
}
