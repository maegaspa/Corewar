/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:09:21 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:09:21 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		check_file_int(t_tab *tab, t_file *file, int i)
{
	if (file->file[file->count][i] == COMMENT_CHAR)
		file->count++;
	else
	{
		if (is_instruction(file->file[file->count]) == SUCCESS
				&& file->ligne_name != file->count &&
				file->ligne_comment != file->count)
		{
			tab->info_ins[file->cnt_tab].line_error = file->count;
			file->ligne_error = file->count;
			tab->info_ins[file->cnt_tab].label = NULL;
			if ((file->error = is_label_or_instruction(tab, file)) < 1)
				return (file->error);
			if ((file->error = check_param(tab, file)) < 1)
				return (file->error);
			file->cnt_tab++;
		}
	}
	return (SUCCESS);
}

int		lexer_analysis(t_tab *tab, t_file *file)
{
	int i;

	file->count = -1;
	file->cnt_tab = 0;
	while (file->file[++file->count])
	{
		i = 0;
		while (file->file[file->count][i] == ' ' ||
		file->file[file->count][i] == '\t')
			i++;
		if ((file->error = check_file_int(tab, file, i)) != SUCCESS)
			return (file->error);
	}
	return (SUCCESS);
}

int		lexer(t_tab *tab, t_file *file)
{
	if ((file->error = read_instruction(file)) < 1)
		return (file->error);
	if ((file->error = init_instruction_tab(tab, file)) < 1)
		return (file->error);
	if ((file->error = lexer_analysis(tab, file)) < 1)
		return (file->error);
	if ((file->error = init_param(tab)) < 1)
		return (file->error);
	if ((file->error = define_param(tab, file)) < 1)
		return (file->error);
	tab->no_prob = 1;
	return (SUCCESS);
}

int		exec_process(t_tab *tab, t_file *file, t_header *head, char **av)
{
	if ((file->error = file_check(file, head, av[1])) < 1)
	{
		print_error(file);
		free_error(tab, file);
		return (file->error);
	}
	if ((file->error = lexer(tab, file)) < 1)
	{
		print_error(file);
		free_error(tab, file);
		return (file->error);
	}
	if ((file->error = convertion(head, file, tab)) < 1)
	{
		print_error(file);
		free_error(tab, file);
		return (file->error);
	}
	return (SUCCESS);
}

int		main(int ac, char **av)
{
	t_file		file;
	t_header	head;
	t_tab		tab;

	set_op_tab(&file);
	tab.no_prob = 0;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm <file.s>\n", 2);
		return (ERROR_USAGE);
	}
	if ((file.error = exec_process(&tab, &file, &head, av)) != SUCCESS)
		return (file.error);
	ft_printf("File [.cor] has been created\n");
	free_error(&tab, &file);
	return (SUCCESS);
}
