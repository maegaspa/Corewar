/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/25 23:02:52 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_get_op(t_war *war, t_chariot *chariot)
{
	return (ft_stand_op(war, chariot));
}

void		ft_stand_op(t_war *war, t_chariot *chariot)
{
	int		pos;

	pos = chariot->start_pos + chariot->pc;
	if (war->arena[pos] > '1' || (war->arena[pos] == '1' && war->arena[pos + 1] != '0')
		|| (war->arena[pos] == '0' && war->arena[pos + 1] == '0'))
		chariot->pc++;
	else
	{
		if (war->arena[chariot->start_pos + chariot->pc] == '1')
			war->ope = 16;
		else if (war->arena[chariot->start_pos + chariot->pc + 1] <= '9')
			war->ope = war->arena[chariot->start_pos + chariot->pc] - '0';
		else if (war->arena[chariot->start_pos + chariot->pc + 1] >= 'a')
			war->ope = war->arena[chariot->start_pos + chariot->pc] - 'a' + 10;
	}
}