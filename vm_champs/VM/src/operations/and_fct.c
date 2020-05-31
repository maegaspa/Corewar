/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:08 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:39:03 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			and_fct(t_war *war, t_chariot *chariot)
{
	verbose(war, chariot);
	chariot->registres[war->param[2] - 1] = war->param[0] & war->param[1];
	printf("%d\n", chariot->registres[war->param[2] - 1]);
	if ((war->param[0] & war->param[1]) == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
	return (0);
}
