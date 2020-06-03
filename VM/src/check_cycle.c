/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:00:44 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		no_chariot(t_war *war)
{
	if (war->nb_chariot == 0)
	{
		if (war->visu != 1)
			printf("Contestant %d, \"%s\", has won !\n", war->lastlive,
					war->player[war->lastlive - 1].header.prog_name);
		else if (war->visu)
		{
			mvwprintw(war->visual.keys_win, 12, 2,
				"Contestant %d, \"%s\", has won !", war->lastlive,
				war->player[war->lastlive - 1].header.prog_name);
			wrefresh(war->visual.keys_win);
		}
		return (FAILURE);
	}
	return (SUCCESS);
}

static int		end_game(t_war *war)
{
	if (!no_chariot(war))
		return (FAILURE);
	if (war->cycle_to_die <= 0)
	{
		war->cycles++;
		if (war->verbose[3] == 1)
			printf("It is now cycle %d\n", war->cycles);
		delete_chariot(war, war->begin);
		if (war->visu != 1)
			printf("Contestant %d, \"%s\", has won !\n",
				war->lastlive, war->player[war->lastlive - 1].header.prog_name);
		else if (war->visu)
		{
			mvwprintw(war->visual.keys_win, 12, 2,
				"Contestant %d, \"%s\", has won !", war->lastlive,
				war->player[war->lastlive - 1].header.prog_name);
			wrefresh(war->visual.keys_win);
		}
		return (FAILURE);
	}
	return (SUCCESS);
}

int				check_cycle(t_war *war)
{
	delete_chariot(war, war->begin);
	war->cycles_btw_check = 0;
	if (!end_game(war))
		return (FAILURE);
	if (war->nb_lives >= NBR_LIVE || war->check_cycles_to_die >= MAX_CHECKS)
	{
		war->cycle_to_die -= CYCLE_DELTA;
		if (war->verbose[3] == 1)
			printf("Cycle to die is now %d\n", war->cycle_to_die);
		war->check_cycles_to_die = 1;
	}
	else
		war->check_cycles_to_die++;
	war->nb_lives = 0;
	return (SUCCESS);
}
