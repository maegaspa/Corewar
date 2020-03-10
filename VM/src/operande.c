/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/03/10 15:50:58 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			ft_get_op(t_war *war, t_chariot *chariot)
{
	int		pos;

	if (chariot->ope != -1)
		return (0);
	pos = chariot->start_pos + chariot->pc;
	if (war->arena[pos] > 16 || war->arena[pos] <= 0)
	{
		chariot->pc++;
		return (0);
	}
	else
		chariot->ope = war->arena[pos];
	return (1);
}

int			is_conform(char ocp, int param, int ope)
{
	//printf("ocp recu %d\n", (int)ocp);
	//	ft_printf("\n");
	if (ocp == 0)
		return (FAILURE);
	if (ocp == 1 && (0x01 & g_op_tab[ope].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 2) == 1
	{
		//printf("param %d is a register\n", param);
		return (T_REG);
	}
	if (ocp == 2 && (0x02 & g_op_tab[ope].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 4) >= 2
	{
		//printf("param %d is a direct\n", param);
		if (g_op_tab[ope].label_size)
			return (T_DIR_TWO);
		return (T_DIR_FOUR);
	}
	if (ocp == 3 && (0x04 & g_op_tab[ope].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 8) >= 4
	{
		//printf("param %d is an index\n", param);
		return (T_IND);
	}
	//printf("error ocp\n");
	return (FAILURE);
}

int			ft_tcheck_ocp(t_chariot *chariot, t_war *war)//return jump
{
	char		ocp;
	int			i;
	int			jump;

	if (g_op_tab[chariot->ope - 1].acb == 0)//ope n'a pas d'ocp
		return (2);
	i = -1;
	jump = 2;//ope et ocp de 1 octet
	ocp = war->arena[chariot->start_pos + chariot->pc + 1];
	//printf("ocp = %d\n", ocp);
	if (!(jump += is_conform(ocp >> 6, 0, chariot->ope - 1)))
		return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params >= 2)
		if (!(jump += is_conform(((ocp & 0x30) >> 4), 1, chariot->ope - 1)))
			return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params == 3)
		if (!(jump += is_conform((ocp & 0x0C) >> 2, 2, chariot->ope - 1)))
			return (FAILURE);
	return (jump);
}

void		ft_exec_opp(t_chariot *chariot, t_war *war/*, t_opp *opp_tab*/)
{
	int		jump;

	jump = 0;
	if (war->visual.pause == -1)
	{
		if (chariot->wait > 0)
		{
			chariot->wait--;
		}
		if (chariot->wait == 0 && chariot->ope > 0)
		{
			printf("EXEC_OPP\n");
			if ((jump = ft_tcheck_ocp(chariot, war)))
			{
				//jump = ft_jump(chariot, war);
				//opp_tab[chariot->ope - 1](war, chariot);
				chariot->pc += jump;
			}
			chariot->ope = -1;
		}
		if (ft_get_op(war, chariot) == 1) //&& chariot->ope >= 1) //on tcheck si on lit une nouvelle operande, si oui on init "wait"
			chariot->wait = war->op_cycle[chariot->ope - 1];
	}
	ft_print_chariot(chariot, 0); //reg == 1 pour afficher les registres
	ft_printf("ope chariot [%d]: %d\n", chariot->index, chariot->ope);
//	return (SUCCESS);
	//ft_printf("ope chariot [%d]: %d\n", chariot->index, chariot->ope);
}
