/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:21 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/26 01:33:43 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void			add_cursor(t_chariot **begin, t_chariot *new)
{
	if (new)
		new->next = *begin;
	*begin = new;
}

static t_chariot	*ft_fork_chariot(t_chariot *chariot, int param, t_war *war)
{
	t_chariot	*new;
	int			i;

	i = -1;
	if (!(new = (t_chariot *)ft_memalloc(sizeof(t_chariot))))
		return (NULL);
	new->pc = calc_addr(C_POS + (param % IDX_MOD));
	new->live = chariot->live;
	new->carry = chariot->carry;
	new->wait = 0;
	new->index = war->id_chariot;
	war->id_chariot++;
	new->player = chariot->player;
	new->start_pos = 0;
	new->last_live = chariot->last_live;
	new->prev_color = chariot->player;
	new->ope = -1;
	while (++i < REG_NUMBER)
		new->registres[i] = chariot->registres[i];
	new->next = NULL;
	return (new);
}

int					fork_fct(t_war *war, t_chariot *chariot)
{
	t_chariot *tmp_char;

	if (war->verbose[2] == 1)
		printf("P %4d | fork %d (%d)\n", (chariot->index + 1),
				(short)war->param[0], C_POS + (war->param[0] % IDX_MOD));
	war->nb_chariot++;
	if (!(tmp_char = ft_fork_chariot(chariot, war->param[0], war)))
		return (ERROR_MALLOC);
	add_cursor(&(war->begin), tmp_char);
	return (0);
}
