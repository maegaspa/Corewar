/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/25 21:44:24 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	init_tab(t_test *test)
{
	ft_bzero(test, 2);
	test[0] = &live_fct;
	test[1] = &ld_fct;
	test[2] = &st_fct;
	test[3] = &add_fct;
	test[4] = &sub_fct;
	test[5] = &and_fct;
	test[6] = &or_fct;
	test[7] = &xor_fct;
	test[8] = &zjmp_fct;
	test[9] = &ldi_fct;
	test[10] = &sti_fct;
	test[11] = &fork_fct;
	test[12] = &lld_fct;
	test[13] = &lldi_fct;
	test[14] = &lfork_fct;
	test[15] = &aff_fct;
}

int		ft_game(t_war *war)
{
	t_proc		*chariot;

	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = &chariot;
	//while (ft_game_on())
	while (war->cycles < war->to_die)
	{
		while (chariot != NULL)
		{
			ft_exec_opp(chariot, war);
			chariot = chariot->next;
		}
		chariot = (*begin);
		war->cycles++;
	}
	return (SUCCESS);
}
/*
int		play_game(t_war *war)
{
	t_test test[16];

	init_tab(test);
	war->to_die = CYCLE_TO_DIE - 1;
	set_procs(war);

	while (war->procs)
	{
//		do_processus(war, test);
//		check_live();
//		cycle_to_die();

//		set_procs();
	}

	ft_printf("%d\n", war->to_die);
	return (0);
}*/
