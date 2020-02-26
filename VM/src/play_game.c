/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:41:07 by seanseau         ###   ########lyon.fr   */
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




void	ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab)
{
	//check wait, live
	ft_get_op(war, chariot);
	ft_printf("ope chariot [%d]: %d\n", chariot->index, chariot->ope);
	opp_tab[chariot->ope](war, chariot);
}

int		ft_game(t_war *war)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp[16];

	init_tab(opp);
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = &chariot;
	while (war->cycles < war->to_die)
	{
		while (chariot)
		{
			ft_exec_opp(chariot, war, opp);
			chariot = chariot->next;
		}
		//		chariot = (*war->begin);
		war->cycles++;
	}
	return (SUCCESS);
}
