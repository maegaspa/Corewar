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

int		which_direct(t_tab *tab, int actual_inst)
{
    if (tab->info_ins[actual_inst].id_inst == 9 || tab->info_ins[actual_inst].id_inst == 10 || tab->info_ins[actual_inst].id_inst == 11
    	|| tab->info_ins[actual_inst].id_inst == 12 || tab->info_ins[actual_inst].id_inst == 15)
    	return (1);
   	if (tab->info_ins[actual_inst].id_inst == 1 || tab->info_ins[actual_inst].id_inst == 2 || tab->info_ins[actual_inst].id_inst == 6
   		|| tab->info_ins[actual_inst].id_inst == 7 || tab->info_ins[actual_inst].id_inst == 8 || tab->info_ins[actual_inst].id_inst == 13) //CAS : DIRECT LABEL CHAR DEFINI SUR 4 OCTETS
   		return (2);
   	return (0);
}

int		get_label_init(t_tab *tab)
{
	int		i;

	i = -1;
	if (!(tab->tabyte = (int *)malloc(sizeof(int) * CHAMP_MAX_SIZE)))
    	return (ERROR_MALLOC);
 	if (!(tab->n_label = (int *)malloc(sizeof(int) * tab->nb_instruction)))
 		return (ERROR_MALLOC);
    if (!(tab->label_name = (char **)malloc(sizeof(char*) * tab->nb_instruction)))
    	return (ERROR_MALLOC);
    i = -1;
    while(++i < tab->nb_instruction)
    {
    	if (!(tab->label_name[i] = (char *)malloc(sizeof(char) * 6)))
    		return (ERROR_MALLOC);
   		tab->n_label[i] = 0;
   	}
   	return (SUCCESS);
}


