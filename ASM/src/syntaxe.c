/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:09:06 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:32 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			true_syntaxe2(char *str, int tmp, int chose, t_header *head)
{
	int i;

	i = -1;
	while (str[++tmp] != '\"')
	{
		if (chose == 1)
			head->prog_name[++i] = str[tmp];
		if (chose == 2)
			head->comment[++i] = str[tmp];
	}
	if (chose == 1)
		head->prog_name[++i] = '\0';
	if (chose == 2)
		head->comment[++i] = '\0';
	if (i >= PROG_NAME_LENGTH)
		return (ERROR_MEMORY);
	if (i >= COMMENT_LENGTH)
		return (ERROR_MEMORY);
	return (SUCCESS);
}

int			true_syntaxe1(char *str, int count, int select)
{
	select++;
	while (str[select] != '\"' && str[select])
	{
		if (count > 1 && str[select] != ' ' && str[select] != '\t')
			return (ERROR_INFO);
		select++;
	}
	if (str[select] != '\"')
		return (ERROR_CHAR);
	select++;
	return (select);
}

int			true_syntaxe_info(t_header *head, char *str, int select, int chose)
{
	int		tmp;

	while (str[select] == ' ' || str[select] == '\t')
		select++;
	if (str[select] == '\"')
	{
		tmp = select;
		if ((select = true_syntaxe1(str, 0, select)) < 0)
			return (select);
		while (str[select])
		{
			while (str[select] == ' ' || str[select] == '\t')
				select++;
			if (str[select] != COMMENT_CHAR)
				return (ERROR_COMMENT);
			else
				break ;
		}
		if (true_syntaxe2(str, tmp, chose, head) < 0)
			return (ERROR_MEMORY);
	}
	else
		return (ERROR_CHAR);
	return (SUCCESS);
}
