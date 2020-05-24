/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 16:16:14 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int 	ft_check_type(int d_type, int type)
{
	if (d_type == T_REG)
		if (type == T_REG)
			return (SUCCESS);
	if (d_type == T_IND)
		if (type == T_IND)
			return (SUCCESS);
	if (d_type == T_DIR)
		if (type == T_DIR)
			return (SUCCESS);
	if (d_type == (T_REG + T_DIR))
		if (type == T_REG || type == T_DIR)
			return (SUCCESS);
	if (d_type == (T_IND + T_DIR))
		if (type == T_IND || type == T_DIR)
			return (SUCCESS);
	if (d_type == (T_IND + T_REG))
		if (type == T_IND || type == T_REG)
			return (SUCCESS);
	if (d_type == (T_REG + T_DIR + T_IND))
		if (type == T_REG || type == T_DIR || type == T_IND)
			return (SUCCESS);
	return (FAILURE);
}

//int		get_param(t_chariot *chariot, t_war *war)
//{
//	int i;
//	int error;
//
//	error = 0;
//	i = -1;
//	if (!(war->rtype = malloc(sizeof(int) * 3)))
//		return (ERROR_MALLOC);
//	while (++i < 3)
//		war->rtype[i] = 0;
//	i = -1;
//	while (++i < g_op_tab[chariot->ope - 1].nb_params)
//	{
//		printf("g_op_tab[chariot->ope - 1].params_type[%d] = %d\n", i, g_op_tab[chariot->ope - 1].params_type[i]);
//		if ((error = ft_check_type(g_op_tab[chariot->ope - 1].params_type[i], T_REG)) > 0)
//			war->rtype[i] = T_REG;
//		if ((error = ft_check_type(g_op_tab[chariot->ope - 1].params_type[i], T_DIR)) > 0)
//        	war->rtype[i] = T_DIR;
//        if (war->rtype[i] != T_DIR && (error = ft_check_type(g_op_tab[chariot->ope - 1].params_type[i], T_IND)) > 0)
//       		war->rtype[i] = T_IND;
//        if ((error = ft_check_type(g_op_tab[chariot->ope - 1].params_type[i], T_LAB)) > 0)
//       		war->rtype[i] = T_LAB;
//		printf("rtype[%d] = %d\n", i, war->rtype[i]);
//	}
//	return (SUCCESS);
//}

void	get_param(t_war *war, char *str)
{
//	int i = -1;
	if (!(war->rtype = malloc(sizeof(int) * 3)))
		return ;
	if (str[0] == '1' && str[1] == '0')
		war->rtype[0] = DIR_CODE;
	else if (str[0] == '0' && str[1] == '1')
		war->rtype[0] = REG_CODE;
	else if (str[0] == '1' && str[1] == '1')
		war->rtype[0] = IND_CODE;
	else
		war->rtype[0] = 0;
	if (str[2] == '1' && str[3] == '0')
		war->rtype[1] = DIR_CODE;
	else if (str[2] == '0' && str[3] == '1')
		war->rtype[1] = REG_CODE;
	else if (str[2] == '1' && str[3] == '1')
		war->rtype[1] = IND_CODE;
	else
		war->rtype[1] = 0;
	if (str[4] == '1' && str[5] == '0')
		war->rtype[2] = DIR_CODE;
	else if (str[4] == '0' && str[5] == '1')
		war->rtype[2] = REG_CODE;
	else if (str[4] == '1' && str[5] == '1')
		war->rtype[2] = IND_CODE;
	else
		war->rtype[2] = 0;
//	while (++i < 3)
//		printf("war->rtype[%d] = %d\n", i, war->rtype[i]);
}

void	fill_bin(char *str, char *fill, int j)
{
	int i;

	i = -1;
	while (fill[++i])
		str[j++] = fill[i];
}

