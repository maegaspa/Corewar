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

int		get_2_val(t_war *war, t_chariot *chariot, int i)
{
	unsigned char	valx[3];
    char			*str;
    char			*str2;
    char			*str3;
    int				rval;

    valx[0] = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i];
    valx[1] = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i + 1];
    valx[2] = '\0';
   	str = ft_itoa_base(valx[0], 16);
   	str2 = ft_itoa_base(valx[1], 16);
   	if (valx[1] < 10)
    {
		str2[1] = str2[0];
       	str2[0] = '0';
       	str2[2] = '\0';
    }
	if (!(str3 = (char *)malloc(sizeof(int) * ft_strlen(str) + ft_strlen(str2) + 1)))
    	return (ERROR_MALLOC);
   	ft_strcpy(str3, str);
   	ft_strcat(str3, str2);
   	rval = ft_atoi_base(str3, 16);
   	ft_strdel(&str3);
   	return (rval);
}

int			sti_fct(t_war *war, t_chariot *chariot)
{
	int 			i;
	int				param2;
	int				param3;
	int				cell;
	int				pos;

	i = 3;
	get_bin_ocp(chariot, war);
	/*int k = -1;
	while (++k < 3)
		printf("[sti] war->rtype[%d] = %d\n", k, war->rtype[k]);*/
	pos = chariot->start_pos + chariot->pc;
	printf("chariot->registres[0] = %d\n", chariot->registres[0]);
	//hariot->registres[(pos + 1) - 1] = 42000;
	if ((war->rtype[1] == DIR_CODE && war->rtype[2] == DIR_CODE) || (war->rtype[1] == DIR_CODE && war->rtype[2] == DIR_CODE))
	{
    	param2 = get_2_val(war, chariot, i);
		  param3 = get_2_val(war, chariot, i + 2);
      cell = ((param2 + param3) % IDX_MOD);
    	if (war->verbose[2] == 1)
      {
          ft_printf("P %4d | sti r%d %d %d\n", (chariot->pc + 1), (unsigned char)war->arena[pos + 2], param2, param3);
          ft_printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, (chariot->pc + cell));
      }
    	print_verbose_16(war, chariot, 8);
	}
	else if (war->rtype[1] == IND_CODE && war->rtype[2] == REG_CODE)
    {
    	param2 = get_2_val(war, chariot, i);
    	param3 = war->arena[pos + i + 2];
      cell = ((param2 + param3) % IDX_MOD);
   		if (war->verbose[2] == 1)
     	{
    		ft_printf("P %4d | sti r%d %d %d\n", (chariot->pc + 1), (unsigned char)war->arena[pos + 2], param2, param3);
       		ft_printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, (chariot->pc + cell));
     	}
    	print_verbose_16(war, chariot, 7);
    }
	else if (war->rtype[1] == REG_CODE && war->rtype[2] == REG_CODE)
    {
    	param2 = war->arena[pos + i];
    	param3 = war->arena[pos + i + 1];
      cell = ((param2 + param3) % IDX_MOD);
      if (war->verbose[2] == 1)
      {
        	ft_printf("P %4d | sti r%d %d %d\n", (chariot->pc + 1), (unsigned char)war->arena[pos + 2], param2, param3);
          ft_printf("       | -> store to  %d + %d = %d (with pc and mod %d)\n", param2, param3, param2 + param3, (chariot->pc + cell));
      }
    	print_verbose_16(war, chariot, 6);
    }
    write_on_arena(war, chariot->registres[(unsigned char)war->arena[pos - 1]], pos + cell, REG_SIZE);
//    printf("STI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->start_pos + chariot->pc);
	return (0);
}
