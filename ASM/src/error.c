#include "../includes/asm.h"
#include <stdio.h>

void	print_line_error(t_file *file)
{
	ft_putstr_fd("Line ", 2);
	ft_putnbr_fd(file->ligne_error, 2);
	ft_putstr_fd(": \"", 2);
	ft_putstr_fd(file->file[file->ligne_error], 2);
	ft_putstr_fd("\"", 2);
	ft_putstr_fd("\n", 2);
}

void 	print_error(t_file *file)
{
	if (file->error == ERROR_MALLOC)
	{
		ft_putstr_fd("ERROR: Malloc failed\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_INSTRUCT)
	{
		ft_putstr_fd("ERROR: Bad instruction\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_CHAR)
	{
		ft_putstr_fd("ERROR: Unexpected char\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_PARAM)
	{
		ft_putstr_fd("ERROR: Bad parameter\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_LABEL)
	{
		ft_putstr_fd("ERROR: Label not declare\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_EMPTY)
	{
		ft_putstr_fd("ERROR: Empty file\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_INFO)
	{
		ft_putstr_fd("ERROR: Unexpected CMD string\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_MEMORY)
	{
		ft_putstr_fd("ERROR: Lot of memory use\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_NOINST)
	{
		ft_putstr_fd("ERROR: No instruction\n", 2);
		print_line_error(file);
	}
}

void 	free_error(t_tab *tab, t_file *file, t_description *desc)
{
	int 	i;
	int 	j;

	i = -1;
	if (desc->name)
		ft_strdel(&desc->name);
	if (desc->comment)
		ft_strdel(&desc->comment);
	if (desc->file_name)
		ft_strdel(&desc->file_name);
	if (file->file)
	{
		while (file->file[++i])
			ft_strdel(&file->file[i]);
		free(file->file);
	}
	if (tab->nb_instruction)
	{
		i = -1;
		while (++i < tab->nb_instruction)
		{
			if (tab->info_ins[i].label)
				ft_strdel(&tab->info_ins[i].label);
			if (tab->info_ins[i].instruction)
				ft_strdel(&tab->info_ins[i].instruction);
			j = -1;
			while (++j < tab->info_ins[i].nb_parameter)
			{
				if (tab->info_ins[i].direct_str != NULL)
				{
					ft_strdel(&tab->info_ins[i].direct_str);
					break;
				}
				if (tab->info_ins[i].indirect_str != NULL)
				{
					ft_strdel(&tab->info_ins[i].indirect_str);
					break;
				}
				if (tab->info_ins[i].instruction && (tab->info_ins[i].type_param[j] != T_REG && tab->info_ins[i].type_param[j] != T_IND && tab->info_ins[i].type_param[j] != T_DIR))
					break;
			}
			if (tab->info_ins[i].check)
				free(tab->info_ins[i].type_param);
			j = -1;
			while (++j < tab->info_ins[i].nb_parameter)
				ft_strdel(&tab->info_ins[i].parameter[j]);
			free(tab->info_ins[i].parameter);
		}
	}
	if (tab->info_ins)
		free(tab->info_ins);
}