/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:33 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:29 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_file(t_file *file)
{
	int i;

	i = -1;
	if (file->file_name)
		ft_strdel(&file->file_name);
	if (file->file)
	{
		while (file->file[++i])
			ft_strdel(&file->file[i]);
		free(file->file);
	}
}

void	free_error(t_tab *tab, t_file *file, int error)
{
	int i;

	i = -1;
	if (error == FAILURE)
		free_file(file);
	else
	{
		free_file(file);
		free_tab(tab, file, error);
		if (error == ERROR_TYPE_PARAM)
			free(tab->info_ins);
		if (error == TOO_BIG || error == FREE)
		{
			while (++i < tab->nb_instruction)
				ft_strdel(&tab->label_name[i]);
			free(tab->label_name);
			free(tab->info_ins);
			free(tab->n_label);
			free(tab->r_pos);
			if (error != TOO_BIG)
				free(tab->dir_pos);
		}
	}
}

void	free_split(t_file *file)
{
	int	i;

	i = -1;
	while (++i <= file->free_cnt)
		free(file->split[i]);
	free(file->split);
}
