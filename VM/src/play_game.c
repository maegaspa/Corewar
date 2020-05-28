/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:32 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:19:50 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			is_conform2(char ocp, int param, int ope)
{
//	if (ocp == 0)
//		return (0);
	if (ocp == 1 && (0x01 & g_op_tab[ope].params_type[param]))
		return (REG_CODE);
	if (ocp == 2 && (0x02 & g_op_tab[ope].params_type[param]))
		return (DIR_CODE);
	if (ocp == 3 && (0x04 & g_op_tab[ope].params_type[param]))
		return (IND_CODE);
	return (0);
}

int		get_bin_ocp(t_chariot *chariot, t_war *war)
{
	unsigned char	ocp;
	int				i;

	i = -1;
	if (!(war->rtype = malloc(sizeof(int) * 3)))
    		return (ERROR_MALLOC);
	while (++i < 3)
		war->rtype[i] = -1;
	ocp = war->arena[chariot->start_pos + chariot->pc + 1];
    if (!(war->rtype[0] = is_conform2((ocp >> 6), 0, chariot->ope - 1)))
    	return (FAILURE);
    if (g_op_tab[chariot->ope - 1].nb_params >= 2)
    	if (!(war->rtype[1] = is_conform2(((ocp & 0x30) >> 4), 1, chariot->ope - 1)))
    		return (FAILURE);
    if (g_op_tab[chariot->ope - 1].nb_params == 3)
    	if (!(war->rtype[2] = is_conform2(((ocp & 0x0C) >> 2), 2, chariot->ope - 1)))
    		return (FAILURE);
    return (SUCCESS);
}

int		ft_game(t_war *war, t_parse_file *file)
{
	t_chariot		*chariot;
	int				error;
	t_opp			opp_tab[16];
	int 			i;

	init_tab(opp_tab);
	war->aff = file->a;
	i = -1;
	while (++i < 6)
		war->verbose[i] = file->verbose[i];
	if ((error = ft_start_chariot(war, &chariot)) <= 0)
		return (error);
	war->begin = chariot;
	chariot->pc = 0;
	war->back_pc = 0;
	ft_print_war(war);
	while (check_cycle(war, chariot))
	{
		if (war->cycles == file->cycles + 1)
		{
			i = -1;
			while (++i < 6)
				war->verbose[i] = 0;
		}
		while (chariot)
		{
			ft_exec_opp(chariot, war, opp_tab);
			chariot = chariot->next;
		}
		chariot = war->begin;
		if (war->verbose[3] == 1)
           	printf("It is now cycle [%d]\n", war->cycles);
        if (file->dump == war->cycles || file->long_dump == war->cycles)
			print_arena(war, file);
	}
	return (SUCCESS);
}

//int		ft_game_visu(t_war *war)
//{
//	t_chariot		*chariot;
//	int				error;
//	t_opp			opp_tab[16];
//
//	init_tab(opp_tab);
//	if (war->visu == 1)
//		visu_body(war);
//	if ((error = ft_start_chariot(war, &chariot)) <= 0)
//		return (error);
//	war->begin = chariot;
//	while (war->cycles < war->to_die)
//	{
//		while (chariot)
//		{
//			if (war->visual.pause == -1)
//				ft_exec_opp(chariot, war, opp_tab);
//			chariot = chariot->next;
//		}
//		chariot = war->begin;
//		if (update_visu(war) != -1)
//			war->cycles++;
//	}
//	return (SUCCESS);
//}
