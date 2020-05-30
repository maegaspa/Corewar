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

	if (chariot->ope != -1)
		return (0);
	pos = calc_addr(chariot->start_pos + chariot->pc);
	if (war->arena[pos] > 16 || war->arena[pos] <= 0)
	{
		chariot->pc++;
		return (0);
	}
	else
		chariot->ope = war->arena[pos];
	return (1);
}

int			is_conform(char ocp, t_chariot *chariot, t_war *war)
{
//	int		i;
//
//	i = -1;
//    printf("ocp = %d\n", ocp);
	if (ocp == 0)
		return (FAILURE);
	if (ocp == 1) //&& //get_val(war, chariot, war->jump) > 0 &&
		//get_val(war, chariot, war->jump) <= 16 &&
		//(0x01 & g_op_tab[chariot->ope - 1].params_type[param]))
	{
		war->rtype[war->i_ocp] = REG_CODE;
		war->i_ocp++;
		return (T_REG);
	}
	if (ocp == 2) //&& (0x02 & g_op_tab[chariot->ope - 1].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 4) >= 2
	{
		war->rtype[war->i_ocp] = DIR_CODE;
		war->i_ocp++;
		if (g_op_tab[chariot->ope - 1].label_size)
			return (T_DIR_TWO);
		return (T_DIR_FOUR);
	}
	if (ocp == 3) //&& (0x04 & g_op_tab[chariot->ope - 1].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 8) >= 4
	{

		war->rtype[war->i_ocp] = IND_CODE;
		war->i_ocp++;
		return (2);
	}
	return (FAILURE);
}

int			ft_tcheck_ocp(t_chariot *chariot, t_war *war)//return jump
{
	unsigned char		ocp;

	war->i_ocp = 0;
	if (chariot->ope == 1)
		return (5);
	if (g_op_tab[chariot->ope - 1].acb == 0)
		return (3);
	war->jump = 2;
	ocp = war->arena[calc_addr(chariot->start_pos + chariot->pc + 1)];
	//printf("ocp = %d\n", ocp);
	if (ocp <= 0)
		return (FAILURE);
	if (!(war->jump += is_conform((ocp >> 6), chariot, war)))
		return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params >= 2)
		if (!(war->jump += is_conform(((ocp & 0x30) >> 4), chariot, war)))
			return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params == 3)
		if (!(war->jump += is_conform(((ocp & 0x0C) >> 2), chariot, war)))
			return (FAILURE);
	//printf("TCHECK OCP war->rtype[0] = [%d] | war->rtype[1] =  [%d] |  war->rtype[2] =  [%d]\n", war->rtype[0], war->rtype[1], war->rtype[2]);
	//printf("1 = %d\n", war->jump);
	return (war->jump);
}

void		ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab)
{
	int		jump;
	int 	jump2;

	jump = 0;
	jump2 = 0;
	if (chariot->wait > 0)
		chariot->wait--;
	if ((chariot->wait == 0) && chariot->ope > 0)
	{
		if ((jump = ft_tcheck_ocp(chariot, war)) == (jump2 = get_all_param(chariot, war, chariot->ope - 1)))
		{
//			printf("GAY\n");
			chariot->addr = calc_addr(chariot->start_pos + chariot->pc);
			opp_tab[chariot->ope - 1](war, chariot);
			if (chariot->ope != 3)
				print_verbose_16(war, chariot, jump);
			if (war->back_pc == 0)
				chariot->pc = calc_addr(chariot->pc + jump);
			war->back_pc = 0;
		}
		else
        {
//        	printf("jump = %d\n", jump);
            print_verbose_16(war, chariot, jump);
            chariot->pc = calc_addr(chariot->pc + jump);
//        	printf("ope = %d et pos = %d\n", chariot->ope, calc_addr(chariot->start_pos + chariot->pc));
        }
		chariot->ope = -1;
	}
	if (ft_get_op(war, chariot) == 1) //&& chariot->ope >= 1) //on tcheck si on lit une nouvelle operande, si oui on init "wait"
    	chariot->wait = war->op_cycle[chariot->ope - 1];
}

int 	calc_addr(int addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}