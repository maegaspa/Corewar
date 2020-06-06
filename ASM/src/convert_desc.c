/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_desc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:33 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:29 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include <stdio.h>

void		write_dir_int_lab(int n, t_file *file, t_tab *tab, int actual_inst)
{
	int				i;
	unsigned int	val;

	i = -1;
	while (++i < tab->nb_instruction)
	{
		if (tab->label_name[i])
		{
			if (tab->info_ins[actual_inst].param[n].direct_str &&
					ft_strcmp(tab->label_name[i],
						tab->info_ins[actual_inst].param[n].direct_str) == 0)
			{
				val = tab->n_label[i] - tab->dir_pos[actual_inst];
				if (tab->n_label[i] <= tab->dir_pos[actual_inst])
					val = 4294967296 -
						(tab->dir_pos[actual_inst] - tab->n_label[i]);
				write_binary_int(val, file->fd);
			}
		}
	}
}

int			write_dir_int(int n, t_file *file, t_tab *tab, int actual_inst)
{
	unsigned int	val;

	val = ft_atoi_bis(tab->info_ins[actual_inst].parameter[n]);
	if (ft_strstr(tab->info_ins[actual_inst].parameter[n], file->tmp))
		write_dir_int_lab(n, file, tab, actual_inst);
	else
	{
		if (n == 0)
			write_binary_int(val, file->fd);
		if (n == 1)
			write_binary_int(val, file->fd);
		if (n == 2)
			write_binary_int(val, file->fd);
	}
	return (SUCCESS);
}

void		write_dir_short_lab(int n, t_file *file, t_tab *tab, int act_inst)
{
	int				i;
	unsigned short	val;

	i = -1;
	while (++i < tab->nb_instruction)
	{
		if (tab->label_name[i] && ft_strlen(tab->label_name[i]) > 0)
		{
			if (tab->info_ins[act_inst].param[n].indirect_str && ft_strcmp(
	tab->label_name[i], tab->info_ins[act_inst].param[n].indirect_str) == 0)
			{
				val = tab->r_pos[i] - tab->dir_pos[act_inst];
				swap_2(&val);
				write(file->fd, &val, IND_SIZE);
			}
			else if (tab->info_ins[act_inst].param[n].direct_str &&
					ft_strcmp(tab->label_name[i],
						tab->info_ins[act_inst].param[n].direct_str) == 0)
			{
				val = tab->r_pos[i] - tab->dir_pos[act_inst];
				swap_2(&val);
				write(file->fd, &val, IND_SIZE);
			}
		}
	}
}

int			write_short(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	unsigned short val;

	val = (short)ft_atoi_bis(tab->info_ins[actual_inst].parameter[n_param]);
	swap_2(&val);
	if (ft_strstr(tab->info_ins[actual_inst].parameter[n_param], file->tmp))
		write_dir_short_lab(n_param, file, tab, actual_inst);
	else
	{
		if (n_param == 0)
			write(file->fd, &val, IND_SIZE);
		if (n_param == 1)
			write(file->fd, &val, IND_SIZE);
		if (n_param == 2)
			write(file->fd, &val, IND_SIZE);
	}
	return (SUCCESS);
}

int			write_reg_dir_ind(t_file *file, t_tab *tab, int i)
{
	int n;

	n = -1;
	while (++n < tab->info_ins[i].nb_parameter)
	{
		utils_reg_dir_ind(file, tab, i, n);
		if (tab->info_ins[i].param[n].type_param == T_IND)
			write_short(n, file, tab, i);
	}
	return (SUCCESS);
}
