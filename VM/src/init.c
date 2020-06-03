/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:51:56 by hmichel           #+#    #+#             */
/*   Updated: 2020/06/03 16:51:58 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				init_usage(t_parse_file *file)
{
	int i;

	i = -1;
	file->i = 0;
	file->dump = -1;
	file->long_dump = -1;
	file->n = 0;
	file->visu = 0;
	file->nb_player = 0;
	file->rk_player = 1;
	file->cycles = -1;
	file->sv = -1;
	file->a = -1;
	while (++i < 6)
		file->verbose[i] = 0;
	file->verbose[5] = 1;
	i = -1;
	while (++i < MAX_PLAYERS)
		file->rank_player[i] = 0;
	if (!(file->file_name = malloc(sizeof(char*) * MAX_PLAYERS + 1)))
		return (ERROR_MALLOC);
	return (SUCCESS);
}

void			ft_init_op_cycle(t_war *war)
{
	war->op_cycle[0] = 10;
	war->op_cycle[1] = 5;
	war->op_cycle[2] = 5;
	war->op_cycle[3] = 10;
	war->op_cycle[4] = 10;
	war->op_cycle[5] = 6;
	war->op_cycle[6] = 6;
	war->op_cycle[7] = 6;
	war->op_cycle[8] = 20;
	war->op_cycle[9] = 25;
	war->op_cycle[10] = 25;
	war->op_cycle[11] = 800;
	war->op_cycle[12] = 10;
	war->op_cycle[13] = 50;
	war->op_cycle[14] = 1000;
	war->op_cycle[15] = 2;
}

void			init_tab(t_opp *opp_tab)
{
	ft_bzero(opp_tab, 16);
	opp_tab[0] = &live_fct;
	opp_tab[1] = &ld_fct;
	opp_tab[2] = &st_fct;
	opp_tab[3] = &add_fct;
	opp_tab[4] = &sub_fct;
	opp_tab[5] = &and_fct;
	opp_tab[6] = &or_fct;
	opp_tab[7] = &xor_fct;
	opp_tab[8] = &zjmp_fct;
	opp_tab[9] = &ldi_fct;
	opp_tab[10] = &sti_fct;
	opp_tab[11] = &fork_fct;
	opp_tab[12] = &lld_fct;
	opp_tab[13] = &lldi_fct;
	opp_tab[14] = &lfork_fct;
	opp_tab[15] = &aff_fct;
}

void			ft_init_war(t_parse_file file, t_war *war)
{
	int		i;

	i = -1;
	while (++i < 6)
		war->verbose[i] = file.verbose[i];
	war->aff = file.a;
	war->i_ocp = 0;
	war->cycles = 0;
	war->back_pc = 0;
	war->visu = file.visu;
	war->visual.pause = -1;
	war->cycles_btw_check = 0;
	war->id_chariot = file.nb_player;
	war->nb_player = file.nb_player;
	war->nb_chariot = war->nb_player;
	war->dump = file.dump;
	war->jump = 2;
	war->lastlive = file.nb_player;
	war->nb_lives = 0;
	war->next_check = CYCLE_TO_DIE;
	war->cycle_to_die = CYCLE_TO_DIE;
	war->check_cycles_to_die = 1;
	ft_init_op_cycle(war);
}
