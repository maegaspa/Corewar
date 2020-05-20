/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:31 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:38:17 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			live_fct(t_war *war, t_chariot *chariot)
{
	int nb_player;
	t_chariot *ch;

	ch = war->begin;
	//printf("LIVE_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	nb_player = get_4_val(war, chariot, 1);	
	if (war->verbose[2] == 1)
		printf("P %4d | live %d\n", (chariot->index + 1), nb_player);
	print_verbose_16(war, chariot, 5);
	while (ch)
	{
		if (nb_player == ch->player)
		{
			if (war->verbose[4] == 1)
				printf("Player %d (%s) is said to be alive\n", nb_player, war->player[nb_player].header.prog_name);
			ch->live++;
			war->lastlive = nb_player;
			return (0);
		}
		ch = ch->next;
	}
	return (0);
}
