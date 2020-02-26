/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:46:10 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/26 15:48:04 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_chariot		*ft_creat_chariot(int pc, int start_pos)
{
	t_chariot	*new;
	int			i;

	i = -1;
	if (!(new = (t_chariot*)malloc(sizeof(t_chariot))))
		return (NULL);
	new->pc = pc;
	new->live = 0;
	new->carry = 0;
	new->wait = 0;
	new->player = 0; //inutile ?
	new->start_pos = start_pos;
	while (++i < REG_NUMBER)
		new->registres[i] = 0;
	new->next = NULL;
	return (new);
}

int			ft_start_chariot(t_war *war, t_chariot **begin)
{
	int			i;
	t_chariot	*temp;

	i = war->nb_player;
	if (!war->nb_player)
		return (ERROR_NB_PLAYER);
	if (!(temp = ft_creat_chariot(0, war->player[i].pos_arena)))
		return (ERROR_MALLOC);
	while (--i > 0)
	{
		if (!(temp->next = ft_creat_chariot(0, war->player[i].pos_arena)))
			(ERROR_MALLOC);
		temp = temp->next;
	}
	*begin = temp;
	return (SUCCESS);
}
