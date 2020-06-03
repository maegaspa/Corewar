/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:00:44 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		calc_jump(unsigned char ocp, t_chariot *chariot)
{
	if (ocp == 0)
		return (0);
	if (ocp == 1)
		return (1);
	if (ocp == 2)
	{
		if (g_op_tab[chariot->ope - 1].label_size)
			return (T_DIR_TWO);
		return (T_DIR_FOUR);
	}
	if (ocp == 3)
		return (2);
	return (-1);
}

int		ft_jump(t_war *war, t_chariot *chariot)
{
	unsigned char	ocp;
	int				jump;

	ocp = (unsigned char)war->arena[calc_addr(C_POS + 1)];
	jump = 2;
	if (chariot->ope == 1)
	{
		chariot->last_live = war->cycles;
		return (5);
	}
	if (chariot->ope == 12 || chariot->ope == 15 || chariot->ope == 9)
		return (3);
	jump += calc_jump((ocp >> 6), chariot);
	if (g_op_tab[chariot->ope - 1].nb_params >= 2)
		jump += calc_jump(((ocp & 0x30) >> 4), chariot);
	if (g_op_tab[chariot->ope - 1].nb_params == 3)
		jump += calc_jump(((ocp & 0x0C) >> 2), chariot);
	return (jump);
}
