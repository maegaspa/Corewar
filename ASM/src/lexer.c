#include "../includes/asm.h"
#include <stdio.h>

int 		is_instruction_name(char *str, t_file *file, t_tab *tab)
{
	int 	i;

	i = -1;
	while (++i < 17)
		if (!ft_strcmp(file->op[i].name, str))
		{
			tab->info_ins[file->cnt_tab].id_inst = file->op[i].id;
			return (SUCCES);
		}
	return (FAILURE);
}

int 		is_label(char *str)
{
	int 	i;
	int 	j;
	unsigned int 	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		j = -1;
		if (str[i] == LABEL_CHAR)
		{
			if (count != ft_strlen(str) - 1)
				return (ERROR_LABEL);
			return (SUCCES);
		}
		while (LABEL_CHARS[++j])
			if (str[i] == LABEL_CHARS[j])
				count++;
	}
	return (FAILURE);
}

int 		is_instruction(char *str)
{
	int 	i;
	int 	j;

	i = -1;
	j = 0;
	if (!ft_strlen(str))
		return (FAILURE);
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			j++;
	if (j)
		return (SUCCES);
	return (FAILURE);
}

int 		is_name_or_comment(char *str, int chose)
{
	int 	i;

	i = 0;
	if (chose == 1)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!(ft_strncmp(&str[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))))
			return (SUCCES);
	}
	if (chose == 2)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!(ft_strncmp(&str[i], COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))))
			return (SUCCES);
	}
	return (0);
}

int 		true_syntaxe_info(t_description *desc, char *str, int select, int chose)
{
	int i;
	int count;
	int tmp;

	i = 0;
	count = 0;
	while (str[select] == ' ' || str[select] == '\t')
		select++;
	if (str[select] == '\"')
	{
		tmp = select;
		while (str[++select])
		{
			if (count > 1 && str[select] != ' ' && str[select] != '\t')
				return (ERROR_INFO);
			if (str[select] == '\"')
			{
				count++;
				if (count > 1)
					return (ERROR_CHAR);
			}
			if (count == 0)
				i++;
		}
		if (count == 0)
			return (ERROR_CHAR);
		if (chose == 1 && !(desc->name = ft_memalloc(i + 1)))
			return (ERROR_MALLOC);
		if (chose == 2 && !(desc->comment = ft_memalloc(i + 1)))
			return (ERROR_MALLOC);
		i = -1;
		while (str[++tmp] != '\"')
		{
			if (chose == 1)
				desc->name[++i] = str[tmp];
			if (chose == 2)
				desc->comment[++i] = str[tmp];
		}
		if (chose == 1)
				desc->name[++i] = '\0';
			if (chose == 2)
				desc->comment[++i] = '\0';
	}
	else
		return (ERROR_CHAR);
	return (SUCCES);
}