/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 23:24:48 by hmichel          ###   ########lyon.fr   */
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

int 			print_arena(t_war *war, t_parse_file *file)
{
	int i;
	int count_bytes;
	int dump;
	unsigned int bytes;

	i = -1;
	count_bytes = 0;
	dump = 64;
	bytes = 0;
	if (file->long_dump != -1)
		dump = 64;
	else if (file->dump != -1)
		dump = 32;
	else
		return (FAILURE);
	ft_printf("\n");
	while (++i < MEM_SIZE)
	{
		if (count_bytes == 0)
			ft_printf("%#06x : ", bytes);
		ft_printf("%02x ", (unsigned char)war->arena[i]);
		count_bytes++;
		if (count_bytes == dump)
		{
			ft_printf("\n");
			count_bytes = 0;
			bytes += dump;
		}
	}
	return (SUCCESS);
}

void			ft_init_op_cycle(t_war *war)
{
	war->op_cycle[0] = 10;
	war->op_cycle[1] = 5;
	war->op_cycle[2] = 5;
	war->op_cycle[3] = 10;
	war->op_cycle[4] = 10;
	war->op_cycle[5] = 6;
	war->op_cycle[6] = 6;
	war->op_cycle[7] = 6;
	war->op_cycle[8] = 20;
	war->op_cycle[9] = 25;
	war->op_cycle[10] = 25;
	war->op_cycle[11] = 800;
	war->op_cycle[12] = 10;
	war->op_cycle[13] = 50;
	war->op_cycle[14] = 1000;
	war->op_cycle[15] = 2;
}

void	init_tab(t_opp *opp_tab)
{
	ft_bzero(opp_tab, 16);
	opp_tab[0] = &live_fct;
	opp_tab[1] = &ld_fct;
	opp_tab[2] = &st_fct;
	opp_tab[3] = &add_fct;
	opp_tab[4] = &sub_fct;
	opp_tab[5] = &and_fct;
	opp_tab[6] = &or_fct;
	opp_tab[7] = &xor_fct;
	opp_tab[8] = &zjmp_fct;
	opp_tab[9] = &ldi_fct;
	opp_tab[10] = &sti_fct;
	opp_tab[11] = &fork_fct;
	opp_tab[12] = &lld_fct;
	opp_tab[13] = &lldi_fct;
	opp_tab[14] = &lfork_fct;
	opp_tab[15] = &aff_fct;
}
void			ft_init_war(t_parse_file file, t_war *war)
{
	war->cycles = 0;
	war->to_die = CYCLE_TO_DIE; //1536
	war->nb_player = file.nb_player;
	war->dump = file.dump;
	ft_init_op_cycle(war); // a vpor si bien init dans parser
}
