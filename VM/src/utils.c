/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 18:24:32 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 18:28:13 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
