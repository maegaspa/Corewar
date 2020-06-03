/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:00:44 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			ft_load(t_war *war, int size, int adress)
{
	int		param;

	param = 0;
	while (adress < 0)
		adress += MEM_SIZE;
	if (size == 1)
		param = war->arena[(adress) % MEM_SIZE];
	else if (size == 2)
	{
		param = ((unsigned char)war->arena[adress] << 8);
		param += ((unsigned char)war->arena[calc_addr(adress + 1)]);
	}
	else
	{
		param = ((unsigned char)war->arena[adress] << 24);
		param += ((unsigned char)war->arena[calc_addr(adress + 1)] << 16);
		param += ((unsigned char)war->arena[calc_addr(adress + 2)] << 8);
		param += ((unsigned char)war->arena[calc_addr(adress + 3)]);
	}
	return (param);
}

void		verbose_reg(t_war *war, t_chariot *chariot, int i)
{
	if (i == 0 && (chariot->ope == 3 || chariot->ope == 4 || chariot->ope == 5
		|| chariot->ope == 11 || chariot->ope == 16))
		printf("r%d", war->param[i]);
	else if (i == 1 && (chariot->ope == 2 || chariot->ope == 4 ||
				chariot->ope == 5 || chariot->ope == 13))
		printf("r%d", war->param[i]);
	else if (i == 2 && (chariot->ope == 4 || chariot->ope == 5 ||
				chariot->ope == 6 || chariot->ope == 7 || chariot->ope == 8 ||
				chariot->ope == 10 || chariot->ope == 14))
		printf("r%d", war->param[i]);
	else if (i == 1 && (chariot->ope == 3))
		printf("%d", war->param[i]);
	else
		printf("%d", chariot->registres[war->param[i] - 1]);
}

void		verbose_ind(t_war *war, t_chariot *chariot, int i)
{
	if (chariot->ope == 2)
		printf("%d", ft_load(war, 4, calc_addr(C_POS +
			(war->param[0] % IDX_MOD))));
	else if ((chariot->ope == 13) || (chariot->ope == 14 && war->rtype[i] == 3)
		|| (chariot->ope == 11 && war->rtype[i] == 3)
		|| (chariot->ope == 10 && war->rtype[i] == 3))
		printf("%d", ft_load(war, 4,
			calc_addr(C_POS + war->param[i] % IDX_MOD)));
	else if (war->rtype[i] == 3 && chariot->ope >= 6 && chariot->ope <= 8)
		printf("%d", ft_load(war, 4,
			calc_addr(C_POS + war->param[i] % IDX_MOD)));
	else
		printf("%d", war->param[i]);
}

void		verbose_dir(t_war *war, t_chariot *chariot, int i)
{
	if (chariot->ope == 12)
		printf("%d (%d)", (short)war->param[i],
				calc_addr(chariot->pc + (war->param[i] % IDX_MOD)));
	else if (chariot->ope == 15)
		printf("%d (%d)", (short)war->param[i],
				calc_addr(chariot->pc + war->param[i]));
	else if (chariot->ope == 1 || chariot->ope == 2 || chariot->ope == 6 ||
			chariot->ope == 7 || chariot->ope == 8 || chariot->ope == 13)
		printf("%d", war->param[i]);
	else
		printf("%d", (short)war->param[i]);
}

void		verbose(t_war *war, t_chariot *chariot)
{
	int i;

	i = -1;
	if (war->verbose[2] == 1)
	{
		printf("P %4d | %s ", chariot->index + 1,
			g_op_tab[chariot->ope - 1].name);
		while (++i < g_op_tab[chariot->ope - 1].nb_params)
		{
			if (war->rtype[i] == REG_CODE)
				verbose_reg(war, chariot, i);
			else if (war->rtype[i] == DIR_CODE)
				verbose_dir(war, chariot, i);
			else if (war->rtype[i] == IND_CODE)
				verbose_ind(war, chariot, i);
			if (i + 1 != g_op_tab[chariot->ope - 1].nb_params)
				printf(" ");
		}
		printf("\n");
	}
}
