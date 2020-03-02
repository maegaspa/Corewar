/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/28 20:34:34 by hmichel          ###   ########lyon.fr   */
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
	*(war->begin) = chariot;
	//while ()
	//{
	printf("GAME START\n");
	ft_print_war(war);
	while (war->cycles < war->to_die)
	{
		while (chariot)
		{
			ft_exec_opp(chariot, war, opp_tab);
			chariot = chariot->next;
		}
		chariot = *(war->begin);
		war->cycles++;
		printf("cycles++\n");
		//if (war->cycles < 30)
			//ft_print_war(war);
		if (war->cycles > 70)
			break ;
	}
	//}
	return (SUCCESS);
}
