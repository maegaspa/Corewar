/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:44:50 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:44:50 by maegaspa         ###   ########lyon.fr   */
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

void	free_tab_info2(t_tab *tab, int error)
{
	int 	i;
	int 	j;

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
			j = -1;
			while (++j < tab->info_ins[i].nb_parameter)
			{
				if (tab->info_ins[i].param[j].direct_str != NULL)
				{
					ft_strdel(&tab->info_ins[i].param[j].direct_str);
					break;
				}
				if (tab->info_ins[i].param[j].indirect_str != NULL)
				{
					ft_strdel(&tab->info_ins[i].param[j].indirect_str);
					break;
				}
				if (tab->info_ins[i].instruction && (tab->info_ins[i].param[j].type_param != T_REG && tab->info_ins[i].param[j].type_param != T_IND && tab->info_ins[i].param[j].type_param != T_DIR))
					break;
			}
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

void	free_tab_info1(t_tab *tab, t_file *file, int error)
{
	int 	i;
	int 	j;

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
//		if (file->free_cnt)
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

void	free_tab(t_tab *tab, t_file *file, int error)
{
	free_tab_info1(tab, file, error);
	free_tab_info2(tab, error);
}

void 	free_error(t_tab *tab, t_file *file, int error)
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
			i = -1;
		//	printf("EN REVANCHE ICI NB INSTR = %d\n", tab->nb_instruction);
			while (++i < tab->nb_instruction)
				ft_strdel(&tab->label_name[i]);
			free(tab->label_name);
			free(tab->info_ins);
			free(tab->n_label);
			if (error != TOO_BIG)
			{
				free(tab->dir_pos);
				free(tab->r_pos);
			}
		}
	}
}

/*void	free_error(t_tab *tab, t_file *file)
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
}*/

void				free_split(t_file *file)
{
	int	i;

	i = -1;
	while (++i <= file->free_cnt)
		free(file->split[i]);
	free(file->split);
}
