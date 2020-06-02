/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:35 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:37:55 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		lldi_verbose(t_war *war, t_chariot *chariot, int p1, int p2)
{
	int		res;

	res = p1 + p2;
	if (war->verbose[2] == 1)
	{
		printf("       | -> load from %d + %d = %d (with pc %d)\n", p1, p2, res,
			res + calc_addr(C_POS));
	}
	if (ft_load(war, 4, calc_addr(p1 + p2 + C_POS)) == 0)
		chariot->carry = 1;
	else
		chariot->carry = 0;
}

int			lldi_fct_norm_2(t_war *war, t_chariot *chariot)
{
	if (war->rtype[0] == IND_CODE && war->rtype[1] == REG_CODE)
	{
		lldi_verbose(war, chariot, ft_load(war, 4, calc_addr(C_POS +
			war->param[0] % IDX_MOD)), chariot->registres[war->param[1] - 1]);
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, (ft_load(war, 4,
			calc_addr(C_POS + war->param[0] % IDX_MOD)) +
			chariot->registres[war->param[1] - 1]) % IDX_MOD + C_POS);
		return (1);
	}
	else if (war->rtype[0] != REG_CODE && war->rtype[1] == REG_CODE)
	{
		lldi_verbose(war, chariot, war->param[0],
			chariot->registres[war->param[1] - 1]);
		chariot->registres[war->param[2] - 1] = ft_load(war, 4,
			calc_addr(C_POS + ((war->param[0] +
			chariot->registres[war->param[1] - 1]))));
		return (1);
	}
	return (0);
}

int			lldi_fct_norm_1(t_war *war, t_chariot *chariot)
{
	if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE)
	{
		lldi_verbose(war, chariot, chariot->registres[war->param[0] - 1],
			chariot->registres[war->param[1] - 1]);
		chariot->registres[war->param[2] - 1] = ft_load(war, 4,
			calc_addr(C_POS + ((chariot->registres[war->param[0] - 1] +
			chariot->registres[war->param[1] - 1]))));
		return (1);
	}
	else if (war->rtype[0] == IND_CODE && war->rtype[1] == DIR_CODE)
	{
		lldi_verbose(war, chariot, ft_load(war, 4, calc_addr(C_POS +
			war->param[0] % IDX_MOD)), war->param[1]);
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, (ft_load(war, 4,
			calc_addr(C_POS + war->param[0] % IDX_MOD)) +
			war->param[1]) % IDX_MOD + C_POS);
		return (1);
	}
	return (0);
}

int			lldi_fct(t_war *war, t_chariot *chariot)
{
	verbose(war, chariot);
	if (lldi_fct_norm_1(war, chariot) == 1)
		return (0);
	else if (lldi_fct_norm_2(war, chariot) == 1)
		return (0);
	else if (war->rtype[0] == REG_CODE && war->rtype[1] != REG_CODE)
	{
		lldi_verbose(war, chariot, chariot->registres[war->param[0] - 1],
			war->param[1]);
		chariot->registres[war->param[2] - 1] = ft_load(war, 4,
			calc_addr(C_POS + ((chariot->registres[war->param[0] - 1] +
			war->param[1]))));
	}
	else
	{
		lldi_verbose(war, chariot, war->param[0], war->param[1]);
		chariot->registres[war->param[2] - 1] = ft_load(war, 4,
			calc_addr(C_POS + ((war->param[0] + war->param[1]))));
	}
	return (0);
}
