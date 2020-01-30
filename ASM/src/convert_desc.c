/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_desc.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: maegaspa <maegaspa@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 03:08:59 by maegaspa     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 03:08:59 by maegaspa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"
#include <stdio.h>

void	convert_int(unsigned char **str, int nb)
{
	(*str)[0] = (nb >> 24) & 0xFF;
	(*str)[1] = (nb >> 16) & 0xFF;
	(*str)[2] = (nb >> 8) & 0xFF;
	(*str)[3] = nb & 0xFF;
}

void	write_binary_int(int nb, int fd)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	convert_int(&str, nb);
	write(fd, str, 4);
	free(str);
}

int		write_param(t_file *file, t_tab *tab)
{
	int i;
	int j;

	i = -1;
	while (++i < tab->nb_instruction)
	{
		j = -1;
		write(file->fd, &(tab->info_ins[i].id_inst), 1);
		printf("lsssss = %d\n", file->op[tab->info_ins[i].id_inst - 1].params_type[0] & T_REG);
		//write(file->fd, &())
		//printf("tab->info_ins[i].id_inst = %d et donc file->op[i].name = %s\n", tab->info_ins[i].id_inst, file->op[tab->info_ins[i].id_inst - 1].name);
		while (++j < file->op[tab->info_ins[i].id_inst - 1].nb_params)
			write_binary_int((file->op[tab->info_ins[i].id_inst - 1].params_type[j] & T_REG), file->fd);
				//write(file->fd, &(file->op[tab->info_ins[i].id_inst - 1].params_type[file->op[tab->info_ins[i].id_inst - 1].nb_params] & T_REG), file->op[tab->info_ins[i].id_inst - 1].acb);
			//write(file->fd, &(file->op[tab->info_ins[i].id_inst - 1].params_type), file->op[tab->info_ins[i].id_inst - 1].acb);

			//printf("file->op[i].nbparans = %d et param_type = %s\n", file->op[tab->info_ins[i].id_inst - 1].nb_params, file->op[tab->info_ins[i].id_inst - 1].params_type);
			//write(file->fd, file->op[i].params_type[j], 1);
		break;
	}
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

int 	write_name(t_description *desc, t_file *file)
{
	int 	i;

	i = -1;
    write(file->fd, desc->name, ft_strlen(desc->name));
    while (++i < ((PROG_NAME_LENGTH / 4)))
    	write_binary_int(0, file->fd);
	return (SUCCESS);
}

int 	write_comment(t_description *desc, t_file *file)
{
	int 	i;

    i = -1;
    write(file->fd, desc->comment, ft_strlen(desc->comment));
    while (++i < ((COMMENT_LENGTH / 4) - 2))
    	write_binary_int(0, file->fd);
	return (SUCCESS);
}

int		create_cor(t_description *desc, t_file *file, t_tab *tab)
{
	desc->file_name = add_cor(desc->file_name);
	if ((file->fd = open(desc->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600)) < 0)
		return (FAILURE);
	write_binary_int(COREWAR_EXEC_MAGIC, file->fd);
	if ((file->error = write_name(desc, file)) < 1)
		return (file->error);
	write_binary_int(0, file->fd);
	if ((file->error = write_comment(desc, file)) < 1)
		return (file->error);
	if ((file->error = write_param(file, tab)) < 1)
	    return (file->error);
	return (SUCCESS);
}

int 	convertion(t_description *desc, t_file *file, t_tab *tab)
{
	if ((file->error = create_cor(desc, file, tab)) < 1)
		return (file->error);
	return (SUCCESS);
}