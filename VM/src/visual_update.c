/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:53:06 by seanseau          #+#    #+#             */
/*   Updated: 2020/03/10 17:42:25 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	print_cursor(t_war *war)
{
	int			pos;
	t_chariot	*chariot;

	war->visual.process_nb = 0;
	//chariot = war->begin;
	chariot = war->begin;
	while (chariot)
	{
		if (chariot->ope != -1 && chariot->wait != 0)
		{
			if (chariot->prev_cursor != -1)
			{
				wattron(war->visual.arena_win, COLOR_PAIR(chariot->prev_color));
				mvwprintw(war->visual.arena_win, (chariot->prev_cursor / 64) + 1, ((chariot->prev_cursor % 64) * 3) + 2, "%02x", (unsigned char)war->arena[chariot->prev_cursor]);
				wattroff(war->visual.arena_win, COLOR_PAIR(chariot->prev_color));
			}
			wattron(war->visual.arena_win, COLOR_PAIR(war->nb_player - chariot->index) | A_STANDOUT);
			pos = chariot->start_pos + chariot->pc;
			mvwprintw(war->visual.arena_win, (pos / 64) + 1, ((pos % 64) * 3) + 2, "%02x", (unsigned char)war->arena[pos]);
			wattroff(war->visual.arena_win, COLOR_PAIR(war->nb_player - chariot->index) | A_STANDOUT);
			chariot->prev_cursor = pos;
			chariot->prev_color = (mvwinch(war->visual.arena_win, (pos / 64) + 1, ((pos % 64) * 3) + 2) & A_COLOR) / 256;
		}
		war->visual.process_nb++;
		chariot = chariot->next;
	}
	//free(zob);
}

void	infos_print(t_war *war)
{
	mvwprintw(war->visual.infos_win, 4, 40, "%d", war->cycles);
	mvwprintw(war->visual.infos_win, 6, 40, "%d", war->visual.process_nb);
	mvwprintw(war->visual.infos_win, 30, 40, "%d", war->to_die);


	//REVOIR LES CYCLES/SECONDES A LA FIN
	if (war->visual.sleeptime > 1000)
		mvwprintw(war->visual.infos_win, 2, 40, "%d ", 1000000 / war->visual.sleeptime);
	else
		mvwprintw(war->visual.infos_win, 2, 40, "300");
}

void	arena_update(t_war *war)
{
	int i;

	i = 0;
	if (war->cycles < 100)
	{
		war->visual.arena_cursor = war->cycles;
		ft_memcpy(war->visual.arena_list[war->cycles], war->arena, MEM_SIZE);
	}
	else
	{
		while (++i < 99)
			ft_memcpy(war->visual.arena_list[i - 1], war->visual.arena_list[i], MEM_SIZE);
		ft_memcpy(war->visual.arena_list[99], war->arena, MEM_SIZE);
	}
}

int		update_visu(t_war *war)
{

	cbreak();
	nodelay(war->visual.infos_win, 1);
	get_keys(war);
	arena_update(war);
	if (war->visual.pause == -1)
	{
		usleep(war->visual.sleeptime);
		wrefresh(war->visual.infos_win);
		print_cursor(war);

		infos_print(war);

		wrefresh(war->visual.infos_win);
		wrefresh(war->visual.arena_win);
		return (SUCCESS);
	}
//	wrefresh(war->visual.infos_win);
//	wrefresh(war->visual.arena_win);
	return (-1);
}//NEED UNE FONCTION QUI RECOLORE QUAND FINIT UNE INSTRUCTION ; UN COMPTE EN TEMPS REEL DES CYCLES/TO_DIE/NBR_LIVE/MAX_CHECKS ; CURSOR SUR REPLAY ? ; A LA FIN REWORK CYCLE/S
