/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:33:51 by hmichel           #+#    #+#             */
/*   Updated: 2020/03/09 19:42:21 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_print_chariot(t_chariot *chariot, int reg) //reg == 1 <=> print 16 REG
{
	int		i;

	i = -1;
	ft_printf("\n#------chariot [%d]-------#\n", chariot->index);
	ft_printf("pc = %d\nlive = %d\ncarry = %d\nwait = %d\nstart_pos = %d\nope = %d\n", 
	chariot->pc, chariot->live, chariot->carry, chariot->wait, chariot->start_pos, chariot->ope);
	if (reg)
	{
		ft_printf("registre:");
		while (++i < REG_NUMBER)
			ft_printf(" |%d|", i);
		ft_printf("\n");
	}
}

void		ft_print_war(t_war *war)
{
	ft_printf("\n#------war-------#\n");
	ft_printf("nb_player = %d\nto_die = %d\ncycles = %d\ndump = %d\n", war->nb_player, war->to_die, war->cycles, war->dump);
	if (war->begin)
		ft_printf("begin : %p <=> chariot %d\n", war->begin, (war->begin)->index);
	else
		ft_printf("begin sur NULL\n");
}
