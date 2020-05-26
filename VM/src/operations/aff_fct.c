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
	unsigned char value;

//	if (war->verbose[2] == 1)
//        printf("P %4d | aff r%d\n", (chariot->index + 1), (unsigned char)war->arena[chariot->start_pos + chariot->pc + 2]);
	value = war->arena[chariot->start_pos + chariot->pc + 2];
	value = chariot->registres[value - 1];
	value %= 256;
	if (war->aff == 1)
		printf("Aff: %c\n", value);
	print_verbose_16(war, chariot, 3);
	return (0);
}
