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

//void	convert_short(unsigned char **ptr, int n)
//{
//	(*ptr)[0] = (n >> 8) & 0xFF;
//	(*ptr)[1] = n & 0xFF;
//}
//
//void	write_binary_short(int fd, short nb)
//{
//	unsigned char	*str;
//
//	str = (unsigned char *)ft_strnew(2);
//	convert_short(&str, nb);
//	write(fd, str, 2);
//	free(str);
//}

int		which_direct(t_tab *tab, int actual_inst)
{
    if (tab->info_ins[actual_inst].id_inst == 9 || tab->info_ins[actual_inst].id_inst == 10 || tab->info_ins[actual_inst].id_inst == 11
    	|| tab->info_ins[actual_inst].id_inst == 12 || tab->info_ins[actual_inst].id_inst == 15)
    	return (1);
   	if (tab->info_ins[actual_inst].id_inst == 1 || tab->info_ins[actual_inst].id_inst == 2 || tab->info_ins[actual_inst].id_inst == 6
   		|| tab->info_ins[actual_inst].id_inst == 7 || tab->info_ins[actual_inst].id_inst == 8 || tab->info_ins[actual_inst].id_inst == 13)
   		return (2);
   	return (0);
}

int		get_label_pos(t_tab *tab, t_file *file)
{
	int		i;
	int		n_param;
	int		add;
	int 	*tabyte;

	i = -1;
	add = 0;
	if (!(tabyte = (int *)malloc(sizeof(int) * tab->nb_instruction))) // REFAIRE TAB QUI REPREND QUAND str label = (null) -> stocker num du byte, comme ca le nvx tab fais la taille du nb de label;
		return (ERROR_MALLOC);
	while (++i < tab->nb_instruction)
		tabyte[i] = 0;
	i = -1;
	while(++i < tab->nb_instruction)
	{
		add = 0;
		n_param = -1;
		if (i != 0)
			tabyte[i] += tabyte[i - 1];
		if (i != tab->nb_instruction - 1)
			tabyte[i] += 1;
		if (file->op[tab->info_ins[i].id_inst - 1].acb)
       		tabyte[i] += 1;
		while(++n_param < tab->info_ins[i].nb_parameter)
		{
			if (tab->info_ins[i].param[n_param].type_param == REG_CODE)
				tabyte[i] += 1;
			if (tab->info_ins[i].param[n_param].type_param == DIR_CODE)
			{
				if (which_direct(tab, i) == 1)
					tabyte[i] += 2;
				else
					tabyte[i] += 4;
			}
			if (tab->info_ins[i].param[n_param].type_param == IND_CODE)
				tabyte[i] += 2;
		}
		printf("tabyte[%d] = %d\n", i, tabyte[i]);
	}
	return (SUCCESS);
}

void	convert_int(unsigned char **str, int nb)
{
	(*str)[0] = (nb >> 24) & 0xFF;
	(*str)[1] = (nb >> 16) & 0xFF;
	(*str)[2] = (nb >> 8) & 0xFF;
	(*str)[3] = nb & 0xFF;
}

void    write_binary_int(int nb, int fd)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	convert_int(&str, nb);
	write(fd, str, 4);
	free(str);
}

int		write_dir_int(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	int	val;

	val = ft_atoi_2(tab->info_ins[actual_inst].parameter[n_param]);
	if (n_param == 0)
		write_binary_int(val, file->fd);
	if (n_param == 1)
		write_binary_int(val, file->fd);
	if (n_param == 2)
		write_binary_int(val, file->fd);
	return (SUCCESS);
}

int		write_short(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	unsigned short val;
	char tmp[2];

	tmp[0] = LABEL_CHAR;
	tmp[1] = '\0';
    val = (short)ft_atoi_2(tab->info_ins[actual_inst].parameter[n_param]);
    printf("lsddlsld = %s\n", tab->info_ins[actual_inst].parameter[n_param]);
    printf("[%hd]\n", val);
    swap_2(&val);
    if (ft_strstr(tab->info_ins[actual_inst].parameter[n_param], tmp))
    {
    	printf("in if n_param in else = %d\n", n_param); //ENCORE COMPARAISON ENTRE LABEL POINTE ET LE BON LABEL; // SI (null) ALORS Num byte, last du tab -> nb_writen_bytes;
    	if (n_param == 0)
        	write(file->fd, &val, IND_SIZE); //trouver la size a retirer pour retrouver le parametre pointé // comptage index de
        	//byte pour l'ecriture avec un tableau d'index /!\ OU /!\ comptage du nb de byte avec les infos des inst+opc+param pour chaque label, comme ca on obtient la pos pointé en byte (ex num = 15 pour label live avec zork)
        if (n_param == 1)
    		write(file->fd, &val, IND_SIZE);
        if (n_param == 2)
    		write(file->fd, &val, IND_SIZE);
    }
    else
    {
    	printf("n_param in else = %d\n", n_param);
    	if (n_param == 0)
    		write(file->fd, &val, IND_SIZE);
       	if (n_param == 1)
    		write(file->fd, &val, IND_SIZE);
       	if (n_param == 2)
       		write(file->fd, &val, IND_SIZE);
    }
    return (SUCCESS);
}

