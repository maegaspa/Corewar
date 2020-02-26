/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 15:50:05 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	init_tab(t_opp *opp_tab)
{
	ft_bzero(opp_tab, 2);
	opp_tab[0] = &live_fct;
	opp_tab[1] = &ld_fct;
	opp_tab[2] = &st_fct;
	opp_tab[3] = &add_fct;
	opp_tab[4] = &sub_fct;
	opp_tab[5] = &and_fct;
	opp_tab[6] = &or_fct;
	opp_tab[7] = &xor_fct;
	opp_tab[8] = &zjmp_fct;
	opp_tab[9] = &ldi_fct;
	opp_tab[10] = &sti_fct;
	opp_tab[11] = &fork_fct;
	opp_tab[12] = &lld_fct;
	opp_tab[13] = &lldi_fct;
	opp_tab[14] = &lfork_fct;
	opp_tab[15] = &aff_fct;
}

int		ft_game(t_war *war)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp[16];

	init_tab(opp);
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);

	ft_printf("valeur start pos war begin chariot : %d\n", chariot->start_pos);

	war->begin = &chariot;
	//while (ft_game_on())
	while (war->cycles < war->to_die)
	{
		while (chariot)
		{
			ft_printf("chariot actuel : start_pos : %d\n", chariot->start_pos);
		//	ft_exec_opp(chariot, war, opp);
			chariot = chariot->next;
		}
		chariot = (*war->begin);
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
