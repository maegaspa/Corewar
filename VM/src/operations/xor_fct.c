/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:46 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:37:06 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			xor_fct(t_war *war, t_chariot *chariot)
{
	int i;
	int param1;
	int param2;
	int r;

	get_bin_ocp(chariot, war);
	if (war->rtype[0] == T_REG)//REG
	{
		if (war->verbose[2] == 1)
			printf("P %4d | xor %d ", (chariot->index + 1), (unsigned char)war->arena[chariot->start_pos + chariot->pc + 2]);
		param1 = chariot->registres[(unsigned char)war->arena[chariot->start_pos + chariot->pc + 2]];
		i = 3;
	}
	if (war->rtype[0] == T_IND)//IND
	{
		param1 = get_2_val(war, chariot, 2);
		if (war->verbose[2] == 1)
			printf("P %4d | xor %d ", (chariot->index + 1), param1);
		param1 %= IDX_MOD;
		i = 4;
	}
	if (war->rtype[0] == T_DIR)//DIR
	{
		param1 = get_4_val(war, chariot, 2);
		if (war->verbose[2] == 1)
			printf("P %4d | xor %d ", (chariot->index + 1), param1);
		i = 6;
	}
	if (war->rtype[1] == T_REG)
	{
		if (war->verbose[2] == 1)
			printf("%d", (unsigned char)war->arena[chariot->start_pos + chariot->pc + i]);
		param2 = chariot->registres[(unsigned char)war->arena[chariot->start_pos + chariot->pc + i]];
		i++;
	}
	if (war->rtype[1] == T_IND)
	{
		param2 = get_2_val(war, chariot, i);
		if (war->verbose[2] == 1)
			printf("%d", param2);
		param2 %= IDX_MOD;
		i += 2;
	}
	if (war->rtype[1] == T_REG)
	{
		param2 = get_4_val(war, chariot, i);
		if (war->verbose[2] == 1)
			printf("%d", param2);
		i += 4;
	}
	r = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i];
	if (war->verbose[2] == 1)
		printf(" r%d\n", r);
	print_verbose_16(war, chariot, i + 1);
	chariot->registres[r - 1] = param1 ^ param2;

	//printf("XOR_FCT : index_chariot : %d\tto_die : %d\n", chariot->index, war->to_die);
	return (0);
}