int		write_reg_dir_ind(t_file *file, t_tab *tab, int actual_inst)
{
	int n_param;

	n_param = -1;
	while(++n_param < tab->info_ins[actual_inst].nb_parameter)
	{
    	if (tab->info_ins[actual_inst].param[n_param].type_param == REG_CODE)
		{
			printf(" reg n_param in else = %d\n", n_param);
			if (n_param == 0)
				write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
			if (n_param == 1)
            	write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
           	if (n_param == 2)
            	write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
    	}
    	if (tab->info_ins[actual_inst].param[n_param].type_param == DIR_CODE)
    	{
			if (which_direct(tab, actual_inst) == 1) // trouver condition pour size de short | faire une fonction qui check le label
				write_short(n_param, file, tab, actual_inst);
			else
				write_dir_int(n_param, file, tab, actual_inst);
    	}
    	if (tab->info_ins[actual_inst].param[n_param].type_param == IND_CODE)
			write_short(n_param, file, tab, actual_inst);
	}
	return (SUCCESS);
}

int		write_param(t_file *file, t_tab *tab, int actual_inst)
{
	int 			n_param;

	n_param = -1;
	while(++n_param < tab->info_ins[actual_inst].nb_parameter)
	{
		if (tab->info_ins[actual_inst].param[n_param].type_param == REG_CODE)
		{
			if (n_param == 0)
				file->op_c += 64;
			if (n_param == 1)
				file->op_c += (64 >> 2);
			if (n_param == 2)
				file->op_c += (64 >> 4);
		}
		if (tab->info_ins[actual_inst].param[n_param].type_param == DIR_CODE)
		{
			if (n_param == 0)
            	file->op_c += 128;
            if (n_param == 1)
            	file->op_c += (128 >> 2);
            if (n_param == 2)
            	file->op_c += (128 >> 4);
		}
		if (tab->info_ins[actual_inst].param[n_param].type_param == IND_CODE)
		{
			if (n_param == 0)
            	file->op_c += 192;
            if (n_param == 1)
            	file->op_c += (192 >> 2);
            if (n_param == 2)
            	file->op_c += (192 >> 4);
		}
		printf("tab->info_ins[%d].label = \t\t%s\n", actual_inst, tab->info_ins[actual_inst].label);
		printf("tab->info_ins[%d].parameter[j] = \t\t%s\n", actual_inst, tab->info_ins[actual_inst].parameter[n_param]);
		printf("tab->info_ins[%d].param->type_param = \t\t%d\n", actual_inst, tab->info_ins[actual_inst].param[n_param].type_param);
		printf("tab->info_ins[actual_inst].param[n_param].is_direct = %d\n", tab->info_ins[actual_inst].param[n_param].is_direct);
        printf("tab->info_ins[actual_inst].param[n_param].direct_str = %s\n", tab->info_ins[actual_inst].param[n_param].direct_str);
	}
	printf("[%d] acb = %d\n", tab->info_ins[actual_inst].id_inst, file->op[tab->info_ins[actual_inst].id_inst - 1].acb);
	//printf("tab->info_ins[actual_inst].param[n_param].direct_str = %s\n", tab->info_ins[actual_inst].param[n_param].direct_str);
	//printf("tab->info_ins[actual_inst].regitre = %d\n", tab->info_ins[actual_inst].param[n_param].registre);
	if (file->op[tab->info_ins[actual_inst].id_inst - 1].acb)
		write(file->fd, &(file->op_c), file->op[tab->info_ins[actual_inst].id_inst - 1].acb);
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
	printf("%s\n", file->file_name);
	if ((file->fd = open(file->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600)) < 0)
		return (FAILURE);
	if (write(file->fd, &(*head), sizeof(t_header)) != sizeof(t_header))
		return (ERROR_WRITE);
	get_label_pos(tab, file);
	while (++i < tab->nb_instruction)
	{
		write(file->fd, &(tab->info_ins[i].id_inst), 1);
		printf("id_inst = %d\n", tab->info_ins[i].id_inst);
		file->op_c = 0;
		if ((file->error = write_param(file, tab, i)) < 1)
			return (file->error);
		if ((file ->error = write_reg_dir_ind(file, tab, i) < 1))
		    return (file->error);
		//break;
	}
	return (SUCCESS);
}

int 	convertion(t_header *head, t_file *file, t_tab *tab)
{
	if ((file->error = create_cor(head, file, tab)) < 1)
		return (file->error);
	return (SUCCESS);
}