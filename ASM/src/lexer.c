/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:09:06 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:32 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			is_instruction_name(char *str, t_file *file, t_tab *tab)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (str && !ft_strcmp(file->op[i].name, str))
		{
			tab->info_ins[file->cnt_tab].id_inst = file->op[i].id;
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int			is_label(char *str)
{
	int				i;
	int				j;
	unsigned int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		j = -1;
		if (str[i] == LABEL_CHAR)
		{
			if (count != ft_strlen(str) - 1)
				return (ERROR_LABEL);
			return (SUCCESS);
		}
		while (LABEL_CHARS[++j])
			if (str[i] == LABEL_CHARS[j])
				count++;
	}
	return (FAILURE);
}

int			is_instruction(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!ft_strlen(str))
		return (FAILURE);
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			j++;
	if (j)
		return (SUCCESS);
	return (FAILURE);
}

int			is_name_or_comment(char *str, int chose)
{
	int		i;

	i = 0;
	if (chose == 1)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!(ft_strncmp(&str[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))))
			return (SUCCESS);
	}
	if (chose == 2)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!(ft_strncmp(&str[i], COMMENT_CMD_STRING,
						ft_strlen(COMMENT_CMD_STRING))))
			return (SUCCESS);
	}
	return (0);
}
