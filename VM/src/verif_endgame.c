/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_endgame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:00:44 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		dead_chariot(t_war *war, t_chariot *chariot)
{
	return (war->cycle_to_die <= 0 ||
			war->cycles - chariot->last_live >= war->cycle_to_die);
}

void	delete_chariot(t_war *war, t_chariot *current)
{
	t_chariot *previous;
	t_chariot *delete;

	previous = NULL;
	while (current)
	{
		if (dead_chariot(war, (delete = current)) && war->nb_chariot--)
		{
			current = current->next;
			if (war->begin == delete)
				war->begin = current;
			if (previous)
				previous->next = current;
			if (war->verbose[1])
				printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		delete->index + 1, war->cycles - delete->last_live, war->cycle_to_die);
			ft_memdel((void **)&delete);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

void	reset_lives_chariot(t_war *war)
{
	t_chariot *temp;

	temp = war->begin;
	while (temp)
	{
		temp->live = 0;
		temp = temp->next;
	}
}
