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
	chariot = war->begin;
	while (chariot)
	{
		pos = (chariot->start_pos + chariot->pc) % MEM_SIZE;
		wattron(war->visual.arena_win, COLOR_PAIR(chariot->player));
		mvwprintw(war->visual.arena_win, (pos / 64) + 1,
		((pos % 64) * 3) + 2, "%02x", (unsigned char)war->arena[pos]);
		wattroff(war->visual.arena_win, COLOR_PAIR(chariot->player));
		chariot->prev_cursor = pos;
		war->visual.process_nb++;
		chariot = chariot->next;
	}
}

void	infos_print(t_war *war)
{
	mvwprintw(war->visual.infos_win, 4, 40, "%d", war->cycles);
	mvwprintw(war->visual.infos_win, 6, 40, "%d", war->visual.process_nb);
	mvwprintw(war->visual.infos_win, 30, 40, "%d", war->cycle_to_die);
	if (war->visual.sleeptime > 1000)
		mvwprintw(war->visual.infos_win, 2, 40, "%d ",
				1000000 / war->visual.sleeptime);
	else
		mvwprintw(war->visual.infos_win, 2, 40, "300");
}

/*void	arena_update(t_war *war)
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
			ft_memcpy(war->visual.arena_list[i - 1],
			war->visual.arena_list[i], MEM_SIZE);
		ft_memcpy(war->visual.arena_list[99], war->arena, MEM_SIZE);
	}
}*/

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
//	arena_update(war);
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
//	wrefresh(war->visual.arena_win);
//	wrefresh(war->visual.infos_win);
	return (-1);
}
