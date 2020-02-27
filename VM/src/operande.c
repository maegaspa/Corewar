/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/27 13:33:12 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			ft_stand_op(t_war *war, t_chariot *chariot)
{
	int		pos;

	pos = chariot->start_pos + chariot->pc;
	if (war->arena[pos] > 16 || war->arena[pos] == 0)
	{
		chariot->pc++;
		return (0);
	}
	else
		chariot->ope = war->arena[pos];
	return (1);
}

int			ft_get_op(t_war *war, t_chariot *chariot)
{
	if (chariot->ope == -1)
		return (ft_stand_op(war, chariot));
	return (0);
}

int			ft_tcheck_ocp(t_chariot *chariot, t_war *war)
{
	char		ocp;
	int			i;

	i = -1;
	ocp = war->arena[chariot->start_pos + chariot->pc + 1];
	while (++i < g_op_tab[chariot->ope - 1].nb_params)
	{
		//a reprendre gestion tcheck ocp/longueur param
	}
	
}

int			ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab)
{
	if (chariot->wait > 0)
	{
		chariot->wait--;
		return (SUCCESS);
	}
	if (chariot->wait == 0 && chariot->ope > 0)
	{




		opp_tab[chariot->ope - 1](war, chariot);
		//chariot->pc = jump...
		chariot->ope = -1;
		return (SUCCESS);
	}
	if (ft_get_op(war, chariot) == 1) //on tcheck si on lit une nouvelle operande, si oui on init "wait"
		chariot->wait = war->op_cycle[chariot->ope - 1];
	return (SUCCESS);
	//ft_printf("ope chariot [%d]: %d\n", chariot->index, chariot->ope);
}
