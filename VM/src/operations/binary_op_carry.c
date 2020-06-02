/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_op_carry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:06 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:35:29 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	verif_carry_and(t_chariot *chariot, int p1, int p2)
{
	if ((p1 & p2) == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
}

void	verif_carry_or(t_chariot *chariot, int p1, int p2)
{
	if ((p1 | p2) == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
}

void	verif_carry_xor(t_chariot *chariot, int p1, int p2)
{
	if ((p1 ^ p2) == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
}
