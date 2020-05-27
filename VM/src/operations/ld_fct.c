/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:23 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/27 01:05:20 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int   get_4_val(t_war *war, t_chariot *chariot, int i)
{
  unsigned int  res;
  int       tmp;

  res = 0;
  tmp = i;
  while (i < tmp + 4)
  {
    res = res << 8;
    res = res + (unsigned char)war->arena[chariot->start_pos + chariot->pc + i];
    i++;
  }
  return (res);
}

int			ld_fct(t_war *war, t_chariot *chariot)
{
	int i;
	int param1;
	int param2;
	int r;

	i = 2;
	param2 = 0;
	get_bin_ocp(chariot, war);
	if (war->rtype[0] == DIR_CODE)
	{
		param1 = get_4_val(war, chariot, i);
        if (war->verbose[2] == 1)
            printf("P %4d | ld %d r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[chariot->start_pos + chariot->pc + 6]);
        print_verbose_16(war, chariot, 7);
		r = war->arena[chariot->start_pos + chariot->pc + i + 4];
		chariot->registres[(unsigned char)r - 1] = param1;
	}
	if (war->rtype[0] == IND_CODE)
	{
		param1 = get_2_val(war, chariot, i);
        if (war->verbose[2] == 1)
            printf("P %4d | ld %hd r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[chariot->start_pos + chariot->pc + 4]);
		print_verbose_16(war, chariot, 5);
		param2 = read_arena(war, param1);
		r = war->arena[chariot->start_pos + chariot->pc + i + 2];
		chariot->registres[(unsigned char)r - 1] = param2;
	}
	if (param1 == 0)
    	chariot->carry = 1;
    else
        chariot->carry = 0;
//	printf("LD_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
