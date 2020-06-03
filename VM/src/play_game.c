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

int		is_one_direct_arg(t_war *war, t_chariot *chariot)
{
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
	return (0);
}

int		check_param_valid(t_war *war, t_chariot *chariot, int tmpc, int i)
{
	if (war->rtype[i] == DIR_CODE)
	{
		if (g_op_tab[chariot->ope - 1].label_size == 0)
		{
			war->param[i] = get_4_val(war, chariot, tmpc);
			return (4);
		}
		else
		{
			war->param[i] = get_2_val(war, chariot, tmpc);
			return (2);
		}
	}
	else if (war->rtype[i] == REG_CODE)
	{
		war->param[i] = get_val(war, chariot, tmpc);
		return (1);
	}
	else if (war->rtype[i] == IND_CODE)
	{
		war->param[i] = get_2_val(war, chariot, tmpc);
		return (2);
	}
	return (0);
}

int		get_all_param(t_chariot *chariot, t_war *war)
{
	int		i;
	int		tmpc;

	i = -1;
	tmpc = 1;
	if (g_op_tab[chariot->ope - 1].acb != 0)
		tmpc += 1;
	while (++i < g_op_tab[chariot->ope - 1].nb_params)
		war->param[i] = 0;
	if ((i = is_one_direct_arg(war, chariot)) != 0)
		return (i);
	i = -1;
	while (++i < g_op_tab[chariot->ope - 1].nb_params)
		tmpc += check_param_valid(war, chariot, tmpc, i);
	return (tmpc);
}

void	play_cycle(t_war *war, t_chariot *chariot, t_parse_file *file,
		t_opp opp_tab[])
{
	int i;

	i = -1;
	if (file->dump == war->cycles || file->long_dump == war->cycles)
		print_arena(war, file);
	if (war->cycles == file->cycles || file->dump == war->cycles ||
			file->long_dump == war->cycles)
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
	while (chariot && war->visual.pause != 1)
	{
		ft_exec_opp(chariot, war, opp_tab);
		chariot = chariot->next;
	}
}

int		ft_game(t_war *war, t_parse_file *file)
{
	t_chariot		*chariot;
	t_opp			opp_tab[16];

	init_tab(opp_tab);
	if (war->visu == 1)
		visu_body(war);
	if ((file->error = ft_start_chariot(war, &chariot, file)) <= 0)
		return (file->error);
	war->begin = chariot;
	while (COREWAR)
	{
		play_cycle(war, chariot, file, opp_tab);
		if (war->cycle_to_die == war->cycles_btw_check ||
				war->cycle_to_die <= 0)
			if (check_cycle(war) == FAILURE)
				break ;
	}
	while (war->visu == 1)
		get_keys(war);
	return (SUCCESS);
}
