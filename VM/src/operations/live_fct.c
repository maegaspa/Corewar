/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:31 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 16:44:34 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			live_fct(t_war *war, t_chariot *chariot)
{
	int nb_player;
	//t_chariot *ch;
	int i;
	int pos;

	//ch = war->begin;
	chariot->live++;
	//printf("LIVE_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	nb_player = get_4_val(war, chariot, 1);
	pos = chariot->pc + chariot->start_pos;
	//printf("pc [%d], nb_player = [%d]\n", pos, nb_player);
	if (war->verbose[2] == 1)
		ft_printf("P %4d | live %d\n", (chariot->index + 1), nb_player);
	print_verbose_16(war, chariot, 5);
	i = -1;
	//dprintf(1, "ICI 1\n");
	while (++i < war->nb_player)
	{
		if (nb_player == ((war->player[i].num + 1) * -1))
		{
			if (war->verbose[4] == 1)
				ft_printf("Player %d (%s) is said to be alive\n", (nb_player * -1), war->player[(nb_player * -1) - 1].header.prog_name);
			war->lastlive = nb_player * -1;
			return (0);
		}
	}
//	i = -1;
//	while (++i < war->nb_player)
//	{
//		if (war->player[i].num == nb_player)
//		{
//			if (war->verbose[4] == 1)
//            	ft_printf("Player %d (%s) is said to be alive\n", nb_player, war->player[nb_player].header.prog_name);
//			ch->live++;
//			war->lastlive = i;
//			break ;
//		}
//	}
	return (0);
}
