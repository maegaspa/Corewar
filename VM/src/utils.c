/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/24 14:40:19 by seanseau         ###   ########lyon.fr   */
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
