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
    res = res + (unsigned char)war->arena[calc_addr(chariot->addr + i)];
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
	param1 = 0;
	r = -1;
	get_bin_ocp(chariot, war);
	if (war->rtype[0] == DIR_CODE)
	{
		r = war->arena[calc_addr(chariot->addr + i + 4)];
		param1 = get_4_val(war, chariot, i);
        if (war->verbose[2] == 1 && r > 0 && r <= 16)
            printf("P %4d | ld %d r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[calc_addr(chariot->addr + 6)]);
		if (r > 16 || r <= 0)
		{
			print_verbose_16(war, chariot, 7);
        	return(FAILURE);
		}
		else
			 print_verbose_16(war, chariot, 7);
		chariot->registres[(unsigned char)r - 1] = param1;
	}
	else if (war->rtype[0] == IND_CODE)
	{
		r = war->arena[calc_addr(chariot->addr + i + 2)];
		param1 = get_2_val(war, chariot, i);
        if (war->verbose[2] == 1 && r > 0 && r <= 16)
            printf("P %4d | ld %hd r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[calc_addr(chariot->addr + 4)]);
		if (r > 16 || r <= 0)
		{
			print_verbose_16(war, chariot, 5);
			return (FAILURE);
		}
		else
			print_verbose_16(war, chariot, 5);
		param2 = read_arena(war, param1);
		chariot->registres[(unsigned char)r - 1] = param2;
	}
	else
		print_verbose_16(war, chariot, 3);
	if (r != -1)
	{
		if (param1 == 0)
			chariot->carry = 1;
		else
			chariot->carry = 0;
	}
//	printf("LD_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