int		get_label_pos(t_tab *tab, t_file *file) //RELOU POUR LA NORME
{
	file->i = -1;
	file->j = 0;
	file->k = 1;
	if (!(get_label_init(tab)))
		return (file->error);
	while(++file->i < tab->nb_instruction)
	{
		file->n_param = -1;
		if (tab->info_ins[file->i].id_inst > 0)
		{
			tab->tabyte[file->j] = tab->info_ins[file->i].id_inst;
			file->j++;
		}
		if (file->op[tab->info_ins[file->i].id_inst - 1].acb)
		{
			tab->tabyte[file->j] = -3;
       		file->j++;
		}
		while(++file->n_param < tab->info_ins[file->i].nb_parameter)
		{
			if (tab->info_ins[file->i].param[file->n_param].type_param == REG_CODE)
			{
				tab->tabyte[file->j] = -1;
				file->j++;
			}
			if (tab->info_ins[file->i].param[file->n_param].type_param == DIR_CODE)
			{
				if (which_direct(tab, file->i) == 1)
				{
					tab->tabyte[file->j] = -2;
					tab->tabyte[file->j + 1] = -2;
					if (ft_strstr(tab->info_ins[file->i].parameter[file->n_param], file->tmp))
					{
					    tab->tabyte[file->j] = 5;
                        tab->tabyte[file->j + 1] = 0;
					}
					file->j += 2;
				}
				else
				{
					tab->tabyte[file->j] = -4;
					tab->tabyte[file->j + 1] = -4;
					tab->tabyte[file->j + 2] = -4;
					tab->tabyte[file->j + 3] = -4;
					if (ft_strstr(tab->info_ins[file->i].parameter[file->n_param], file->tmp))
                    {
                        tab->tabyte[file->j] = 5;
                        tab->tabyte[file->j + 1] = 0;
                        tab->tabyte[file->j + 2] = 0;
                        tab->tabyte[file->j + 3] = 0;
                    }
					file->j += 4;
				}
			}
			if (tab->info_ins[file->i].param[file->n_param].type_param == IND_CODE)
			{
				tab->tabyte[file->j] += -2;
				file->j += 2;
			}
		}
		if (!tab->info_ins[file->i].label)
		{
        	if (tab->tabyte[file->j] != -5)
        		tab->n_label[file->k] = file->j;
        }
        else
        {
        	tab->label_name[file->k] = tab->info_ins[file->i].label;
        	file->k++;
        }
	}
	tab->tabyte[file->j] = -5;
	tab->n_label[file->k] = file->j - 1;
	file->max_byte = file->j - 1;
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

int		get_dir_pos(t_tab *tab, t_file *file)
{
	int 	i;
	int		k;
	int		j;

	i = -1;
	k = 0;
	j = 0;
	if (!(tab->dir_pos = (int*)malloc(sizeof(int) * tab->nb_instruction)))
		return (ERROR_MALLOC);
	if (!(tab->r_pos = (int*)malloc(sizeof(int) * tab->nb_instruction)))
    	return (ERROR_MALLOC);
	while (++i < file->max_byte)
	{
		if (tab->tabyte[i] > 0 && tab->tabyte[i] != 5)
		{
			tab->dir_pos[k] = i;
			k++;
		}
		if (tab->tabyte[i] == 5)
		{
			tab->r_pos[j] = i;
			j++;
		}
	}
	i = -1;
	return (SUCCESS);
}


int		write_dir_int(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	unsigned int	val;
	int 			i;

    val = ft_atoi_2(tab->info_ins[actual_inst].parameter[n_param]);
    i = -1;
	if (ft_strstr(tab->info_ins[actual_inst].parameter[n_param], file->tmp))
	{
		while (++i < tab->nb_instruction)
		{
			if (tab->label_name[i])
			{
				if (ft_strcmp(tab->label_name[i], tab->info_ins[actual_inst].param[n_param].direct_str) == 0)
    			{
    				val = tab->n_label[i] - tab->dir_pos[actual_inst];
    				if (tab->n_label[i] <= tab->dir_pos[actual_inst])
                    	val = 4294967296 - (tab->dir_pos[actual_inst] - tab->n_label[i]);
    				write_binary_int(val, file->fd);
    			}
    		}
		}
	}
	else
	{
		if (n_param == 0)
			write_binary_int(val, file->fd);
		if (n_param == 1)
			write_binary_int(val, file->fd);
		if (n_param == 2)
			write_binary_int(val, file->fd);
	}
	return (SUCCESS);
}

int		write_short(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	unsigned short val;
	int				i;

    val = (short)ft_atoi_2(tab->info_ins[actual_inst].parameter[n_param]);
    swap_2(&val);
    if (ft_strstr(tab->info_ins[actual_inst].parameter[n_param], file->tmp))
    {
    	i = -1;
    	while (++i < tab->nb_instruction)
    	{
    		if (tab->label_name[i])
    		{
    			if (ft_strcmp(tab->label_name[i], tab->info_ins[actual_inst].param[n_param].direct_str) == 0)
    			{
    				val = tab->n_label[i] - tab->dir_pos[actual_inst];
    				if (tab->n_label[i] <= tab->dir_pos[actual_inst])
    					val = 65536 - (tab->dir_pos[actual_inst] - tab->n_label[i]);
    				swap_2(&val);
    				write(file->fd, &val, IND_SIZE);
    			}
    		}
    	}
    }
    else
    {
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
			if (n_param == 0)
				write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
			if (n_param == 1)
            	write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
           	if (n_param == 2)
            	write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
    	}
    	if (tab->info_ins[actual_inst].param[n_param].type_param == DIR_CODE)
    	{
			if (which_direct(tab, actual_inst) == 1)
				write_short(n_param, file, tab, actual_inst);
			else
				write_dir_int(n_param, file, tab, actual_inst);
    	}
    	if (tab->info_ins[actual_inst].param[n_param].type_param == IND_CODE)
			write_short(n_param, file, tab, actual_inst);
	}
	return (SUCCESS);
}

void	stock_reg_dir(t_tab *tab, t_file *file, int n_param, int actual_inst)
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
}

int		write_param(t_file *file, t_tab *tab, int actual_inst)
{
	int 			n_param;

	n_param = -1;
	while(++n_param < tab->info_ins[actual_inst].nb_parameter)
	{
		stock_reg_dir(tab, file, n_param, actual_inst);
		if (tab->info_ins[actual_inst].param[n_param].type_param == IND_CODE)
		{
			if (n_param == 0)
            	file->op_c += 192;
            if (n_param == 1)
            	file->op_c += (192 >> 2);
            if (n_param == 2)
            	file->op_c += (192 >> 4);
		}
	}
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