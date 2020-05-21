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

//nouvelles variables: actual_cycles dans war,
void	free_chariot(t_chariot *chariot)
{
	chariot = chariot;
	//on verra pour leaks
}

void	delete_chariot(t_chariot *current, t_war *war)
{
	t_chariot *previous;
	t_chariot *delete;

	previous = war->begin;
	delete = current;
	if (current != NULL && current->index == 0)
	{
		war->begin = (war->begin)->next;
		current = current->next;
		free_chariot(delete);
	}
	else
	{
		while (previous != NULL && previous->next != current)
			previous = previous->next;
		current = current->next;
		previous->next = current;
		free_chariot(delete);
	}
}

int		v_alive_chariot(t_chariot *chariot, t_war *war)
{
	int cpt_lives;

	cpt_lives = 0;
	while (chariot)
	{
		if (chariot->live)
		{
			cpt_lives += chariot->live;
			chariot = chariot->next;
		}
		else
			delete_chariot(chariot, war);
	}
	chariot = war->begin;
	return (cpt_lives);
}

int		verif_endgame(t_war *war, t_chariot *chariot)
{
	if (war->actual_cycles == -1) //debut de partie 
		return (SUCCESS);
	if (v_alive_chariot(chariot, war) >= NBR_LIVE || war->check_cycles_to_die == MAX_CHECKS)
	{
		war->cycle_to_die -= CYCLE_DELTA;
		if (war->cycle_to_die < 0)
			war->cycle_to_die = 0;
		war->check_cycles_to_die = 0;
	}
	else
		war->check_cycles_to_die++;
	if (war->begin == NULL)
	{
		printf("On a un vaiqueur\n");//on observe last live pour le vainqueur
		return (FAILURE);
	}
	war->actual_cycles = 0;
	return (SUCCESS);
}