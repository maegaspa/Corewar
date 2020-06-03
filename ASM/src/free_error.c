/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:56 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:33 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_error(t_tab *tab, t_file *file)
{
	int		i;

	i = -1;
	free_error_2(file, i);
	if (tab->nb_instruction && tab->no_prob == 1)
	{
		i = -1;
		while (++i < tab->nb_instruction)
		{
			if (tab->label_name[i])
				ft_strdel(&tab->label_name[i]);
			if (tab->info_ins[i].instruction)
				ft_strdel(&tab->info_ins[i].instruction);
			free_error_3(tab, i);
			free(tab->info_ins[i].parameter);
			if (tab->info_ins[i].param)
				free(tab->info_ins[i].param);
		}
		free_error_4(tab);
	}
}

void	free_error_2(t_file *file, int i)
{
	if (file->file_name)
		ft_strdel(&file->file_name);
	if (file->file)
	{
		while (file->file[++i])
			ft_strdel(&file->file[i]);
		free(file->file);
	}
}

void	free_error_3(t_tab *tab, int i)
{
	int j;

	j = -1;
	while (++j < tab->info_ins[i].nb_parameter)
	{
		if (tab->info_ins[i].param[j].direct_str != NULL)
		{
			ft_strdel(&tab->info_ins[i].param[j].direct_str);
			break ;
		}
		if (tab->info_ins[i].param[j].indirect_str != NULL)
		{
			ft_strdel(&tab->info_ins[i].param[j].indirect_str);
			break ;
		}
		if (tab->info_ins[i].instruction &&
				(tab->info_ins[i].param[j].type_param != T_REG
				&& tab->info_ins[i].param[j].type_param != T_IND
				&& tab->info_ins[i].param[j].type_param != T_DIR))
			break ;
	}
	while (++j < tab->info_ins[i].nb_parameter)
		ft_strdel(&tab->info_ins[i].parameter[j]);
}

void	free_error_4(t_tab *tab)
{
	if (tab->info_ins)
		free(tab->info_ins);
	if (tab->label_name)
		free(tab->label_name);
	if (tab->n_label)
		free(tab->n_label);
	if (tab->dir_pos)
		free(tab->dir_pos);
	if (tab->r_pos)
		free(tab->r_pos);
}

void	free_split(t_file *file)
{
	int	i;

	i = -1;
	while (++i <= file->free_cnt)
		free(file->split[i]);
	free(file->split);
}
