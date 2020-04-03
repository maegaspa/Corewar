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

#include "../includes/corewar.h"

void	cycle_keys(t_war *war, int c)
{
	int	temp_cursor;

	temp_cursor = war->visual.arena_cursor;
	if (war->visual.pause == 1)
	{
		if (c == 'a' && temp_cursor > 0)
		{
			temp_cursor--;
			color_arena(war, -1, war->visual.arena_win, war->visual.arena_list[temp_cursor]);
		}
		if (c == 'd' && temp_cursor < 100)
		{
			temp_cursor++;
			color_arena(war, -1, war->visual.arena_win, war->visual.arena_list[temp_cursor]);
		}
	}
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
}

void	get_keys(t_war *war)
{
	int c;


	c = wgetch(war->visual.infos_win);
	if (c == ' ')
		war->visual.pause = -war->visual.pause;
	if (c == '-' || c == '+')
		sleep_keys(war, c);
	if (c == 'a' || c == 'd')
		cycle_keys(war, c);
}
