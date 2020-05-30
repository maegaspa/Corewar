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
		printf("Contestant %d, \"%s\", has won !\n", war->lastlive, war->player[war->lastlive - 1].header.prog_name);
//		else
//			printf("Contestant %d, \"%s\", has won !\n", war->lastlive, war->player[war->lastlive - 1].header.prog_name);
		//war->cycles++;
		return (FAILURE);
	}
	return (SUCCESS);
}

int			check_cycle(t_war *war, t_chariot *chariot)
{
	if (war->cycles - war->cycle_last_check >= war->cycle_to_die)
	{
		war->cycle_last_check = war->cycles;
		v_alive_chariot(chariot, war);
		reset_lives_chariot(war);
		if (!(end_game(war) == SUCCESS))
        	return (FAILURE);
		//printf("war->nb_lives = %d ET [%d]\n", war->nb_lives, (war->begin)->live);
		if (war->nb_lives >= NBR_LIVE || war->check_cycles_to_die >= MAX_CHECKS)
		{
			war->cycle_to_die -= CYCLE_DELTA;
			printf("CTD = %d\n", war->cycle_to_die);
			if (!(end_game(war) == SUCCESS))
				return (FAILURE);
			war->check_cycles_to_die = 1;
		}
		else
			war->check_cycles_to_die++;
		war->nb_lives = 0;
	}
	war->cycles++;
	return (SUCCESS);
}