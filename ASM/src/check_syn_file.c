/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:09:21 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:09:21 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		read_instruction(t_file *file)
{
	int i;

	file->count = -1;
	file->nb_instruction = 0;
	while (file->file[++file->count])
	{
		i = 0;
		while (file->file[file->count][i] == ' '
				|| file->file[file->count][i] == '\t')
			i++;
		if (file->file[file->count][i] == COMMENT_CHAR)
			file->count++;
		if (is_instruction(file->file[file->count]) == SUCCESS)
			file->nb_instruction++;
	}
	file->ligne_error = file->count;
	if (file->nb_instruction == 2)
		return (ERROR_NOINST);
	file->nb_instruction -= 2;
	return (SUCCESS);
}

int		for_label_or_instruction(t_tab *tab, t_file *file)
{
	if (is_instruction_name(file->split[file->cnt_split], file, tab) == SUCCESS)
	{
		tab->info_ins[file->cnt_tab].instruction =
			strndup(file->split[file->cnt_split],
					(ft_strlen(file->split[file->cnt_split])));
		file->cnt_inst = 1;
	}
	if ((!file->cnt_split && !file->cnt_inst) || !file->cnt_inst)
		return (ERROR_INSTRUCT);
	if (file->cnt_split)
		file->len = file->len2 - 1;
	else
		file->len = file->len1 - 1;
	return (SUCCESS);
}

int		is_label_or_instruction(t_tab *tab, t_file *file)
{
	file->free_cnt = 0;
	file->cnt_split = 0;
	file->cnt_inst = 0;
	tab->no_prob4 = 1;
	if (ft_strlen(file->file[file->count]) > 0)
		file->split = ft_strsplitwsp(file->file[file->count], file);
	if (is_label(file->split[file->cnt_split]) == SUCCESS)
	{
		tab->info_ins[file->cnt_tab].label =
			strndup(file->split[file->cnt_split],
					(ft_strlen(file->split[file->cnt_split]) - 1));
		file->cnt_split++;
	}
	else if ((file->error = is_label(file->split[file->cnt_split])) < 1 &&
			file->error != FAILURE)
		return (file->error);
	if ((file->error = for_label_or_instruction(tab, file)) != SUCCESS)
		return (file->error);
	free_split(file);
	return (SUCCESS);
}

int		check_param_2(t_tab *tab, t_file *file, int i, int j)
{
	if (j != 1)
		tab->info_ins[file->cnt_tab].nb_parameter = i;
	if ((tab->info_ins[file->cnt_tab].nb_parameter !=
		file->op[tab->info_ins[file->cnt_tab].id_inst - 1].nb_params)
		|| (file->param_error + 1 != tab->info_ins[file->cnt_tab].nb_parameter))
		return (ERROR_PARAM);
	return (SUCCESS);
}

int		check_param(t_tab *tab, t_file *file)
{
	int i;
	int j;

	file->param_error = 0;
	i = -1;
	while (file->file[file->count][++i])
		if (file->file[file->count][i] == SEPARATOR_CHAR)
			file->param_error++;
	tab->info_ins[file->cnt_tab].parameter =
		ft_strsplit2(&file->file[file->count][++file->len]);
	i = -1;
	j = 0;
	while (tab->info_ins[file->cnt_tab].parameter[++i])
	{
		if (tab->info_ins[file->cnt_tab].parameter[i][0] == COMMENT_CHAR)
		{
			tab->info_ins[file->cnt_tab].nb_parameter = i;
			j = 1;
		}
		if (j == 1)
			ft_strdel(&tab->info_ins[file->cnt_tab].parameter[i]);
	}
	if ((file->error = check_param_2(tab, file, i, j)) != SUCCESS)
		return (file->error);
	return (SUCCESS);
}
