/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:46 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:37:06 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void     verif_carry_xor(t_chariot *chariot, int p1, int p2)
{
//	printf("p1 = [%d] et p2 = [%d]\n", p1, p2);
	if ((p1 ^ p2) == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
//	printf("dans xor carry = %d\n", chariot->carry);
}

static int		xor_ind_bis(t_war *war, t_chariot *chariot)
{
	if (war->rtype[0] == IND_CODE && war->rtype[1] == REG_CODE)
	{
		REG_TAB[war->param[2] - 1] = ft_load(war, 4,
				calc_addr(chariot->pc + war->param[0])) ^
			REG_TAB[war->param[1] - 1];
		verif_carry_xor(chariot, ft_load(war, 4,
					calc_addr(chariot->pc + war->param[0])),
				REG_TAB[war->param[1] - 1]);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int		xor_ind(t_war *war, t_chariot *chariot)
{
	if (war->rtype[0] == IND_CODE && war->rtype[1] == DIR_CODE)
	{
		REG_TAB[war->param[2] - 1] =
			ft_load(war, 4, calc_addr(chariot->pc + war->param[0])) ^
			war->param[1];
		verif_carry_xor(chariot, ft_load(war, 4,
					calc_addr(chariot->pc + war->param[0])), war->param[1]);
		return (SUCCESS);
	}
	else if (war->rtype[0] == IND_CODE && war->rtype[1] == IND_CODE)
	{
		REG_TAB[war->param[2] - 1] =
			ft_load(war, 4, calc_addr(chariot->pc + war->param[0])) ^
			ft_load(war, 4, calc_addr(chariot->pc + war->param[1]));
		verif_carry_xor(chariot, ft_load(war, 4,
					calc_addr(chariot->pc + war->param[0])),
				ft_load(war, 4, calc_addr(chariot->pc + war->param[1])));
		return (SUCCESS);
	}
	else if (xor_ind_bis(war, chariot))
		return (SUCCESS);
	return (FAILURE);
}

static int		xor_reg(t_war *war, t_chariot *chariot)
{
	if (war->rtype[0] == REG_CODE && war->rtype[1] == IND_CODE)
	{
		REG_TAB[war->param[2] - 1] = REG_TAB[war->param[0] - 1] ^
			ft_load(war, 4, calc_addr(chariot->pc + war->param[1]));
		verif_carry_xor(chariot, REG_TAB[war->param[0] - 1],
				ft_load(war, 4, calc_addr(chariot->pc + war->param[1])));
		return (SUCCESS);
	}
	else if (war->rtype[0] == REG_CODE && war->rtype[1] == DIR_CODE)
	{
		REG_TAB[war->param[2] - 1] = REG_TAB[war->param[0] - 1] ^ war->param[1];
		verif_carry_xor(chariot, REG_TAB[war->param[0] - 1], war->param[1]);
		return (SUCCESS);
	}
	else if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE)
	{
		REG_TAB[war->param[2] - 1] = REG_TAB[war->param[0] - 1] ^
			REG_TAB[war->param[1] - 1];
		verif_carry_xor(chariot, REG_TAB[war->param[0] - 1],
				REG_TAB[war->param[1] - 1]);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int		xor_dir(t_war *war, t_chariot *chariot)
{
	if (war->rtype[0] == DIR_CODE && war->rtype[1] == IND_CODE)
	{
		REG_TAB[war->param[2] - 1] = war->param[0] ^
			ft_load(war, 4, calc_addr(chariot->pc + war->param[1]));
		verif_carry_xor(chariot, war->param[0],
				ft_load(war, 4, calc_addr(chariot->pc + war->param[1])));
		return (SUCCESS);
	}
	else if (war->rtype[0] == DIR_CODE && war->rtype[1] == REG_CODE)
	{
		REG_TAB[war->param[2] - 1] = war->param[0] ^ REG_TAB[war->param[1] - 1];
		verif_carry_xor(chariot, war->param[0], REG_TAB[war->param[1] - 1]);
		return (SUCCESS);
	}
	else if (war->rtype[0] == DIR_CODE && war->rtype[1] == DIR_CODE)
	{
		REG_TAB[war->param[2] - 1] = war->param[0] ^ war->param[1];
		verif_carry_xor(chariot, war->param[0], war->param[1]);
		return (SUCCESS);
	}
	return (FAILURE);
}

int			xor_fct(t_war *war, t_chariot *chariot)
{
	verbose(war, chariot);
	if (xor_dir(war, chariot))
		return (0);
	else if (xor_reg(war, chariot))
		return (0);
	else if (xor_ind(war, chariot))
		return (0);

//	printf("dans and le reg[2] = %d\n", REG_TAB[1]);
	return (0);
}
