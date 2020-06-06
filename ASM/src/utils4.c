/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:56 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:33 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		delete_hash(t_file *file)
{
	int i;
	int j;

	i = -1;
	while (file->file[++i])
	{
		j = -1;
		while (file->file[i][++j])
		{
			if (file->file[i][j] == COMMENT_CHAR)
			{
				file->file[i][j] = '\0';
				while (file->file[i][++j])
				{
					file->file[i][j] = '\0';
				}
				break ;
			}
		}
	}
}

void		utils_reg_dir_ind(t_file *file, t_tab *tab, int i, int n)
{
	if (tab->info_ins[i].param[n].type_param == T_REG)
	{
		if (n == 0)
			write(file->fd, &(tab->info_ins[i].param[n].reg), REG_SIZE);
		if (n == 1)
			write(file->fd, &(tab->info_ins[i].param[n].reg), REG_SIZE);
		if (n == 2)
			write(file->fd, &(tab->info_ins[i].param[n].reg), REG_SIZE);
	}
	if (tab->info_ins[i].param[n].type_param == T_DIR)
	{
		if (which_direct(tab, i) == 1)
			write_short(n, file, tab, i);
		else
			write_dir_int(n, file, tab, i);
	}
}

void		get_label_pos_bis(t_tab *tab, t_file *file)
{
	file->n_param = -1;
	if (tab->info_ins[file->i].id_inst > 0)
	{
		tab->tabyte[file->j++] = tab->info_ins[file->i].id_inst;
		if (tab->info_ins[file->i].label)
			tab->r_pos[file->k] = file->j - 1;
	}
	if (tab->info_ins[file->i].id_inst > 0)
		if (file->op[tab->info_ins[file->i].id_inst - 1].acb)
			tab->tabyte[file->j++] = -3;
	param_fill(tab, file);
	get_label_pos2(tab, file);
}
