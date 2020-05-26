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

	if (war->verbose[2] == 1)
        printf("P %4d | aff r%d\n", (chariot->index + 1), (unsigned char)war->arena[chariot->start_pos + chariot->pc + 2]);
	print_verbose_16(war, chariot, 3);
	value = war->arena[chariot->start_pos + chariot->pc + 2];
	chariot->registres[value - 1] = 112;
	value = chariot->registres[value - 1];
	value %= 256;
	//printf("war->aff = %d\n", war->aff);
	//printf("%c\n", value);
	if (war->aff == 1)
		printf("%c\n", value);
	return (0);
}
