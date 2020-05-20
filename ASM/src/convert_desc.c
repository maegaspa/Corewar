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

int		ft_atoi_2(char const *str)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || ft_isalpha(str[i])
			|| str[i] == '%' || str[i] == '0' || str[i] == '+' || str[i] == '-'
			|| str[i] == '#' || str[i] == 'l' || str[i] == 'h' || str[i] == 'L')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + str[i++] - '0';
	return (nbr);
}

void		write_dir_int_lab(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	int 			i;
	unsigned int	val;

	i = -1;
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

int		write_dir_int(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	unsigned int	val;

    val = ft_atoi_2(tab->info_ins[actual_inst].parameter[n_param]);
	if (ft_strstr(tab->info_ins[actual_inst].parameter[n_param], file->tmp))
		write_dir_int_lab(n_param, file, tab, actual_inst);
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

void	write_dir_short_lab(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	int 			i;
	unsigned short val;

	i = -1;
    while (++i < tab->nb_instruction)
    {
    	if (tab->label_name[i] && ft_strlen(tab->label_name[i]) > 0)
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

int		write_short(int n_param, t_file *file, t_tab *tab, int actual_inst)
{
	unsigned short val;

    val = (short)ft_atoi_2(tab->info_ins[actual_inst].parameter[n_param]);
    swap_2(&val);
    if (ft_strstr(tab->info_ins[actual_inst].parameter[n_param], file->tmp))
    	write_dir_short_lab(n_param, file, tab, actual_inst);
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
	while (++n_param < tab->info_ins[actual_inst].nb_parameter)
	{
    	if (tab->info_ins[actual_inst].param[n_param].type_param == T_REG)
		{
			if (n_param == 0)
				write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
			if (n_param == 1)
            	write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
           	if (n_param == 2)
            	write(file->fd, &(tab->info_ins[actual_inst].param[n_param].registre), REG_SIZE);
    	}
    	if (tab->info_ins[actual_inst].param[n_param].type_param == T_DIR)
    	{
			if (which_direct(tab, actual_inst) == 1)
				write_short(n_param, file, tab, actual_inst);
			else
				write_dir_int(n_param, file, tab, actual_inst);
    	}
    	if (tab->info_ins[actual_inst].param[n_param].type_param == T_IND)
			write_short(n_param, file, tab, actual_inst);
	}
	return (SUCCESS);
}
