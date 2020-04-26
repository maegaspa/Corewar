/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:21 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:38:53 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			fork_fct(t_war *war, t_chariot *chariot)
{
	t_chariot *tmp_char;
	int 	param;

	param = get_2_val(war, chariot, 1);
	printf("[%x]\n", param);
	tmp_char = chariot;
	printf("FORK_FCT : index_chariot : %d\tto_die : %d\n", chariot->index, war->to_die);
	if (!(tmp_char->next = ft_creat_chariot(tmp_char->index + 1, (chariot->pc + (param % IDX_MOD)), war->player[chariot->player].pos_arena, chariot->player)))
		(ERROR_MALLOC);
	tmp_char = tmp_char->next;
	chariot = tmp_char;
	return (0);
}
