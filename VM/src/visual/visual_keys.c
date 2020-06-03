/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 04:14:10 by seanseau          #+#    #+#             */
/*   Updated: 2020/03/09 13:20:30 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_cursor_temp(t_war *war, int temp)
{
	int			pos;
	t_chariot	*chariot;

	war->visual.process_nb = 0;
	chariot = war->begin;
	while (chariot)
	{
		pos = (chariot->start_pos + chariot->pc) % MEM_SIZE;
		wattron(war->visual.arena_win, COLOR_PAIR(chariot->player));
		mvwprintw(war->visual.arena_win, (pos / 64) + 1,
			((pos % 64) * 3) + 2, "%02x",
			(unsigned char)war->visual.arena_list[temp][pos]);
		wattroff(war->visual.arena_win, COLOR_PAIR(chariot->player));
		chariot->prev_cursor = pos;
		war->visual.process_nb++;
		chariot = chariot->next;
	}
}

void	refresh_arena_temp(t_war *war, int temp)
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
				(unsigned char)war->visual.arena_list[temp][i]);
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

void	sleep_keys(t_war *war, int c)
{
	if (c == '-' && war->visual.sleeptime < 1000000)
		war->visual.sleeptime *= 10;
	if (war->visual.sleeptime == 10)
		war->visual.sleeptime = 10000;
	if (c == '+' && war->visual.sleeptime > 1000)
		war->visual.sleeptime /= 10;
	if (war->visual.sleeptime == 1000)
		war->visual.sleeptime = 1;
	if (war->visual.sleeptime > 1000)
		mvwprintw(war->visual.infos_win, 2, 20, "%d ",
				1000000 / war->visual.sleeptime);
	else
		mvwprintw(war->visual.infos_win, 2, 20, "300");
	wrefresh(war->visual.infos_win);
}

void	fnct_pause(t_war *war)
{
	war->visual.pause = war->visual.pause * -1;
	if (war->visual.pause == -1)
	{
		wattron(war->visual.keys_win, COLOR_PAIR(1));
		mvwprintw(war->visual.keys_win, 2, 36, "[SPACE BAR]");
		wattroff(war->visual.keys_win, COLOR_PAIR(1));
	}
	else
	{
		wattron(war->visual.keys_win, COLOR_PAIR(3));
		mvwprintw(war->visual.keys_win, 2, 36, "[SPACE BAR]");
		wattroff(war->visual.keys_win, COLOR_PAIR(3));
	}
	wrefresh(war->visual.keys_win);
}

void	get_keys(t_war *war)
{
	int c;

	c = wgetch(war->visual.infos_win);
	if (c == ' ')
		fnct_pause(war);
	if (c == '-' || c == '+')
		sleep_keys(war, c);
	if (c == 27)
	{
		endwin();
		exit(0);
	}
}
