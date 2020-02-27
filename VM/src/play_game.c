/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 23:24:01 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_game(t_war *war)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp_tab[16];

	init_tab(opp_tab);
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = &chariot;
	//while ()
	//{
		while (war->cycles < war->to_die)
		{
			while (chariot)
			{
				ft_exec_opp(chariot, war, opp_tab);
				chariot = chariot->next;
			}
			//		chariot = (*war->begin);
			war->cycles++;
		}
	//}
	return (SUCCESS);
}
