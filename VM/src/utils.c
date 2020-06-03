/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:06 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				nbr_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)) || \
			(c >= 'a' && c <= ('a' + base - 10)));
}

void			print_arena_2(t_war *war, int dump)
{
	int				i;
	int				count_bytes;
	int				bytes;

	count_bytes = 0;
	bytes = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i == 0)
			printf("0x%04x : ", bytes);
		if (count_bytes == 0 && i)
			printf("%#06x : ", bytes);
		printf("%02x ", (unsigned char)war->arena[i]);
		count_bytes++;
		if (count_bytes == dump)
		{
			printf("\n");
			count_bytes = 0;
			bytes += dump;
		}
	}
}

int				print_arena(t_war *war, t_parse_file *file)
{
	int				dump;

	dump = 64;
	if (file->long_dump != -1)
		dump = 64;
	else if (file->dump != -1)
		dump = 32;
	else
		return (FAILURE);
	print_arena_2(war, dump);
	return (SUCCESS);
}

void			print_verbose_16(t_war *war, t_chariot *chariot, int size)
{
	int i;

	if (war->verbose[0] == 1)
	{
		i = 0;
		war->status[chariot->player - 1] = calc_addr(C_POS);
		printf("ADV %d (0x%04x -> %#06x) ", size,
			war->status[chariot->player - 1],
			war->status[chariot->player - 1] + size);
		while (i < size)
		{
			printf("%02x ", (unsigned char)war->arena[calc_addr(C_POS + i)]);
			i++;
		}
		printf("\n");
	}
}

void			write_on_arena(t_war *war, int value, int start, int size)
{
	int				rest;
	int				swap_size;
	unsigned int	val;

	val = value;
	rest = 1;
	start = start % MEM_SIZE;
	swap_size = size;
	if (start < 0)
		start += MEM_SIZE;
	while (--swap_size > 0)
		rest *= 256;
	while (size)
	{
		war->arena[start] = (val / rest);
		val = (unsigned int)val % rest;
		rest /= 256;
		size--;
		start = (start + 1) % MEM_SIZE;
	}
}
