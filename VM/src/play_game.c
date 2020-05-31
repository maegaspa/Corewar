/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:19:50 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_val(t_war *war, t_chariot *chariot, int i)
{
	return ((unsigned char)war->arena[calc_addr(chariot->start_pos + chariot->pc + i)]);
}

int	get_all_param(t_chariot *chariot, t_war *war, int ope)
{
	int		i;
	int 	tmpc;

	i = -1;
	tmpc = 1;
	if (g_op_tab[chariot->ope - 1].acb != 0)
		tmpc += 1;
	//printf("%d\n", tmpc);
	//	printf("arena : %x\n", (unsigned char)war->arena[tmpc]);
	//printf("GET ALL PARAM war->rtype = 0 [%d] | 1 [%d] | 2 [%d]\n", war->rtype[0], war->rtype[1], war->rtype[2]);
	while (++i < g_op_tab[ope].nb_params)
		war->param[i] = 0;
	if (chariot->ope == 1)
	{
		war->param[0] = get_4_val(war, chariot, 1);
		return (5);
	}
	if (chariot->ope == 12 || chariot->ope == 15 || chariot->ope == 9)
	{
		war->param[0] = get_2_val(war, chariot, 1);
		return (3);
	}
	i = -1;
	while (++i < g_op_tab[ope].nb_params)
	{
		//printf("ON PASSE DANS BOUCLE\n");
		//		printf("get_val = %d\n", get_val(war, chariot, tmpc));
		//		if (war->rtype[i] == 0 || (war->rtype[i] == REG_CODE && (get_val(war, chariot, tmpc) <= 0 || get_val(war, chariot, tmpc) > 16)))
		//        {
		////				printf("ICI ????\n");
		//	        	return (-1);
		//        }
		if (war->rtype[i] == DIR_CODE)
		{
			//			printf("ON PASSE DANS DIR\n");
			if (g_op_tab[ope].label_size == 0)
			{
				war->param[i] = get_4_val(war, chariot, tmpc);
				tmpc += 4;
				//				printf("DANS DIR4\n", get_4_val(war, chariot, tmpc));
			}
			else
			{
				war->param[i] = get_2_val(war, chariot, tmpc);
				tmpc += 2;
				//				printf("DANS DIR2\n");
			}
		}
		else if (war->rtype[i] == REG_CODE) //&& get_val(war, chariot, tmpc) > 0 &&
			//get_val(war, chariot, tmpc) <= 16)
		{
			//printf("ON PASSE DANS REG\n");
			war->param[i] = get_val(war, chariot, tmpc);
			tmpc += 1;
			//			printf("DANS REG\n");
		}
		else if (war->rtype[i] == IND_CODE)
		{
			//			printf("ON PASSE DANS IND\n");
			war->param[i] = get_2_val(war, chariot, tmpc);
			tmpc += 2;
			//			printf("DANS IND = %d\n", get_2_val(war, chariot, tmpc) );
		}
	}
	//	printf("new war->param[0] =  %d | param[1] = %d | param[2] = %d\n", war->param[0], war->param[1], war->param[2]);
	//printf("2tmpc = %d\n", tmpc);
	return (tmpc);
}

int		ft_game(t_war *war, t_parse_file *file)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp_tab[16];
	int 			i;

	init_tab(opp_tab);
	//ft_init_war(file, war);
	if (war->visu == 1)
		visu_body(war);
	war->aff = file->a;
	i = -1;
	while (++i < 6)
		war->verbose[i] = file->verbose[i];
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = chariot;
	war->cycle_last_check = 0;//war->cycles;
	while (COREWAR)
	{
		if (file->dump == war->cycles || file->long_dump == war->cycles)
			print_arena(war, file);
		if (war->cycles  == file->cycles || file->dump == war->cycles || file->long_dump == war->cycles)
		{
			i = -1;
			while (++i < 6)
				war->verbose[i] = 0;
		}
		if (update_visu(war) != -1)
		{
			war->cycles++;
			war->cycles_btw_check++;
		}
		if (war->cycles && war->verbose[3] == 1)
			printf("It is now cycle %d\n", war->cycles);
		chariot = war->begin;
		while (chariot && war->visual.pause == -1)
		{
			ft_exec_opp(chariot, war, opp_tab);
			chariot = chariot->next;
		}
		if (war->cycle_to_die == war->cycles_btw_check || war->cycle_to_die <= 0)
			if (check_cycle(war) == FAILURE)
				break ;
	}
	while (war->visu == 1)
		get_keys(war);
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
