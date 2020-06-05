/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bytes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:57 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:31 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	param_fill_dir(t_tab *tab, t_file *file)
{
	if (tab->info_ins[file->i].param[file->n_param].type_param == T_DIR)
	{
		if (which_direct(tab, file->i) == 1)
		{
			tab->tabyte[file->j] = -2;
			tab->tabyte[file->j + 1] = -2;
			if (ft_strstr(tab->info_ins[file->i].parameter[file->n_param],
						file->tmp))
			{
				tab->tabyte[file->j] = 5;
				tab->tabyte[file->j + 1] = 5;
			}
			file->j += 2;
		}
		else
			param_fill_dir2(tab, file);
	}
}

void	param_fill(t_tab *tab, t_file *file)
{
	while (++file->n_param < tab->info_ins[file->i].nb_parameter)
	{
		if (tab->info_ins[file->i].param[file->n_param].type_param == T_REG)
			tab->tabyte[file->j++] = -1;
		param_fill_dir(tab, file);
		if (tab->info_ins[file->i].param[file->n_param].type_param == T_IND)
		{
			tab->tabyte[file->j] = -2;
			tab->tabyte[file->j + 1] = -2;
			file->j += 2;
		}
	}
}

void	get_label_pos2(t_tab *tab, t_file *file)
{
	if (!tab->info_ins[file->i].label)
	{
		if (tab->tabyte[file->j] != -5)
			tab->n_label[file->k] = file->j;
	}
	else
	{
		tab->label_name[file->k] = ft_strcpy(tab->label_name[file->k],
				tab->info_ins[file->i].label);
		file->k++;
	}
}

int		get_label_pos(t_tab *tab, t_file *file)
{
	file->i = -1;
	file->j = 0;
	file->k = 1;
	if ((file->error = get_label_init(tab)) < 1)
		return (file->error);
	while (++file->i < tab->nb_instruction)
	{
		if (file->j > CHAMP_MAX_SIZE)
			return (TOO_BIG);
		file->n_param = -1;
		if (tab->info_ins[file->i].id_inst > 0)
			tab->tabyte[file->j++] = tab->info_ins[file->i].id_inst;
		if (tab->info_ins[file->i].id_inst > 0)
			if (file->op[tab->info_ins[file->i].id_inst - 1].acb)
				tab->tabyte[file->j++] = -3;
		param_fill(tab, file);
		get_label_pos2(tab, file);
	}
	tab->tabyte[file->j] = -5;
	tab->n_label[file->k] = file->j - 1;
	file->max_byte = file->j - 1;
	return (SUCCESS);
}
