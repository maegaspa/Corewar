#include "../includes/asm.h"
#include <stdio.h>

void 	init_struct_file(t_file *file)
{
	file->name = 0;
	file->comment = 0;
	file->count = -1;
	file->error = 0;
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
	return (SUCCES);
}