#include "../includes/asm.h"
#include <stdio.h>

int 	init_param(t_tab *tab)
{
	int 	i;
	int 	j;

	i = -1;
	while (++i < tab->nb_instruction)
	{
		if (!(tab->info_ins[i].param = malloc(sizeof(t_parameter) * tab->info_ins[i].nb_parameter)))
			return (ERROR_MALLOC);
		j = -1;
		while (++j < tab->info_ins[i].nb_parameter)
		{
			tab->info_ins[i].param[j].registre = 0;
			tab->info_ins[i].param[j].direct_str = NULL;
			tab->info_ins[i].param[j].is_direct = 0;
			tab->info_ins[i].param[j].direct = 0;
			tab->info_ins[i].param[j].indirect_str = NULL;
			tab->info_ins[i].param[j].is_direct = 0;
			tab->info_ins[i].param[j].indirect = 0;
			tab->info_ins[i].param[j].type_param = -1;
		}
	}
	return (SUCCESS);
}

void 	init_struct_file(t_file *file, t_header *head)
{
	file->tmp[0] = LABEL_CHAR;
    file->tmp[1] = '\0';
	file->name = 0;
	file->comment = 0;
	file->count = -1;
	file->error = 0;
	//ft_bzero(&head, sizeof(t_header));
	head->magic = COREWAR_EXEC_MAGIC;
	swap_4(&head->magic);
	ft_bzero(&head->prog_name, PROG_NAME_LENGTH + 1);
	head->prog_size = file->max_byte;
	swap_4(&head->prog_size);
	ft_bzero(&head->comment, COMMENT_LENGTH + 1);
}

int 		init_instruction_tab(t_tab *tab, t_file *file)
{
	int i;

	i = -1;
	tab->nb_instruction = file->nb_instruction;
	if (!(tab->info_ins = malloc(sizeof(t_instruction) * tab->nb_instruction)))
		return (ERROR_MALLOC);
	while (++i < tab->nb_instruction)
		tab->info_ins[i].nb_parameter = 0;
	return (SUCCESS);
}