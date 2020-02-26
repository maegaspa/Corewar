/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/26 14:58:41 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

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
			chariot->ope = 16;
		else if (war->arena[chariot->start_pos + chariot->pc + 1] <= '9')
			chariot->ope = war->arena[chariot->start_pos + chariot->pc] - '0';
		else if (war->arena[chariot->start_pos + chariot->pc + 1] >= 'a')
			chariot->ope = war->arena[chariot->start_pos + chariot->pc] - 'a' + 10;
	}
}

int		ft_get_op(t_war *war, t_chariot *chariot)
{
	ft_stand_op(war, chariot);
	return (1);
}
