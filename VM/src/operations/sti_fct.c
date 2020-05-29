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
	int 			tmp;

	res = 0;
	tmp = i;
	while (i < tmp + 2)
	{
		res = res << 8;
		res = res + (unsigned char)war->arena[calc_addr(chariot->addr + i)];
		i++;
	}
	return (res);
}

int			sti_fct(t_war *war, t_chariot *chariot)
{
	int 			i;
	int				param2;
	int				param3;
	int				cell;
	int				r;
	int 			check;

	i = 3;
	check = 0;
	get_bin_ocp(chariot, war);
	r = war->arena[calc_addr(chariot->addr + 2)];
//	printf("COUCOU C ALAAAAAAAAAAA war->1 = %d et war->2 = %d\n", war->rtype[1],  war->rtype[2]);
	if ((war->rtype[1] == DIR_CODE || war->rtype[1] == IND_CODE) && war->rtype[2] == DIR_CODE)
	{
		check = 1;
		param2 = get_2_val(war, chariot, i);
		param3 = get_2_val(war, chariot, i + 2);
		cell = ((param2 + param3) % IDX_MOD);
		if (war->verbose[2] == 1 && r > 0 && r <= 16)
		{
			printf("P %4d | sti r%d %hd %hd\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], param2, param3);
			printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, calc_addr(chariot->addr + cell));
		}
		if (r > 16 || r <= 0)
		{
			print_verbose_16(war, chariot, 7);
			return(FAILURE);
		}
		else
			print_verbose_16(war, chariot, 7);
	}
	else if ((war->rtype[1] == IND_CODE || war->rtype[1] == DIR_CODE) && war->rtype[2] == REG_CODE)
	{
		check = 1;
		param2 = get_2_val(war, chariot, i);
		if (war->rtype[1] == IND_CODE)
			param2 = read_arena(war, param2);
		param3 = war->arena[calc_addr(chariot->addr + i + 2)];
		cell = ((param2 + param3) % IDX_MOD);
		if (war->verbose[2] == 1 && r > 0 && r <= 16)
		{
			printf("P %4d | sti r%d %d %d\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], param2, param3);
			printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, calc_addr(chariot->addr + cell));
		}
		if (r > 16 || r <= 0)
        {
        	print_verbose_16(war, chariot, 6);
        	return (FAILURE);
        }
		else
			print_verbose_16(war, chariot, 6);
	}
	else if (war->rtype[1] == REG_CODE && war->rtype[2] == REG_CODE)
	{
		check = 1;
		param2 = war->arena[calc_addr(chariot->addr + i)];
		param3 = war->arena[calc_addr(chariot->addr + i + 1)];
		cell = ((param2 + param3) % IDX_MOD);
		if (war->verbose[2] == 1 && r > 0 && r <= 16)
		{
			printf("P %4d | sti r%d %d %d\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], param2, param3);
			printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, calc_addr(chariot->addr + cell));
		}
		if (r > 16 || r <= 0)
        {
        	print_verbose_16(war, chariot, 5);
        	return (FAILURE);
        }
        else
			print_verbose_16(war, chariot, 5);
	}
	else if (war->rtype[1] == REG_CODE && war->rtype[2] == DIR_CODE)
	{
		check = 1;
		param2 = war->arena[calc_addr(chariot->addr + i)];
		param3 = get_2_val(war, chariot, i + 1);
		cell = ((param2 + param3) % IDX_MOD);
		if (war->verbose[2] == 1 && r > 0 && r <= 16)
		{
			printf("P %4d | sti r%d %d %d\n", (chariot->index + 1), (unsigned char)war->arena[calc_addr(chariot->addr + 2)], param2, param3);
			printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, calc_addr(chariot->addr + cell));
		}
		if (r > 16 || r <= 0)
        {
        	print_verbose_16(war, chariot, 6);
        	return (FAILURE);
        }
        else
			print_verbose_16(war, chariot, 6);
	}
	if (r > 0 && r <= 16 && check == 1)
		write_on_arena(war, chariot->registres[(unsigned char)war->arena[calc_addr(chariot->addr + 2)] - 1], calc_addr(chariot->addr + cell), REG_SIZE);
	//    printf("STI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
