/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:33:51 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:23:47 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

void		ft_print_chariot(t_chariot *chariot, int reg) //reg == 1 <=> print 16 REG
 {
 	int		i;

 	i = -1;
 	printf("\n#------chariot [%d]-------#\n", chariot->index);
 	printf("pc = %d\nlive = %d\ncarry = %d\nwait = %d\nstart_pos = %d\nope = %d\n",
 	chariot->pc, chariot->live, chariot->carry, chariot->wait, chariot->start_pos, chariot->ope);
 	if (reg)
 	{
 		printf("registre:");
 		while (++i < REG_NUMBER)
 			printf(" |%d|", i);
 		printf("\n");
 	}
 }

void		ft_print_war(t_war *war)
{
	printf("\n#------war-------#\n");
	printf("nb_player = %d\nto_die = %d\ncycles = %d\ndump = %d\n ", war->nb_player, war->cycle_to_die, war->cycles, war->dump);
	if ((war->begin))
		printf("begin : %p <=> chariot %d\n", (war->begin), (war->begin)->index);
	else
		printf("begin sur NULL\n");
}