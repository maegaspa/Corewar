/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 18:37:39 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

unsigned int	u_int_reverse_octet(unsigned int x)
{
	unsigned int rev;

	rev = x & 0xff000000;
	rev = rev >> 8;
	x = x << 8;
	rev = rev | (x & 0xff000000);
	rev = rev >> 8;
	x = x << 8;
	rev = rev | (x & 0xff000000);
	rev = rev >> 8;
	x = x << 8;
	rev = rev | (x & 0xff000000);
	return (rev);
}

void			print_arena(t_war *war)
{
	int i;
	int count_bytes;

	i = -1;
	count_bytes = 0;
	printf("\n");
	while (++i < MEM_SIZE)
	{
		printf("%02X ", (unsigned char)war->arena[i]);
		count_bytes++;
		if (count_bytes == 64)
		{
			printf("\n");
			count_bytes = 0;
		}
	}
}

void			ft_init_war(t_parse_file file, t_war *war)
{
	war->cycles = 0;
	war->to_die = CYCLE_TO_DIE; //1536
	war->nb_player = file.nb_player;
	war->dump = file.dump; // a vpor si bien init dans parser
}
