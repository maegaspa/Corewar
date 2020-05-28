/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:31 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:10 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			live_fct(t_war *war, t_chariot *chariot)
{
	int nb_player;
	//t_chariot *ch;
	int i;

	//ch = war->begin;
	war->lastlive = 0;
	war->nb_lives++;
	//printf("LIVE_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	nb_player = get_4_val(war, chariot, 1);
//	if(war->cycles > 27000)
//	 	printf("war->verbose[2] = %d\n", war->verbose[2]);
	//printf("pc [%d], nb_player = [%d]\n", pos, nb_player);
	if (war->verbose[2] == 1)
		printf("P %4d | live %d\n", (chariot->index + 1), nb_player);
	i = -1;
	while (++i < war->nb_player)
	{
		if (nb_player == ((war->player[i].num + 1) * -1))
		{
			if (war->verbose[4] == 1)
				printf("Player %d (%s) is said to be alive\n", (nb_player * -1), war->player[(nb_player * -1) - 1].header.prog_name);
			war->lastlive = nb_player * -1;
//			if (nb_player < 0)
			//war->is_live = 1;
			print_verbose_16(war, chariot, 5);
			return (0);
		}
	}
	print_verbose_16(war, chariot, 5);
	return (0);
}
