/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:28 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/26 01:35:11 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static	t_chariot *ft_fork_chariot(t_chariot *chariot, int param, t_war *war)
{
	t_chariot	*new;
	int			i;

	i = -1;
	if (!(new = (t_chariot*)malloc(sizeof(t_chariot))))
		return (NULL);
	new->pc = chariot->pc + param;
	new->live = chariot->live; //a check, sujet dit de garder le meme last_live, on a fait differament
	new->carry = chariot->carry;
	new->wait = 0;
	new->index = war->nb_chariot;
	new->player = chariot->player;
	new->start_pos = chariot->start_pos;
	new->prev_color = chariot->player;
	new->ope = -1; // <=> ope non conforme
	while (++i < REG_NUMBER)
		new->registres[i] = chariot->registres[i];
	new->next = war->begin;
	return (new);
}

int			lfork_fct(t_war *war, t_chariot *chariot)
{
	t_chariot *tmp_char;
	int 	para_dir;

	para_dir = get_2_val(war, chariot, 1);
	if (war->verbose[2] == 1)
        printf("P %4d | lfork %d (%d)\n", (chariot->index + 1), para_dir, (chariot->pc + para_dir));
    print_verbose_16(war, chariot, 3);
	war->nb_chariot++;
	if (!(tmp_char = ft_fork_chariot(chariot, para_dir, war)))
		return (ERROR_MALLOC);
	war->begin = tmp_char;
	// tmp_char = chariot;
	//printf("FORK_FCT : index_chariot : %d\tto_die : %d\n", chariot->index, war->to_die);
	// if (!(tmp_char->next = ft_creat_chariot(tmp_char->index + 1, (chariot->pc + (param % IDX_MOD)), war->player[chariot->player].pos_arena, chariot->player)))
		// return (ERROR_MALLOC);
	// tmp_char = tmp_char->next;
	// chariot = tmp_char;
	return (0);
}
