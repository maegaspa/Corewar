/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_body.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 04:10:53 by seanseau          #+#    #+#             */
/*   Updated: 2020/03/09 19:20:13 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include <curses.h>

void	color_arena(t_war *war, int p, WINDOW *arena_win, char *arena)
{
	int i;
	int line;
	int col;

	i = 0;
	line = 1;
	col = 2;
	while (++p < war->nb_player)
	{
		while (i < (MEM_SIZE / war->nb_player) * (p + 1))
		{
			if (i == (int)(war->player[p].pos_arena))
				wattron(arena_win, COLOR_PAIR(p + 1));
			if (i == (int)(war->player[p].pos_arena + war->player[p].prog_size))
				wattroff(arena_win, COLOR_PAIR(p + 1));
			mvwprintw(arena_win, line, col, "%02x  ", (unsigned char)arena[i]);
			col = col + 3;
			if (col >= 194)
			{
				col = 2;
				line++;
			}
			i++;
		}
	}
}

void	infos_printer(WINDOW *infos_win, t_war *war)
{
	int i;
	int pos;

	pos = 0;
	i = 0;
	war->visual.sleeptime = 1000000;
	mvwprintw(infos_win, 2, 4, "Actual speed :  1");
	mvwprintw(infos_win, 2, 26, "Cycle(s)/s");
	mvwprintw(infos_win, 4, 4, "Cycle :");
	mvwprintw(infos_win, 6, 4, "Processes : \t\t\t%d", war->visual.process_nb);
	while (++i <= war->nb_player)
	{
		pos = 6 + (4 * i);
		mvwprintw(infos_win, pos, 4, "Player - %d : ", i);
		wattron(infos_win, COLOR_PAIR(i));
		mvwprintw(infos_win, pos, 18, war->player[i - 1].real_name);
		wattroff(infos_win, COLOR_PAIR(i));
	}
	mvwprintw(infos_win, 30, 4, "Cycle to die : \t%d", CYCLE_TO_DIE);
	mvwprintw(infos_win, 32, 4, "Cycle delta : \t%d", CYCLE_DELTA);
	mvwprintw(infos_win, 34, 4, "NB_LIVE : \t\t%d", NBR_LIVE);
	mvwprintw(infos_win, 36, 4, "MAX CHECKS : \t%d", MAX_CHECKS);
}

void	keys_printer(WINDOW *keys_win)
{
	mvwprintw(keys_win, 2, 4, "PAUSE / RESUME : \t\t    [SPACE BAR]");
	mvwprintw(keys_win, 5, 4, "CHANGE SPEED : \t\t[+]\t\t[-]");
	mvwprintw(keys_win, 6, 31, "FASTER          SLOWER");
	mvwprintw(keys_win, 8, 7, "---------------------------------------------");
	mvwprintw(keys_win, 18, 7, "---------------------------------------------");
}

void	init_windows(t_war *war)
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	war->visual.process_nb = war->nb_player;
	war->visual.arena_cursor = 0;
	war->visual.arena_win = newwin(66, 196, 0, 0);
	box(war->visual.arena_win, 0, 0);
	color_arena(war, -1, war->visual.arena_win, war->arena);
	war->visual.infos_win = newwin(40, 60, 0, 200);
	box(war->visual.infos_win, 0, 0);
	infos_printer(war->visual.infos_win, war);
	war->visual.keys_win = newwin(25, 60, 41, 200);
	box(war->visual.keys_win, 0, 0);
	keys_printer(war->visual.keys_win);
}

int		visu_body(t_war *war)
{
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);
	get_valid_name(war);
	init_windows(war);
	wrefresh(war->visual.infos_win);
	wrefresh(war->visual.arena_win);
	wrefresh(war->visual.keys_win);
	return (SUCCESS);
}
