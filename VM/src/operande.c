/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:00:44 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			ft_get_op(t_war *war, t_chariot *chariot)
{
	int		pos;

	pos = calc_addr(chariot->start_pos + chariot->pc);
	chariot->ope = war->arena[pos];
	if (chariot->ope >= 1 && chariot->ope <= 16)
		chariot->wait = war->op_cycle[chariot->ope - 1];
	return (1);
}

int			ft_tcheck_ocp(t_chariot *chariot, t_war *war)
{
	unsigned char		ocp;
	int					i;

	i = -1;
	while (++i < 3)
		war->rtype[i] = 0;
	war->i_ocp = 0;
	if (g_op_tab[chariot->ope - 1].acb == 0)
		return (SUCCESS);
	war->jump = 2;
	ocp = (unsigned char)war->arena[calc_addr(
			chariot->start_pos + chariot->pc + 1)];
	if (!is_conform((ocp >> 6), chariot, war))
		return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params >= 2)
		if (!is_conform(((ocp & 0x30) >> 4), chariot, war))
			return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params == 3)
		if (!is_conform(((ocp & 0x0C) >> 2), chariot, war))
			return (FAILURE);
	return (SUCCESS);
}

void		exec_jump(t_chariot *chariot, t_war *war, t_opp *opp_tab)
{
	int		jump;

	jump = 0;
	if (chariot->ope >= 1 && chariot->ope <= 16)
	{
		jump = ft_jump(war, chariot);
		if (ft_tcheck_ocp(chariot, war))
		{
			get_all_param(chariot, war);
			opp_tab[chariot->ope - 1](war, chariot);
		}
		if (war->back_pc == 0)
		{
			print_verbose_16(war, chariot, jump);
			chariot->pc = calc_addr(chariot->pc + jump);
		}
	}
	else
		chariot->pc = calc_addr(chariot->pc + 1);
}

void		ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab)
{
	if (chariot->wait == 0)
		ft_get_op(war, chariot);
	if (chariot->wait > 0)
		chariot->wait--;
	if (chariot->wait == 0)
		exec_jump(chariot, war, opp_tab);
	war->back_pc = 0;
}
