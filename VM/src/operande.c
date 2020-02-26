/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/26 19:12:50 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_stand_op(t_war *war, t_chariot *chariot)
{
	int		pos;

	pos = chariot->start_pos + chariot->pc;
	if (war->arena[pos] > 16 || war->arena[pos] == 0)
		chariot->pc++;
	else
		chariot->ope = war->arena[pos];
}

int		ft_get_op(t_war *war, t_chariot *chariot)
{
	ft_stand_op(war, chariot);
	return (1);
}
