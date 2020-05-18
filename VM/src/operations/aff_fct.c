/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:06 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:35:29 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			aff_fct(t_war *war, t_chariot *chariot)
{
	unsigned char reg;
	int value;

//	if (war->aff == 1)
//	{
	get_bin_ocp(chariot, war);
	reg = (unsigned char)war->arena[chariot->start_pos + chariot->pc +2];
	if (war->rtype[0] == T_REG && (reg > 0 && reg < 17))
	{
		value = chariot->registres[reg - 1];
		if ((char)value == 0)
		{
			if (chariot->carry == 0)
				chariot->carry = 1;
			else
				chariot->carry = 0;
		}
		else
			printf("%c\n", (char)(value));
	}
	printf("AFF_FCT : index_chariot : %d\tto_die : %d\n", chariot->index, war->to_die);
//	}
	return (0);
}
