/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 02:23:24 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 02:23:24 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
//ini next_check a 1536
//compter live au chariot meme quand l'ope live s'execute pas normalement
/*int			check_cycle(t_war *war, t_chariot *chariot)
{
	if (war->cycles < war->next_check)
	{
		war->cycles++;
		return (SUCCESS);
	}
	else
	{
		v_alive_chariot(chariot, war);
		if (war->nb_lives < NBR_LIVE && war->check_cycles_to_die < MAX_CHECKS)
		{
			war->check_cycles_to_die++;
			war->next_check += war->cycle_to_die;
		}
		else
		{
			war->check_cycles_to_die = 0;
			war->cycle_to_die -= CYCLE_DELTA;
			if (war->begin == NULL || (war->cycle_to_die <= 0))
			{
				if (war->verbose[3] == 1)
					printf("It is now cycle [%d]\n", war->cycles);//on observe last live pour le vainqueur
				printf("Contestant %d, \"%s\", has won !\n", war->lastlive, war->player[war->lastlive - 1].header.prog_name);
				war->cycles++;
				return (FAILURE);
			}
			war->next_check += war->cycle_to_die;
			war->nb_lives = 0;
			reset_lives_chariot(war);
		}
		war->cycles++;
	}
	return (SUCCESS);
}*/

int		end_game(t_war *war) //il faudra surement rejouer un tour
{
	if (war->begin == NULL || (war->cycle_to_die <= 0))
	{
		if (war->cycle_to_die <= 0 && war->verbose[3] == 1)
			printf("It is now cycle %d\n", war->cycles + 1);
		delete_chariot(war);
		if (war->verbose[5] == 1)
		{
			if (war->visu != 1)
				printf("Contestant %d, \"%s\", has won !\n", war->lastlive, war->player[war->lastlive - 1].header.prog_name);
			else
			{
				mvwprintw(war->visual.keys_win, 10, 4, "Contestant %d, \"%s\", has won !", war->lastlive, war->player[war->lastlive - 1].header.prog_name);
				wrefresh(war->visual.keys_win);
			}
		}
//		else
//			printf("Contestant %d, \"%s\", has won !\n", war->lastlive, war->player[war->lastlive - 1].header.prog_name);
		//war->cycles++;
		return (FAILURE);
	}
	return (SUCCESS);
}

int			check_cycle(t_war *war)
{
	//if (vm->cycles_to_die == vm->cycles_after_check
    //			|| vm->cycles_to_die <= 0)
	if (war->cycles - war->cycle_last_check >= war->cycle_to_die || war->cycle_to_die <= 0)
	{
		delete_chariot(war);
		war->cycle_last_check = war->cycles;
		if (!end_game(war))
        	return (FAILURE);
		//printf("war->nb_lives = %d ET [%d]\n", war->nb_lives, (war->begin)->live);
		if (war->nb_lives >= NBR_LIVE || war->check_cycles_to_die >= MAX_CHECKS)
		{
			war->cycle_to_die -= CYCLE_DELTA;
			if (war->verbose[3] == 1)
				printf("Cycle to die is now %d\n", war->cycle_to_die);
			if (!(end_game(war) == SUCCESS))
				return (FAILURE);
			war->check_cycles_to_die = 1;
		}
		else
			war->check_cycles_to_die++;
		war->nb_lives = 0;
	}
	mvwprintw(war->visual.infos_win, 4, 10, "on passe la %d", war->cycles);
	wrefresh(war->visual.infos_win);
	if (update_visu(war) != -1)
		war->cycles++;
	return (SUCCESS);
}
