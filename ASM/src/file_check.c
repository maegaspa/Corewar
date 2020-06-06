/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:44 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:30 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		check_file_name(t_file *file, char *file_name)
{
	int		len;

	len = ft_strlen(file_name);
	if (!(file_name[len - 1] == 's' && file_name[len - 2] == '.'))
	{
		ft_putstr_fd("Error \".s\" extension required\n", 2);
		ft_putstr_fd("Usage: ./asm <file.s>\n", 2);
		return (ERROR_DOT_S);
	}
	file->file_name = strndup(file_name, len - 1);
	return (SUCCESS);
}

int		init_file_2(t_file *file, t_header *head)
{
	if (is_name_or_comment(file->file[file->count], 1))
	{
		if ((file->error = true_syntaxe_info(head, file->file[file->count],
						ft_strlen(NAME_CMD_STRING), 1)) < 1)
			return (file->error);
		file->ligne_name = file->count;
		file->name++;
	}
	if (is_name_or_comment(file->file[file->count], 2))
	{
		if ((file->error = true_syntaxe_info(head, file->file[file->count],
						ft_strlen(COMMENT_CMD_STRING), 2)) < 1)
			return (file->error);
		file->ligne_comment = file->count;
		file->comment++;
	}
	return (SUCCESS);
}

int		init_file(t_file *file, t_header *head, char *file_name)
{
	if (!(file->file = get_file(file_name)))
		return (ERROR_EMPTY);
	delete_hash(file);
	init_struct_file(file, head);
	while (file->file[++file->count])
	{
		file->ligne_error = file->count;
		init_file_2(file, head);
	}
	if (file->name != 1 || file->comment != 1)
		return (ERROR_INFO);
	return (SUCCESS);
}

int		file_check(t_file *file, t_header *head, char *file_name)
{
	if ((check_file_name(file, file_name)) < 1)
		return (ERROR_DOT_S);
	if ((file->error = init_file(file, head, file_name)) < 1)
		return (file->error);
	return (SUCCESS);
}
