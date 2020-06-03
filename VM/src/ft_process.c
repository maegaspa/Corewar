/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:46:10 by hmichel           #+#    #+#             */
/*   Updated: 2020/06/03 18:16:00 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_chariot	*ft_creat_chariot(int index, int pc, int start_pos, int player)
{
	t_chariot	*new;
	int			i;

	i = 0;
	if (!(new = (t_chariot *)ft_memalloc(sizeof(t_chariot))))
		return (NULL);
	new->pc = pc;
	new->live = 0;
	new->carry = 0;
	new->wait = 0;
	new->index = index;
	new->player = player;
	new->start_pos = start_pos;
	new->prev_color = player;
	new->ope = -1;
	new->registres[0] = player * -1;
	while (++i < REG_NUMBER)
		new->registres[i] = 0;
	new->next = NULL;
	return (new);
}

int			ft_start_chariot(t_war *war, t_chariot **begin, t_parse_file *file)
{
	int			i;
	t_chariot	*temp;

	if (!war->nb_player)
		return (ERROR_NB_PLAYER);
	i = 0;
	if (!(temp = ft_creat_chariot(0, 0,
	war->player[file->rank_player[i] - 1].pos_arena, file->rank_player[i])))
		return (ERROR_MALLOC);
	*begin = temp;
	while (++i < war->nb_player)
	{
		if (!(temp = ft_creat_chariot(temp->index + 1, 0, war->player
			[file->rank_player[i] - 1].pos_arena, file->rank_player[i])))
			return (ERROR_MALLOC);
		temp->next = *begin;
		*begin = temp;
	}
	return (SUCCESS);
}
