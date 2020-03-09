/*# **************************************************************************** #*/
/*#                                                                              #*/
/*#                                                         :::      ::::::::    #*/
/*#    bite                                               :+:      :+:    :+:    #*/
/*#                                                     +:+ +:+         +:+      #*/
/*#    By: maegaspa <marvin@42.fr>                    +#+  +:+       +#+         #*/
/*#                                                 +#+#+#+#+#+   +#+            #*/
/*#    Created: 2020/03/06 21:57:36 by maegaspa          #+#    #+#              #*/
/*#    Updated: 2020/03/06 21:58:16 by maegaspa         ###   ########lyon.fr    #*/
/*#                                                                              #*/
/*# **************************************************************************** #*/

#include "../includes/asm.h"

int		write_header(t_header *head, int fd, t_file *file) //GESTION ERREUR EN +
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
	if ((file->error = get_label_pos(tab, file) < 1))
		return (file->error);
	if ((file->error = get_dir_pos(tab, file) < 1))
		return (file->error);
	if ((file->fd = open(file->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600)) < 0)
		return (ERROR_OPEN);
	if (write_header(head, file->fd, file) != 1)
		return (ERROR_WRITE);
	while (++i < tab->nb_instruction)
	{
		write(file->fd, &(tab->info_ins[i].id_inst), 1);
		file->op_c = 0;
		if ((file->error = write_param(file, tab, i)) < 1)
			return (file->error);
		if ((file->error = write_reg_dir_ind(file, tab, i) < 1))
		    return (file->error);
	}
	return (SUCCESS);
}

int 	convertion(t_header *head, t_file *file, t_tab *tab)
{
	if ((file->error = create_cor(head, file, tab)) < 1)
		return (file->error);
	return (SUCCESS);
}
