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

#include "../../includes/corewar.h"

void	print_cursor(t_war *war)
{
	int			pos;
	t_chariot	*chariot;

	war->visual.process_nb = 0;
	chariot = war->begin;
	while (chariot)
	{
		pos = (chariot->start_pos + chariot->pc) % MEM_SIZE;
		wattron(war->visual.arena_win, COLOR_PAIR(chariot->player));
		mvwprintw(war->visual.arena_win, (pos / 64) + 1, ((pos % 64) * 3) + 2,
			"%02x", (unsigned char)war->arena[pos]);
		wattroff(war->visual.arena_win, COLOR_PAIR(chariot->player));
		chariot->prev_cursor = pos;
		war->visual.process_nb++;
		chariot = chariot->next;
	}
}

void	infos_print(t_war *war)
{
	int i;

	i = 0;
	mvwprintw(war->visual.infos_win, 4, 20, "%d", war->cycles);
	mvwprintw(war->visual.infos_win, 6, 20, "%d    ", war->nb_chariot);
	mvwprintw(war->visual.infos_win, 30, 24, "%d    ", war->cycle_to_die);
	mvwprintw(war->visual.infos_win, 28, 4, "LAST CHECK : \t%d   ",
		war->cycle_last_check);
	mvwprintw(war->visual.infos_win, 28, 34, "NEXT CHECK : \t%d   ",
		war->cycles_btw_check);
	mvwprintw(war->visual.infos_win, 6, 34, "NB LIVE : \t%d    ",
		war->nb_lives);
	while (++i <= war->nb_player)
		mvwprintw(war->visual.infos_win, 6 + (4 * i) + 1, 6,
			"                     ");
	mvwprintw(war->visual.infos_win, 6 + (4 * war->lastlive) + 1, 6,
		" -> Last player alive");
}

void	refresh_arena(t_war *war)
{
	int i;
	int line;
	int col;

	i = 0;
	line = 1;
	col = 2;
	wattron(war->visual.arena_win, COLOR_PAIR(6));
	while (i < MEM_SIZE)
	{
		mvwprintw(war->visual.arena_win, line, col, "%02x",
			(unsigned char)war->arena[i]);
		col = col + 3;
		if (col >= 194)
		{
			col = 2;
			line++;
		}
		i++;
	}
	wattroff(war->visual.arena_win, COLOR_PAIR(6));
}

int		update_visu(t_war *war)
{
	if (war->visu != 1)
		return (SUCCESS);
	cbreak();
	nodelay(war->visual.infos_win, 1);
	get_keys(war);
	if (war->visual.pause == -1)
	{
		if (war->cycles != 0)
			usleep(war->visual.sleeptime);
		wrefresh(war->visual.infos_win);
		refresh_arena(war);
		print_cursor(war);
		infos_print(war);
		wrefresh(war->visual.infos_win);
		wrefresh(war->visual.arena_win);
		return (SUCCESS);
	}
	return (-1);
}
