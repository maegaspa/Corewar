/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 16:06:28 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

short		get_2_val(t_war *war, t_chariot *chariot, int i)
{
	unsigned short	res;
	int				tmp;

	res = 0;
	tmp = i;
	while (i < tmp + 2)
	{
		res = res << 8;
		res = res + (unsigned char)war->arena[calc_addr(C_POS + i)];
		i++;
	}
	return (res);
}

void		sti_verbose(t_war *war, t_chariot *chariot, int p1, int p2)
{
	int	res;

	res = p1 + p2;
	if (war->verbose[2] == 1)
	{
		printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", p1,
			p2, res, (C_POS + res % IDX_MOD) % MEM_SIZE);
	}
}

int			sti_fct_norm_2(t_war *war, t_chariot *chariot)
{
	if (war->rtype[1] == IND_CODE && war->rtype[2] == REG_CODE)
	{
		sti_verbose(war, chariot, ft_load(war, 4,
			calc_addr(C_POS + war->param[1] % IDX_MOD)),
			chariot->registres[war->param[2] - 1]);
		write_on_arena(war, chariot->registres[war->param[0] - 1],
			calc_addr(C_POS + ft_load(war, 4,
			calc_addr(C_POS + war->param[1] % IDX_MOD)) +
			chariot->registres[war->param[2] - 1]) % IDX_MOD, 4);
		return (1);
	}
	else if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE
		&& war->rtype[2] != REG_CODE)
	{
		sti_verbose(war, chariot, chariot->registres[war->param[1] - 1],
			war->param[2]);
		write_on_arena(war, chariot->registres[war->param[0] - 1],
			calc_addr(C_POS + ((chariot->registres[war->param[1] - 1] +
			war->param[2]) % IDX_MOD)), 4);
		return (1);
	}
	return (0);
}

int			sti_fct_norm_1(t_war *war, t_chariot *chariot)
{
	if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE
		&& war->rtype[2] == REG_CODE)
	{
		sti_verbose(war, chariot, chariot->registres[war->param[1] - 1],
			chariot->registres[war->param[2] - 1]);
		write_on_arena(war, chariot->registres[war->param[0] - 1],
			calc_addr(C_POS + ((chariot->registres[war->param[1] - 1] +
			chariot->registres[war->param[2] - 1]) % IDX_MOD)), 4);
		return (1);
	}
	else if (war->rtype[1] == IND_CODE && war->rtype[2] != REG_CODE)
	{
		sti_verbose(war, chariot, ft_load(war, 4,
			calc_addr(C_POS + war->param[1] % IDX_MOD)), (short)war->param[2]);
		write_on_arena(war, chariot->registres[war->param[0] - 1],
			calc_addr(C_POS + ft_load(war, 4,
			calc_addr(C_POS + war->param[1] % IDX_MOD)) +
			(short)war->param[2]) % IDX_MOD, 4);
		return (1);
	}
	return (0);
}

int			sti_fct(t_war *war, t_chariot *chariot)
{
	verbose(war, chariot);
	if (sti_fct_norm_1(war, chariot) == 1)
		return (0);
	else if (sti_fct_norm_2(war, chariot) == 1)
		return (0);
	else if (war->rtype[0] == REG_CODE && war->rtype[1] != REG_CODE
		&& war->rtype[2] == REG_CODE)
	{
		sti_verbose(war, chariot, war->param[1],
			chariot->registres[war->param[2] - 1]);
		write_on_arena(war, chariot->registres[war->param[0] - 1],
			calc_addr(C_POS + ((war->param[1] +
			chariot->registres[war->param[2] - 1]) % IDX_MOD)), 4);
	}
	else
	{
		sti_verbose(war, chariot, war->param[1], war->param[2]);
		write_on_arena(war, chariot->registres[war->param[0] - 1],
			calc_addr(C_POS + ((war->param[1] + war->param[2]) % IDX_MOD)), 4);
	}
	return (0);
}
