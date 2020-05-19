/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/04/03 19:56:28 by maegaspa         ###   ########lyon.fr   */
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

	i = 3;
//	printf("nb param pour sti chariot [%d]\n", g_op_tab[chariot->ope - 1].nb_params);
	printf("nbplayer = %d\n", war->nb_player);
	get_bin_ocp(chariot, war);
	if (war->rtype[1] == 2 && war->rtype[2] == T_DIR)
	{
		param2 = get_2_val(war, chariot, i);
		param3 = get_2_val(war, chariot, i + 2);
		cell = ((param2 + param3) % IDX_MOD);
	}
	if (war->rtype[1] == 2 && war->rtype[2] == T_REG)
    {
    	param2 = get_2_val(war, chariot, i);
    	param3 = war->arena[chariot->start_pos + chariot->pc + i + 2];
    	cell = ((param2 + param3) % IDX_MOD);
    }
	if (war->rtype[1] == T_REG && war->rtype[2] == T_REG)
    {
    	param2 = war->arena[chariot->start_pos + chariot->pc + i];
        param3 = war->arena[chariot->start_pos + chariot->pc + i + 1];
        cell = ((param2 + param3) % IDX_MOD);
    }
		printf("cell = %d\n", cell);
//		printf("r0 = %d et r1 = %d\n", chariot->registres[0], chariot->registres[1]);
//utiliser la verbose pour savoir sur quoi on tombe
//	if (war->arena[chariot->start_pos + chariot->pc + cell] == T_DIR_FOUR)
//		war->arena[chariot->start_pos + chariot->pc + cell + 3] = war->nb_player;
//	if (war->arena[chariot->start_pos + chariot->pc + cell] == T_DIR_TWO
//		|| war->arena[chariot->start_pos + chariot->pc + cell] == T_IND)
//       	war->arena[chariot->start_pos + chariot->pc + cell + 1] = war->nb_player;
//    if (war->arena[chariot->start_pos + chariot->pc + cell] == T_REG)
//       war->arena[chariot->start_pos + chariot->pc + cell] = war->nb_player;
//		printf("ici l'arene = %x et nb_player = %d\n", (unsigned char)war->arena[chariot->start_pos + chariot->pc + cell], war->nb_player);
	printf("STI_FCT : index_chariot : %d\tto_die : %d et pc = [%d]\n", chariot->index, war->to_die, (chariot->start_pos + chariot->pc));
	return (0);
}
