/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:27 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:27 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	param_fill_dir2(t_tab *tab, t_file *file)
{
	tab->tabyte[file->j] = -4;
	tab->tabyte[file->j + 1] = -4;
	tab->tabyte[file->j + 2] = -4;
	tab->tabyte[file->j + 3] = -4;
	if (ft_strstr(tab->info_ins[file->i].parameter[file->n_param], file->tmp))
	{
		tab->tabyte[file->j] = 17;
		tab->tabyte[file->j + 1] = 17;
		tab->tabyte[file->j + 2] = 17;
		tab->tabyte[file->j + 3] = 17;
	}
	file->j += 4;
}

int		write_header(t_header *head, int fd, t_file *file)
{
	write_binary_int(head->magic, fd);
	write(fd, head->prog_name, PROG_NAME_LENGTH);
	write_binary_int(0, fd);
	write_binary_int(file->max_byte + 1, fd);
	write(fd, head->comment, COMMENT_LENGTH);
	write_binary_int(0, fd);
	return (SUCCESS);
}

char	*add_cor(char *str)
{
	char	*new_name;
	int		i;

	i = ft_strlen(str);
	new_name = ft_strnew(ft_strlen(str) + 4);
	ft_strcat(new_name, str);
	ft_strdel(&str);
	if (new_name[i - 1] == '.')
	{
		new_name[i] = 'c';
		new_name[i + 1] = 'o';
		new_name[i + 2] = 'r';
	}
	return (new_name);
}

int		create_cor(t_header *head, t_file *file, t_tab *tab)
{
	int i;

	i = -1;
	file->file_name = add_cor(file->file_name);
	if ((file->error = get_label_pos(tab, file)) < 1)
		return (file->error);
	if ((file->error = get_dir_pos(tab, file)) < 1)
		return (file->error);
	if ((file->fd = open(file->file_name, O_CREAT |
		O_WRONLY | O_TRUNC, 0600)) < 0)
		return (ERROR_OPEN);
	if (write_header(head, file->fd, file) != 1)
		return (ERROR_WRITE);
	while (++i < tab->nb_instruction)
	{
		write(file->fd, &(tab->info_ins[i].id_inst), 1);
		file->op_c = 0;
		if ((file->error = write_param(file, tab, i)) < 1)
			return (file->error);
		if ((file->error = write_reg_dir_ind(file, tab, i)) < 1)
			return (file->error);
	}
	return (SUCCESS);
}

int		convertion(t_header *head, t_file *file, t_tab *tab)
{
	int		i;

	i = -1;
	while (++i < CHAMP_MAX_SIZE)
		tab->tabyte[i] = 0;
	if ((file->error = create_cor(head, file, tab)) < 1)
		return (file->error);
	return (SUCCESS);
}
