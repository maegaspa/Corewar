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
#include <stdio.h>

int			ft_pow(int nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

char		*ft_itoa_base(int value, int base)
{
	int		i;
	char	*nbr;
	int		neg;

	i = 1;
	neg = 0;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value *= -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	if (!(nbr = (char *)malloc(sizeof(nbr) * i)))
		return (NULL);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		nbr[i + neg] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}

int		nbr_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)) || \
			(c >= 'a' && c <= ('a' + base - 10)));
}

int		ft_atoi_base(const char *str, int base)
{
	int		i;
	int		nbr;
	int		sign;

	i = 0;
	if (!str[0] || (base < 2 || base > 16))
		return (0);
	nbr = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' || \
			str[i] == ' ' || str[i] == '\r' || str[i] == '\f')
		i += 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] && nbr_inbase(str[i], base))
	{
		if (str[i] >= 'A' && 'F' >= str[i])
			nbr = (nbr * base) + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && 'f' >= str[i])
			nbr = (nbr * base) + (str[i] - 'a' + 10);
		else
			nbr = (nbr * base) + (str[i] - '0');
		i += 1;
	}
	return (nbr * sign);
}

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
	war->visu = file.visu;
	war->visual.pause = -1;

	war->i_ocp = 0;
	war->cycles = 0;
	war->back_pc = 0;
	war->id_chariot = file.nb_player;
	war->nb_player = file.nb_player;
	//printf("nbplayer = %d\n", file.nb_player);
	war->nb_chariot = war->nb_player;
	war->dump = file.dump;
	war->jump = 2;
	war->lastlive = file.nb_player;
	war->nb_lives = 0; //new
	war->next_check = CYCLE_TO_DIE;
	war->cycle_to_die = CYCLE_TO_DIE;
	war->check_cycles_to_die = 1; //new
	ft_init_op_cycle(war);
}

void        print_verbose_16(t_war *war, t_chariot *chariot, int size)
{
	int i;

	if (war->verbose[0] == 1)
	{
		i = 0;
		war->status[chariot->player - 1] = calc_addr(chariot->pc + chariot->start_pos);
		printf("ADV %d (0x%04x -> %#06x) ", size, war->status[chariot->player - 1], war->status[chariot->player - 1] + size);
		while (i < size)
		{
			printf("%02x", (unsigned char)war->arena[calc_addr(chariot->start_pos + chariot->pc + i)]);
			i++;
			if (i != size)
				printf(" ");
		}
		printf("\n");
	}
}

int					read_arena(t_war *war, int cell)
{
	int	n;

	n = 0;
	cell = (cell % MEM_SIZE);
	if (cell < 0)
		cell += MEM_SIZE;
	n += war->arena[(cell % MEM_SIZE)] << 24;
	printf("n 1 = %d\n", n);
	n += war->arena[((cell + 1) % MEM_SIZE)] << 16;
	printf("n 2 = %d\n", n);
	n += war->arena[((cell + 2) % MEM_SIZE)] << 8;
	printf("n 3 = %d\n", n);
	n += war->arena[((cell + 3) % MEM_SIZE)];
	printf("n 4 = %d\n", n);
	return (n);
}

void		write_on_arena(t_war *war, int value, int start, int size)
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
