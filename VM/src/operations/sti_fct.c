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
		res = res + (unsigned char)war->arena[chariot->start_pos + chariot->pc + i];
		i++;
	}
	return (res);
}

int			sti_fct(t_war *war, t_chariot *chariot)
{
	int 			i;
	int				param2;
	int				param3;
	int				cell;
	int				pos;

	i = 3;
	get_bin_ocp(chariot, war);
	pos = chariot->start_pos + chariot->pc;
	if (war->rtype[1] == DIR_CODE && war->rtype[2] == DIR_CODE)
	{
		param2 = get_2_val(war, chariot, i);
		param3 = get_2_val(war, chariot, i + 2);
		cell = ((param2 + param3) % IDX_MOD);
		if (war->verbose[2] == 1)
		{
			printf("P %4d | sti r%d %hd %hd\n", (chariot->index + 1), (unsigned char)war->arena[pos + 2], param2, param3);
			printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, (chariot->pc + cell));
		}
		print_verbose_16(war, chariot, 7);
	}
	else if (war->rtype[1] == IND_CODE && war->rtype[2] == REG_CODE)
	{
		param2 = get_2_val(war, chariot, i);
		param3 = war->arena[pos + i + 2];
		cell = ((param2 + param3) % IDX_MOD);
		if (war->verbose[2] == 1)
		{
			printf("P %4d | sti r%d %d %d\n", (chariot->index + 1), (unsigned char)war->arena[pos + 2], param2, param3);
			printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, (chariot->pc + cell));
		}
		print_verbose_16(war, chariot, 7);
	}
	else if (war->rtype[1] == REG_CODE && war->rtype[2] == REG_CODE)
	{
		param2 = war->arena[pos + i];
		param3 = war->arena[pos + i + 1];
		cell = ((param2 + param3) % IDX_MOD);
		if (war->verbose[2] == 1)
		{
			printf("P %4d | sti r%d %d %d\n", (chariot->index + 1), (unsigned char)war->arena[pos + 2], param2, param3);
			printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, (chariot->pc + cell));
		}
		print_verbose_16(war, chariot, 6);
	}
	write_on_arena(war, chariot->registres[(unsigned char)war->arena[pos + 2] - 1], pos + cell, REG_SIZE);
	//    printf("STI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
