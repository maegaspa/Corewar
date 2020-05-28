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

int			syntaxe_dcote(char *str, int select)
{
	int		count;

	count = 0;
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
	while (str[select])
	{
		while (str[select] == ' ' || str[select] == '\t')
			select++;
		if (str[select] != COMMENT_CHAR)
			return (ERROR_COMMENT);
		else
			break ;
	}
	return (SUCCESS);
}

int			syntaxe_name_com(t_header *head, char *str, int tmp, int chose)
{
	int		i;

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

int			true_syntaxe_info(t_header *head, char *str, int select, int chose)
{
	int		tmp;
	int		error;

	error = 0;
	while (str[select] == ' ' || str[select] == '\t')
		select++;
	if (str[select] == '\"')
	{
		tmp = select;
		if ((error = syntaxe_dcote(str, select)) != SUCCESS)
			return (error);
		if ((error = syntaxe_name_com(head, str, tmp, chose)) != SUCCESS)
			return (error);
	}
	else
		return (ERROR_CHAR);
	return (SUCCESS);
}
