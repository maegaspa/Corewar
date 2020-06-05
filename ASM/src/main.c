/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:09:06 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:32 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		lexer_analysis(t_tab *tab, t_file *file)
{
	int i;

	file->count = -1;
	file->cnt_tab = 0;
	file->ligne_error = 0;
	while (file->file[++file->count])
	{
		i = 0;
		while (file->file[file->count][i] == ' '
				|| file->file[file->count][i] == '\t')
			i++;
		if (file->file[file->count][i] == COMMENT_CHAR)
			file->count++;
		else if ((file->error = lexer_check_instruction(file, tab)) < 0)
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
	{
		print_error(file);
		free_error(tab, file, file->error);
		return (file->error);
	}
	if ((file->error = init_param(tab)) < 1)
		return (file->error);
	if ((file->error = define_param(tab, file)) < 1)
	{
		print_error(file);
		free_error(tab, file, file->error);
		return (file->error);
	}
	return (SUCCESS);
}

int		main_fnct(t_tab *tab, t_file *file, t_header *head, char **av)
{
	if ((file->error = file_check(file, head, av[1])) < 1)
	{
		print_error(file);
		if (file->error != ERROR_DOT_S)
			free_error(tab, file, FAILURE);
		return (file->error);
	}
	if ((file->error = lexer(tab, file)) < 1)
	{
		return (file->error);
	}
	if ((file->error = convertion(head, file, tab)) < 1)
	{
		print_error(file);
		free_error(tab, file, TOO_BIG);
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
	if ((file.error = main_fnct(&tab, &file, &head, av)) < 0)
		return (file.error);
	ft_putstr("File [.cor] has been created\n");
	free_error(&tab, &file, FREE);
	return (SUCCESS);
}
