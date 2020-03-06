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
	get_label_pos(tab, file);
    get_dir_pos(tab, file);
	if ((file->fd = open(file->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600)) < 0)
		return (FAILURE);
	if (write(file->fd, &(*head), sizeof(t_header)) != sizeof(t_header))
		return (ERROR_WRITE);
	while (++i < tab->nb_instruction)
	{
		write(file->fd, &(tab->info_ins[i].id_inst), 1);
		file->op_c = 0;
		if ((file->error = write_param(file, tab, i)) < 1)
			return (file->error);
		if ((file ->error = write_reg_dir_ind(file, tab, i) < 1))
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
