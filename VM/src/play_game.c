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
		if (war->rtype[i] == DIR_CODE)
		{
			if (g_op_tab[ope].label_size == 0)
			{
				war->param[i] = get_4_val(war, chariot, tmpc);
				tmpc += 4;
			}
			else
			{
				war->param[i] = get_2_val(war, chariot, tmpc);
				tmpc += 2;
			}
		}
		else if (war->rtype[i] == REG_CODE)
		{
			war->param[i] = get_val(war, chariot, tmpc);
			tmpc += 1;
		}
		else if (war->rtype[i] == IND_CODE)
		{
			war->param[i] = get_2_val(war, chariot, tmpc);
			tmpc += 2;
		}
	}
	return (tmpc);
}

int		ft_game(t_war *war, t_parse_file *file)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp_tab[16];
	int 			i;

	init_tab(opp_tab);
	war->aff = file->a;
	i = -1;
	while (++i < 6)
		war->verbose[i] = file->verbose[i];
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = chariot;
	war->cycle_last_check = 0;
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
		war->cycles++;
        war->cycles_btw_check++;
		if (war->cycles && war->verbose[3] == 1)
        	printf("It is now cycle %d\n", war->cycles);
		chariot = war->begin;
		while (chariot)
		{
			ft_exec_opp(chariot, war, opp_tab);
			chariot = chariot->next;
		}
		while (war->visu == 1)
			get_keys(war);
		if (war->cycle_to_die == war->cycles_btw_check || war->cycle_to_die <= 0)
			if (check_cycle(war) == FAILURE)
				break ;
	}
	return (SUCCESS);
}
