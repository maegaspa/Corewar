/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/03/10 15:52:35 by seanseau         ###   ########lyon.fr   */
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
	war->begin = chariot;

	printf("GAME START\n");
	ft_print_war(war);
	while (war->cycles < war->to_die)
	{
		while (chariot->next)
		{
			ft_exec_opp(chariot, war);//, opp_tab);
			chariot = chariot->next;
		}
		chariot = war->begin;
		war->cycles++;
	printf("------------------------------cycles++------------------------------\n");
	}
	return (SUCCESS);
}

int		ft_game_visu(t_war *war)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp_tab[16];

	init_tab(opp_tab);
	if (war->visu == 1)
		visu_body(war);
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = chariot;

	while (war->cycles < war->to_die)
	{
		while (chariot->next)
		{
			if (war->visual.pause == -1)
				ft_exec_opp(chariot, war);//, opp_tab);
			chariot = chariot->next;
		}
		chariot = war->begin;

			if (update_visu(war) != -1)
				war->cycles++;
	}
	return (SUCCESS);
}
