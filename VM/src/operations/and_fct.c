/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:08 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:39:03 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			and_fct(t_war *war, t_chariot *chariot)
{
	printf("AND_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, (chariot->start_pos + chariot->pc));
	return (0);
}
