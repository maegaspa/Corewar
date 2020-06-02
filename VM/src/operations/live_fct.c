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
	int		id_player;

	id_player = war->param[0];
	chariot->live += 1;
	war->nb_lives += 1;
	if (war->verbose[2] == 1)
		printf("P %4d | live %d\n", (chariot->index + 1), id_player);
	if (id_player < 0 && id_player >= -(war->nb_player))
	{
		id_player = -id_player;
		war->lastlive = id_player;
		if (war->verbose[4] == 1)
			printf("Player %d (%s) is said to be alive\n",
			id_player, war->player[id_player - 1].header.prog_name);
	}
	return (0);
}
