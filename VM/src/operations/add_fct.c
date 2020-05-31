/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:04 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:35:00 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			add_fct(t_war *war, t_chariot *chariot)
{
	verbose(war, chariot);
	if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE && war->rtype[2] == REG_CODE)
	{
		if ((chariot->registres[war->param[0] - 1] + chariot->registres[war->param[1] - 1]) == 0)
			chariot->carry = 1;
		else
			chariot->carry = 0;
		chariot->registres[war->param[2] - 1] = chariot->registres[war->param[0] - 1] + chariot->registres[war->param[1] - 1];
	}
	printf("DANS ADD chariot->carry = %d\n", chariot->carry);
	return (0);
}
