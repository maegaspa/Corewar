#include "../includes/asm.h"
#include <stdio.h>

int 	read_instruction(t_file *file)
{
	int i;

	file->count = -1;
	file->nb_instruction = 0;
	while (file->file[++file->count])
	{
		i = 0;
		while (file->file[file->count][i] == ' ' || file->file[file->count][i] == '\t')
			i++;
		if (file->file[file->count][i] == COMMENT_CHAR)
				file->count++;
		if (is_instruction(file->file[file->count]) == SUCCESS)
			file->nb_instruction++;
	}
	file->ligne_error = file->count;
	if (file->nb_instruction == 2)
		return (ERROR_NOINST);
	file->nb_instruction -= 2;
	return (SUCCESS);
}

int 	is_label_or_instruction(t_tab *tab, t_file *file)
{
	file->free_cnt = 0;
	file->cnt_split = 0;
	file->cnt_inst = 0;
	file->split = ft_strsplitwsp(file->file[file->count], file);
	if (is_label(file->split[file->cnt_split]) == SUCCESS)
	{
		tab->info_ins[file->cnt_tab].label = strndup(file->split[file->cnt_split], (ft_strlen(file->split[file->cnt_split]) - 1));
		file->cnt_split++;
	}
	else if ((file->error = is_label(file->split[file->cnt_split])) < 1 && file->error != FAILURE)
		return (file->error);
	if (is_instruction_name(file->split[file->cnt_split], file, tab) == SUCCESS)
	{
		tab->info_ins[file->cnt_tab].instruction = strndup(file->split[file->cnt_split], (ft_strlen(file->split[file->cnt_split])));
		file->cnt_inst = 1;
	}
	if ((!file->cnt_split && !file->cnt_inst) || !file->cnt_inst)
		return (ERROR_INSTRUCT);
	if (file->cnt_split)
		file->len = file->len2 - 1;
	else
		file->len = file->len1 - 1;
	free_split(file);
	return (SUCCESS);
}

int 	check_param(t_tab *tab, t_file *file)
{
	int i;
	int j;

	file->param_error = 0;
	i = -1;
	while (file->file[file->count][++i])
		if (file->file[file->count][i] == SEPARATOR_CHAR)
			file->param_error++;
	tab->info_ins[file->cnt_tab].parameter =
		ft_strsplit2(&file->file[file->count][++file->len]);
	i = -1;
	j = 0;
	while (tab->info_ins[file->cnt_tab].parameter[++i])
	{
		if (tab->info_ins[file->cnt_tab].parameter[i][0] == COMMENT_CHAR)
		{
			tab->info_ins[file->cnt_tab].nb_parameter = i;
			j = 1;
		}
		if (j == 1)
			ft_strdel(&tab->info_ins[file->cnt_tab].parameter[i]);
	}
	if (j != 1)
		tab->info_ins[file->cnt_tab].nb_parameter = i;
	if ((tab->info_ins[file->cnt_tab].nb_parameter !=
		file->op[tab->info_ins[file->cnt_tab].id_inst - 1].nb_params)
		|| (file->param_error + 1 != tab->info_ins[file->cnt_tab].nb_parameter))
		return (ERROR_PARAM);
	return (SUCCESS);
}

int 	lexer_analysis(t_tab *tab, t_file *file)
{
	int i;

	file->count = -1;
	file->cnt_tab = 0;
	while (file->file[++file->count])
	{
		i = 0;
		while (file->file[file->count][i] == ' ' || file->file[file->count][i] == '\t')
				i++;
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
	}
	return (SUCCESS);
}


int 	lexer(t_tab *tab, t_file *file)
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

int 	main(int ac, char **av)
{
	t_file file;
	t_header head;
	t_tab tab;

	set_op_tab(&file);
	tab.no_prob = 0;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm <file.s>\n", 2);
		return (ERROR_USAGE);
	}
	if ((file.error = file_check(&file, &head, av[1])) < 1)
	{
		print_error(&file);
		free_error(&tab, &file);
		return (file.error);
	}
	if ((file.error = lexer(&tab, &file)) < 1)
	{
		print_error(&file);
		free_error(&tab, &file);
		return (file.error);
	}
	if ((file.error = convertion(&head, &file, &tab)) < 1)
	{
		print_error(&file);
		free_error(&tab, &file);
		return (file.error);
	}
	//ft_printf("File is create\n");
	free_error(&tab, &file);
	return (SUCCESS);
}