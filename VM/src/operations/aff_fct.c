/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:06 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:35:29 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			aff_fct(t_war *war, t_chariot *chariot)
{
	printf("AFF_FCT : index_chariot : %d\tto_die : %d et pc = %d\n", chariot->index, war->to_die, (chariot->start_pos + chariot->pc));
	return (0);
}
