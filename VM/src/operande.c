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

int 			print_arena2(t_war *war)
{
	int i;
	int count_bytes;
	int dump;
	unsigned int bytes;

	i = -1;
	count_bytes = 0;
	dump = 32;
	bytes = 0;
	while (++i < MEM_SIZE)
	{
		if (i == 0)
        	printf("0x%04x : ", bytes);
		if (count_bytes == 0 && i)
			printf("%#06x : ", bytes);
		printf("%02x ", (unsigned char)war->arena[i]);
		count_bytes++;
		if (count_bytes == dump)
		{
			printf("\n");
			count_bytes = 0;
			bytes += dump;
		}
	}
	return (SUCCESS);
}

int			ft_get_op(t_war *war, t_chariot *chariot)
{
	int		pos;

	pos = calc_addr(chariot->start_pos + chariot->pc);
	chariot->ope = war->arena[pos];
	if (chariot->ope >= 1 && chariot->ope <= 16)
		chariot->wait = war->op_cycle[chariot->ope - 1];
	return (1);
}

int			is_conform(unsigned char ocp, t_chariot *chariot, t_war *war) //return 1 si ocp correspond au param, 0 sinon
{
	if (ocp == 0)
		return (FAILURE);
	if (ocp == 1 && get_val(war, chariot, war->jump) > 0 &&
		get_val(war, chariot, war->jump) <= 16 && (0x01 & g_op_tab[chariot->ope - 1].params_type[war->i_ocp]))
	{
		war->rtype[war->i_ocp] = REG_CODE;
		war->jump += 1;
		war->i_ocp++;
		return (SUCCESS);
	}
	if (ocp == 2 && (0x02 & g_op_tab[chariot->ope - 1].params_type[war->i_ocp]))
	{
		war->rtype[war->i_ocp] = DIR_CODE;
		war->i_ocp++;
		if (g_op_tab[chariot->ope - 1].label_size)
        	war->jump += T_DIR_TWO;
        else
			war->jump += T_DIR_FOUR;
		return (SUCCESS);
	}
	if (ocp == 3 && (0x04 & g_op_tab[chariot->ope - 1].params_type[war->i_ocp]))
	{
		war->rtype[war->i_ocp] = IND_CODE;
		war->jump += 2;
		war->i_ocp++;
		return (SUCCESS);
	}
	return (FAILURE);
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
	ocp = (unsigned char)war->arena[calc_addr(chariot->start_pos + chariot->pc + 1)];
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

void		ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab)
{
	int		jump;

	jump = 0;
	if (chariot->wait == 0)
    	ft_get_op(war, chariot);
    if (chariot->wait > 0)
    	chariot->wait--;
    if (chariot->wait == 0)
    {
    	if (chariot->ope >= 1 && chariot->ope <= 16)
    	{
    		jump = ft_jump(war, chariot);
    		if (ft_tcheck_ocp(chariot, war))
    		{
    			get_all_param(chariot, war, chariot->ope - 1);
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
    war->back_pc = 0;
}

//void		ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab)
//{
//	int		jump;
//	int		error;
//
//	error = 0;
//	jump = -1;
//	if (chariot->wait > 0)
//		chariot->wait--;
//	if ((chariot->wait == 0) && chariot->ope > 0)
//	{
//		jump = ft_jump(war, chariot);
//		if (ft_tcheck_ocp(chariot, war))
//		{
//			get_all_param(chariot, war, chariot->ope - 1);
//			opp_tab[chariot->ope - 1](war, chariot);
//			if (war->back_pc == 0)
//				print_verbose_16(war, chariot, jump);
//			if (war->back_pc == 0)
//				chariot->pc = calc_addr(chariot->pc + jump);
//			 war->back_pc = 0;
//		}
//		else //if ((unsigned char)war->arena[chariot->pc] != 0)
//        {
//            print_verbose_16(war, chariot, jump);
//            chariot->pc = calc_addr(chariot->pc + jump);
//            error = 1;
//        }
//		chariot->ope = -1;
//	}
//	//printf("war->back_pc %d\n", war->back_pc);
//	// if (/*!error && war->back_pc == 0 &&*/ ft_get_op(war, chariot) == 1)
// //    	chariot->wait = war->op_cycle[chariot->ope - 1];
//}

int 	calc_addr(int addr)
{
	addr %= MEM_SIZE;
	while (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}