/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_endgame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:31:33 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/20 17:31:33 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*void	free_chariot(t_chariot *chariot)
{
	//int		i_moove;
	t_chariot *temp;

	temp = chariot;
	//i_moove = chariot->index;
//	while (temp->next != NULL)
//	{
//		(temp->next)->index -= 1;
//		temp = temp->next;
//	}
	//on verra pour leaks
}*/

void	delete_chariot(t_chariot *current, t_war *war)
{
	t_chariot *previous;

	previous = war->begin;
	if (current != NULL && current->index == (war->begin)->index)
	{
		if (war->begin != NULL)
			war->begin = (war->begin)->next;
		current = current->next;
		//free_chariot(delete);
	}
	else
	{
		while (previous != NULL && previous->next != current)
			previous = previous->next;
		
		current = current->next;
		previous->next = current;
		//free_chariot(delete);
	}
}

void	reset_lives_chariot(t_war *war)
{
	t_chariot *temp;

	//war->nb_lives = 0;
	temp = war->begin;
	while (temp)
	{
		temp->live = 0;
		temp = temp->next;
	}
}
/*
int		v_alive_chariot(t_chariot *chariot, t_war *war)
{
	int cpt_lives;

	cpt_lives = 0;
	while (chariot)
	{
		//printf("chariot++\n");
		if (chariot->live)
			cpt_lives += chariot->live;
		else
			delete_chariot(chariot, war);
		chariot = chariot->next;
	}
	chariot = war->begin;
	//printf("%d lives sur les chariots\n", cpt_lives);
	if (cpt_lives >= NBR_LIVE)
    	reset_lives_chariot(war);
	return (cpt_lives);
}*/

int		v_alive_chariot(t_chariot *chariot, t_war *war)
{
	while (chariot)
	{
		//printf("chariot++\n");
		if (chariot->live == 0)
			delete_chariot(chariot, war);
		chariot = chariot->next;
	}
	chariot = war->begin;
	//printf("%d lives sur les chariots\n", cpt_lives);
	return (SUCCESS);
}
/*
int		verif_endgame(t_war *war, t_chariot *chariot)
{
	//printf("DEBUT verif_endgame\n");
	if (war->actual_cycles == 0) //debut de partie 
		return (SUCCESS);
	if (v_alive_chariot(chariot, war) >= NBR_LIVE || war->check_cycles_to_die == MAX_CHECKS)
	{
		war->to_die -= CYCLE_DELTA;
		printf("To_die - cycle_delta = %d\n", war->to_die);
//		reset_lives_chariot(war);
		if (war->to_die < 0)
			war->to_die = 0;
		war->check_cycles_to_die = 0;
	}
	else
	{
		war->check_cycles_to_die++;
		reset_lives_chariot(war);
		printf("war->check_cycles_to_die++\n");
	}
	//if (war->to_die == 0)
	if (war->begin == NULL || war->to_die == 0)
	{
		if (war->verbose[3] == 1)
			printf("It is now cycle [%d]\n", war->cycles);//on observe last live pour le vainqueur
		printf("Contestant %d, \"%s\", has won !\n", war->lastlive, war->player[war->lastlive - 1].header.prog_name);
		return (FAILURE);
	}
	war->actual_cycles = 0;
	//reset_lives_chariot(war);
	return (SUCCESS);
}*/
