/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:23 by seanseau          #+#    #+#             */
/*   Updated: 2020/04/03 19:57:55 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		get_4_val(t_war *war, t_chariot *chariot, int i)
{
	unsigned char	valx[5];
    char			*str;
    char			*str2;
    char			*str3;
    char			*str4;
    char			*strr;
    int				rval;

    valx[0] = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i];
    valx[1] = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i + 1];
    valx[2] = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i + 2];
    valx[3] = (unsigned char)war->arena[chariot->start_pos + chariot->pc + i + 3];
    valx[4] = '\0';
   	str = ft_itoa_base(valx[0], 16);
   	str2 = ft_itoa_base(valx[1], 16);
   	str3 = ft_itoa_base(valx[2], 16);
   	str4 = ft_itoa_base(valx[3], 16);
   	if (valx[1] < 10)
   	{
   		str2[1] = str2[0];
   		str2[0] = '0';
   		str2[2] = '\0';
   	}
   	if (valx[2] < 10)
    {
   		str3[1] = str3[0];
      	str3[0] = '0';
      	str3[2] = '\0';
    }
    if (valx[3] < 10)
    {
        str4[1] = str4[0];
        str4[0] = '0';
        str4[2] = '\0';
    }
	 if (!(strr = (char *)malloc(sizeof(int) * ft_strlen(str) +
		ft_strlen(str2) + ft_strlen(str3) + ft_strlen(str4) + 1)))
    	return (ERROR_MALLOC);
   	ft_strcpy(strr, str);
   	ft_strcat(strr, str2);
   	ft_strcat(strr, str3);
   	ft_strcat(strr, str4);
//   	printf("strr = %s\n", strr);
   	rval = ft_atoi_base(strr, 16);
//	printf("rval = %d\n", rval);
   	ft_strdel(&strr);
   	return (rval);
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
	if (war->rtype[0] == T_DIR)
	{
		param1 = get_4_val(war, chariot, i);
        if (war->verbose[2] == 1)
            printf("P %4d | ld %d r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[chariot->start_pos + chariot->pc + 6]);
        print_verbose_16(war, chariot, 7);
		r = war->arena[chariot->start_pos + chariot->pc + i + 4];
		//printf("param1 = %d et param2 = %d\n", param1, r);
		chariot->registres[r - 1] = param1;
	}
	if (war->rtype[0] == T_IND)
	{
		param1 = get_2_val(war, chariot, i);
        if (war->verbose[2] == 1)
            printf("P %4d | ld %d r%d\n", (chariot->index + 1), param1, (unsigned char)war->arena[chariot->start_pos + chariot->pc + 4]);
		print_verbose_16(war, chariot, 5);
        param1 = (param1 % IDX_MOD);
		param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1) % MEM_SIZE] << 24;
		param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 1) % MEM_SIZE] << 16;
		param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 2) % MEM_SIZE] << 8;
		param2 += war->arena[(chariot->start_pos + chariot->pc + i + param1 + 3) % MEM_SIZE];
		r = war->arena[chariot->start_pos + chariot->pc + i + 2];
		//printf("param1 = %d et param2 = %d et r = %d\n", param1, param2, r);
		chariot->registres[r - 1] = param1;
	}
	if (param1 == 0)
    	chariot->carry = 1;
    else
        chariot->carry = 0;
	//printf("LD_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, chariot->pc);
	return (0);
}
