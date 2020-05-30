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

static	t_chariot *ft_fork_chariot(t_chariot *chariot, int param, t_war *war)
{
	t_chariot	*new;
//	int			i;
//
//	i = -1;
	if (!(new = (t_chariot*)malloc(sizeof(t_chariot))))
		return (NULL);
	//printf("nb_chariot = %d\n", war->nb_chariot);
	new->pc = calc_addr(chariot->pc + chariot->start_pos + (param % IDX_MOD));
//	printf("new_add = %d\n", new->pc);
	new->live = chariot->live; //a check, sujet dit de garder le meme last_live, on a fait differament
	new->carry = chariot->carry;
	new->wait = 0;
	new->index = war->nb_chariot - 1;
	new->player = chariot->player;
	new->start_pos = 0;
	new->last_live = chariot->last_live;
	new->prev_color = chariot->player;
	new->ope = -1; // <=> ope non conforme
	new->registres[0] = new->player * -1;
//	while (++i < REG_NUMBER)
//		new->registres[i] = chariot->registres[i];
	new->next = war->begin;
	return (new);
}

int			fork_fct(t_war *war, t_chariot *chariot)
{
	t_chariot *tmp_char;

	if (war->verbose[2] == 1)
        printf("P %4d | fork %d (%d)\n", (chariot->index + 1), (short)war->param[0], calc_addr(chariot->pc + chariot->start_pos + (war->param[0] % IDX_MOD)));
//    print_verbose_16(war, chariot, 3);
//	printf("war->param[0] = %d\n", war->param[0]);
	war->nb_chariot++;
	if (!(tmp_char = ft_fork_chariot(chariot, war->param[0], war)))
		return (ERROR_MALLOC);
	war->begin = tmp_char;
	if (ft_get_op(war, war->begin) == 1)
    	(war->begin)->wait = war->op_cycle[(war->begin)->ope - 1];
	return (0);
}
