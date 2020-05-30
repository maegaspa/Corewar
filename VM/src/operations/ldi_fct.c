/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:25 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/26 19:38:32 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			ldi_fct(t_war *war, t_chariot *chariot)
{
	verbose(war, chariot);
	if (war->rtype[0] == REG_CODE && war->rtype[1] == REG_CODE)
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + ((chariot->registres[war->param[0]- 1] + chariot->registres[war->param[1] - 1]) % IDX_MOD)));
	else if (war->rtype[0] == IND_CODE)
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + war->param[0] % IDX_MOD)) + war->param[1] % IDX_MOD;
	else if (war->rtype[0] == IND_CODE && war->rtype[1] == REG_CODE)
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + war->param[0] % IDX_MOD)) + chariot->registres[war->param[1] - 1] % IDX_MOD;
	else if (war->rtype[0] != REG_CODE && war->rtype[1] == REG_CODE)
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + ((war->param[0] + chariot->registres[war->param[1] - 1]) % IDX_MOD)));
	else if (war->rtype[0] == REG_CODE && war->rtype[1] != REG_CODE)
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + ((chariot->registres[war->param[0]- 1] + war->param[1]) % IDX_MOD)));
	else
		chariot->registres[war->param[2] - 1] = ft_load(war, 4, calc_addr(chariot->pc + chariot->start_pos + ((war->param[0] + war->param[1]) % IDX_MOD)));
	return (0);
}
