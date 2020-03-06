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

void	param_fill_dir(t_tab *tab, t_file *file)
{
	if (tab->info_ins[file->i].param[file->n_param].type_param == DIR_CODE)
    {
        if (which_direct(tab, file->i) == 1)
        {
        	tab->tabyte[file->j] = -2;
        	if (ft_strstr(tab->info_ins[file->i].parameter[file->n_param], file->tmp))
        	    tab->tabyte[file->j] = 5;
        	file->j += 2;
        }
        else
        {
        	tab->tabyte[file->j] = -4;
        	if (ft_strstr(tab->info_ins[file->i].parameter[file->n_param], file->tmp))
            	tab->tabyte[file->j] = 5;
        	file->j += 4;
		}
	}
}

void	param_fill(t_tab *tab, t_file *file)
{
	while (++file->n_param < tab->info_ins[file->i].nb_parameter)
    {
    	if (tab->info_ins[file->i].param[file->n_param].type_param == REG_CODE)
    		tab->tabyte[file->j++] = -1;
    	param_fill_dir(tab, file);
    	if (tab->info_ins[file->i].param[file->n_param].type_param == IND_CODE)
        {
        	tab->tabyte[file->j] += -2;
        	file->j += 2;
        }
   	}
}

int		get_label_pos(t_tab *tab, t_file *file)
{
	file->i = -1;
	file->j = 0;
	file->k = 1;
	if (!(get_label_init(tab)))
		return (file->error);
	while (++file->i < tab->nb_instruction)
	{
		file->n_param = -1;
		if (tab->info_ins[file->i].id_inst > 0)
			tab->tabyte[file->j++] = tab->info_ins[file->i].id_inst;
		if (file->op[tab->info_ins[file->i].id_inst - 1].acb)
			tab->tabyte[file->j++] = -3;
		param_fill(tab, file);
		if (!tab->info_ins[file->i].label)
		{
        	if (tab->tabyte[file->j] != -5)
        		tab->n_label[file->k] = file->j;
        }
        else
        	tab->label_name[file->k++] = tab->info_ins[file->i].label;
	}
	tab->tabyte[file->j] = -5;
	tab->n_label[file->k] = file->j - 1;
	file->max_byte = file->j - 1;
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
