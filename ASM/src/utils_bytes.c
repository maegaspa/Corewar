/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:57 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:31 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	stock_reg_dir(t_tab *tab, t_file *file, int n_param, int actual_inst)
{
	if (tab->info_ins[actual_inst].param[n_param].type_param == T_REG)
	{
		if (n_param == 0)
			file->op_c += 64;
		if (n_param == 1)
			file->op_c += (64 >> 2);
		if (n_param == 2)
			file->op_c += (64 >> 4);
	}
	if (tab->info_ins[actual_inst].param[n_param].type_param == T_DIR)
	{
		if (n_param == 0)
			file->op_c += 128;
		if (n_param == 1)
			file->op_c += (128 >> 2);
		if (n_param == 2)
			file->op_c += (128 >> 4);
	}
}

int		write_param(t_file *file, t_tab *tab, int actual_inst)
{
	int	n_param;

	n_param = -1;
	while (++n_param < tab->info_ins[actual_inst].nb_parameter)
	{
		stock_reg_dir(tab, file, n_param, actual_inst);
		if (tab->info_ins[actual_inst].param[n_param].type_param == T_IND)
		{
			if (n_param == 0)
				file->op_c += 192;
			if (n_param == 1)
				file->op_c += (192 >> 2);
			if (n_param == 2)
				file->op_c += (192 >> 4);
		}
	}
	if (tab->info_ins[actual_inst].id_inst > 0)
		if (file->op[tab->info_ins[actual_inst].id_inst - 1].acb)
			write(file->fd, &(file->op_c),
				file->op[tab->info_ins[actual_inst].id_inst - 1].acb);
	return (SUCCESS);
}
