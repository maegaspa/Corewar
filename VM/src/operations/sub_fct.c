/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:44 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:37:13 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			sub_fct(t_war *war, t_chariot *chariot)
{
	int r1;
	int r2;

	verbose(war, chariot);
	r1 = chariot->registres[war->param[0] - 1];
	r2 = chariot->registres[war->param[1] - 1];
	if (war->rtype[0] == REG_CODE && war->rtype[1] ==
		REG_CODE && war->rtype[2] == REG_CODE)
	{
		if (r1 - r2 == 0)
			chariot->carry = 1;
		else
			chariot->carry = 0;
		chariot->registres[war->param[2] - 1] = r1 - r2;
	}
	return (0);
}
