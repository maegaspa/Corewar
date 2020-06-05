/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:33 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:29 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_tab_info_param(t_tab *tab, int i)
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
			(tab->info_ins[i].param[j].type_param != T_REG &&
			tab->info_ins[i].param[j].type_param != T_IND &&
			tab->info_ins[i].param[j].type_param != T_DIR))
			break ;
	}
}

void	free_tab_info3(t_tab *tab, int error)
{
	int		i;
	int		j;

	i = -1;
	if (error == ERROR_PARAM || error == FREE || error == TOO_BIG ||
			error == ERROR_TYPE_PARAM)
	{
		while (++i < tab->nb_instruction)
		{
			if (tab->info_ins[i].label)
				ft_strdel(&tab->info_ins[i].label);
			if (tab->info_ins[i].instruction)
				ft_strdel(&tab->info_ins[i].instruction);
			free_tab_info_param(tab, i);
			j = -1;
			while (++j < tab->info_ins[i].nb_parameter)
				ft_strdel(&tab->info_ins[i].parameter[j]);
			if (tab->info_ins[i].nb_parameter)
				free(tab->info_ins[i].parameter);
			if (tab->info_ins[i].param)
				free(tab->info_ins[i].param);
		}
	}
}

void	free_tab_info2(t_tab *tab, t_file *file, int error)
{
	int		i;
	int		j;

	if (error == ERROR_PARAM_C)
	{
		i = -1;
		while (++i < tab->nb_instruction)
		{
			j = -1;
			while (++j < tab->info_ins[i].nb_parameter)
				ft_strdel(&tab->info_ins[i].parameter[j]);
			if (tab->info_ins[i].nb_parameter)
				free(tab->info_ins[i].parameter);
		}
		free_split(file);
		i = -1;
		if (tab->nb_instruction)
			while (++i < tab->nb_instruction)
				ft_strdel(&tab->info_ins[i].label);
		i = -1;
		if (tab->nb_instruction)
			while (++i < tab->nb_instruction)
				ft_strdel(&tab->info_ins[i].instruction);
		free(tab->info_ins);
	}
}

void	free_tab_info1(t_tab *tab, t_file *file, int error)
{
	int		i;
	int		j;

	if (error == ERROR_INSTRUCT)
	{
		i = -1;
		while (++i < tab->nb_instruction)
		{
			j = -1;
			while (++j < tab->info_ins[i].nb_parameter)
				ft_strdel(&tab->info_ins[i].parameter[j]);
			if (tab->info_ins[i].nb_parameter)
				free(tab->info_ins[i].parameter);
		}
		i = -1;
		free_split(file);
		if (tab->nb_instruction)
			while (++i < tab->nb_instruction)
				ft_strdel(&tab->info_ins[i].label);
		i = -1;
		if (tab->nb_instruction)
			while (++i < tab->nb_instruction)
				ft_strdel(&tab->info_ins[i].instruction);
		free(tab->info_ins);
	}
}

void	free_tab(t_tab *tab, t_file *file, int error)
{
	free_tab_info1(tab, file, error);
	free_tab_info2(tab, file, error);
	free_tab_info3(tab, error);
}