int		get_bin_ocp(t_chariot *chariot, t_war *war)
{
	int 	i;
	char	str[10];
	int 	j;

	i = -1;
	j = 0;
	war->ocp = war->arena[chariot->start_pos + chariot->pc + 1];
	war->ocxp = ft_itoa_base((unsigned char)war->ocp, 16);
	while (war->ocxp[++i])
	{
		if (war->ocxp[i] == '0')
			fill_bin(str, "0000", j);
		if (war->ocxp[i] == '1')
			fill_bin(str, "0001", j);
		if (war->ocxp[i] == '2')
			fill_bin(str, "0010", j);
		if (war->ocxp[i] == '3')
			fill_bin(str, "0011", j);
		if (war->ocxp[i] == '4')
			fill_bin(str, "0100", j);
		if (war->ocxp[i] == '5')
			fill_bin(str, "0101", j);
		if (war->ocxp[i] == '6')
			fill_bin(str, "0110", j);
		if (war->ocxp[i] == '7')
			fill_bin(str, "0111", j);
		if (war->ocxp[i] == '8')
			fill_bin(str, "1000", j);
		if (war->ocxp[i] == '9')
			fill_bin(str, "1001", j);
		if (war->ocxp[i] == 'a' || war->ocxp[i] == 'A')
			fill_bin(str, "1010", j);
		if (war->ocxp[i] == 'b' || war->ocxp[i] == 'B')
			fill_bin(str, "1011", j);
		if (war->ocxp[i] == 'c' || war->ocxp[i] == 'C')
			fill_bin(str, "1100", j);
		if (war->ocxp[i] == 'd' || war->ocxp[i] == 'D')
			fill_bin(str, "1101", j);
		if (war->ocxp[i] == 'e' || war->ocxp[i] == 'E')
			fill_bin(str, "1110", j);
		if (war->ocxp[i] == 'f' || war->ocxp[i] == 'F')
			fill_bin(str, "1111", j);
		j = 4;
	}
	str[9] = '\0';
//	printf("str = %s\n", str);
	get_param(war, str);
	return (SUCCESS);
}

int		choose_ope(t_war *war, t_chariot *chariot)
{
	if (chariot->ope > 0)
	{
		if (chariot->ope == 1)
			live_fct(war, chariot);
		else if (chariot->ope == 2)
			ld_fct(war, chariot);
		else if (chariot->ope == 3)
			st_fct(war, chariot);
		else if (chariot->ope == 4)
			add_fct(war, chariot);
		else if (chariot->ope == 5)
			sub_fct(war, chariot);
		else if (chariot->ope == 6)
			and_fct(war, chariot);
		else if (chariot->ope == 7)
			or_fct(war, chariot);
		else if (chariot->ope == 8)
			xor_fct(war, chariot);
		else if (chariot->ope == 9)
			zjmp_fct(war, chariot);
		else if (chariot->ope == 10)
			ldi_fct(war, chariot);
		else if (chariot->ope == 11)
			sti_fct(war, chariot);
		else if (chariot->ope == 12)
			fork_fct(war, chariot);
		else if (chariot->ope == 13)
			lld_fct(war, chariot);
		else if (chariot->ope == 14)
			lldi_fct(war, chariot);
		else if (chariot->ope == 15)
			lfork_fct(war, chariot);
		else if (chariot->ope == 16)
			aff_fct(war, chariot);
		else
			return (-1);
	}
	return (SUCCESS);
}

int		ft_game(t_war *war, t_parse_file *file)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp_tab[16];

	init_tab(opp_tab);
	war->aff = file->a;
	war->verbose = file->verbose;
	war->status = 0;
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = chariot;
	printf("GAME START\n");
	chariot->pc = 0;
	ft_print_war(war);
	while (verif_endgame(war, chariot))
	{
		while (war->actual_cycles < war->to_die)
		{
			if (war->verbose[3] == 1)
				printf("It is now cycle [%d]\n", war->cycles);
			if (file->dump == war->cycles|| file->long_dump == war->cycles)
    	    	print_arena(war, file);
			while (chariot)
			{
//			printf("chariot wait = %d\n chariot->ope = %d", chariot->wait, chariot->ope);
				ft_exec_opp(chariot, war, opp_tab);
//			dprintf(1, "ptdr44 et ope = %d\n", chariot->ope);
			//printf("pi = [%d]ici pc = [%d] et index  = %d \n", pi, chariot->pc, chariot->index);
		/*if (chariot->pc > pi)
			if ((error = choose_ope(war, chariot)) <= 0)
					return (error);*/
//			printf("chariot->index = %d\n", chariot->index);
				//printf("PC A CHAQUE CYCLE = %d\n", chariot->pc);
				chariot = chariot->next;
			}
			chariot = war->begin;
			war->actual_cycles++;
			war->cycles++;
		//printf("cycles++\n");
//		ft_print_war(war);
		}
	}
	return (SUCCESS);
}

//int		ft_game_visu(t_war *war)
//{
//	t_chariot		*chariot;
//	int				error;
//	t_opp			opp_tab[16];
//
//	init_tab(opp_tab);
//	if (war->visu == 1)
//		visu_body(war);
//	if ((error = ft_start_chariot(war, &chariot)) <= 0)
//		return (error);
//	war->begin = chariot;
//	while (war->cycles < war->to_die)
//	{
//		while (chariot)
//		{
//			if (war->visual.pause == -1)
//				ft_exec_opp(chariot, war, opp_tab);
//			chariot = chariot->next;
//		}
//		chariot = war->begin;
//		if (update_visu(war) != -1)
//			war->cycles++;
//	}
//	return (SUCCESS);
//}
