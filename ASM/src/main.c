#include "../includes/asm.h"
#include <stdio.h>

int 	read_instruction(t_file *file)
{
	file->count = -1;
	file->nb_instruction = 0;
	while (file->file[++file->count])
		if (is_instruction(file->file[file->count]) == SUCCES)
			file->nb_instruction++;
	file->ligne_error = file->count;
	if (file->nb_instruction == 2)
		return (ERROR_NOINST);
	file->nb_instruction -= 2;
	printf("nb_instruction [%d]\n", file->nb_instruction);
	return (SUCCES);
}

int 	is_label_or_instruction(t_tab *tab, t_file *file)
{
	printf("LIGNE [%d]: |%s|\n", file->count, file->file[file->count]);
	file->free_cnt = 0;
	file->cnt_split = 0;
	file->cnt_inst = 0;
	file->split = ft_strsplitwsp(file->file[file->count], file);
	if (is_label(file->split[file->cnt_split]) == SUCCES)
	{
		printf("%d\n", file->count);
		tab->info_ins[file->cnt_tab].label = strndup(file->split[file->cnt_split], (ft_strlen(file->split[file->cnt_split]) - 1));
		file->cnt_split++;
		printf("LABEL[%d] : [%s]\n", file->cnt_tab, tab->info_ins[file->cnt_tab].label);
	}
	else if ((file->error = is_label(file->split[file->cnt_split])) < 1 && file->error != FAILURE)
		return (file->error);
	if (is_instruction_name(file->split[file->cnt_split], file, tab) == SUCCES)
	{
		tab->info_ins[file->cnt_tab].instruction = strndup(file->split[file->cnt_split], (ft_strlen(file->split[file->cnt_split])));
		printf("INSTRUCTION[%d] : [%s]\n", file->cnt_tab, tab->info_ins[file->cnt_tab].instruction);
		file->cnt_inst = 1;
	}
	if ((!file->cnt_split && !file->cnt_inst) || !file->cnt_inst)
		return (ERROR_INSTRUCT);
	if (file->cnt_split)
		file->len = file->len2 - 1;
	else
		file->len = file->len1 - 1;
	printf("[%d]->(%c)|[%d]->(%c)\n", file->len1, file->file[file->count][file->len1], file->len2, file->file[file->count][file->len2]);
	free_split(file);
	return (SUCCES);
}

int 	check_param(t_tab *tab, t_file *file)
{
	int i;

	tab->info_ins[file->cnt_tab].parameter = ft_strsplit2(&file->file[file->count][++file->len]);
	printf("PARAM :");
	i = -1;
	while (tab->info_ins[file->cnt_tab].parameter[++i])
	{
		printf("[%s] ", tab->info_ins[file->cnt_tab].parameter[i]);
	}
	tab->info_ins[file->cnt_tab].nb_parameter = i;
	if (i != file->op[tab->info_ins[file->cnt_tab].id_inst - 1].nb_params)
		return (ERROR_PARAM);
	printf("\n[%d]\n", tab->info_ins[file->cnt_tab].nb_parameter);
	return (SUCCES);
}

int 	lexer_analysis(t_tab *tab, t_file *file)
{
	file->count = -1;
	file->cnt_tab = 0;
	while (file->file[++file->count])
	{
		if (is_instruction(file->file[file->count]) == SUCCES && file->ligne_name != file->count && file->ligne_comment != file->count)
		{
			file->ligne_error = file->count;
			if ((file->error = is_label_or_instruction(tab, file)) < 1)
				return (file->error);
			if ((file->error = check_param(tab, file)) < 1)
				return (file->error);
			printf("\n");
			file->cnt_tab++;
		}
	}
	return (SUCCES);
}

int 	lexer(t_tab *tab, t_file *file)
{
	if ((file->error = read_instruction(file)) < 1)
		return (file->error);
	if ((file->error = init_instruction_tab(tab, file)) < 1)
		return (file->error);
	if ((file->error = lexer_analysis(tab, file)) < 1)
		return (file->error);
	return (SUCCES);
}

int 	main(int ac, char **av)
{
	t_file file;
	t_description desc;
	t_tab tab;

	set_op_tab(&file);
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm <file.s>\n", 2);
		return (ERROR_USAGE);
	}
	if ((file.error = file_check(&file, &desc, av[1])) < 1)
	{
		print_error(&file);
		free_error(&tab, &file, &desc);
		return (file.error);
	}
	if ((file.error = lexer(&tab, &file)) < 1)
	{
		print_error(&file);
		free_error(&tab, &file, &desc);
		return (file.error);
	}
	print_error(&file);
	free_error(&tab, &file, &desc);
	return (SUCCES);
}