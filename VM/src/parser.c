/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:28:30 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/26 18:37:48 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

int 	init_usage(t_parse_file *file)
{
	file->i = 0;
	file->dump = -1;
	file->long_dump = -1;
	file->n = 0;
	file->nb_player = 0;
	file->rk_player = 1;
	if (!(file->file_name = malloc(sizeof(char*) * MAX_PLAYERS + 1)))
		return (ERROR_MALLOC);
	if (!(file->rank_player = malloc(sizeof(int) * MAX_PLAYERS)))
		return (ERROR_MALLOC);
	return (SUCCESS);
}

int 	flag_is_dump(t_parse_file *file, int ac, char **av)
{
	if (file->i + 1 < ac && (file->dump == -1) && (!ft_strcmp("-dump", av[file->i]) || !ft_strcmp("-d", av[file->i])))
	{
		file->dump = ft_atoi(av[file->i + 1]);
		if (file->i + 1 < ac && (file->dump > 0 || (file->dump == 0 && !ft_strcmp("0", av[file->i + 1]))))
			file->i += 2;
		else
			return (ERROR_USAGE);
	}
	else if (file->i + 1 < ac && (file->long_dump == -1) && (!ft_strcmp("-dump-long", av[file->i]) || !ft_strcmp("-dl", av[file->i])))
	{
		file->long_dump = ft_atoi(av[file->i + 1]);
		if (file->i + 1 < ac && (file->long_dump > 0 || (file->long_dump == 0 && !ft_strcmp("0", av[file->i + 1]))))
			file->i += 2;
		else
			return (ERROR_USAGE);
	}
	return (SUCCESS);
}

int 	flag_is_n(t_parse_file *file, int ac, char **av)
{
	file->n = ft_atoi(av[file->i + 1]);
	if ((file->i + 1 < ac && (file->n > 0 || (file->n == 0 && !ft_strcmp("0", av[file->i + 1])))) && (file->i + 2 < ac && ((av[file->i + 2][ft_strlen(av[file->i + 2]) - 4] == '.') && (av[file->i + 2][ft_strlen(av[file->i + 2]) - 3] == 'c') && (av[file->i + 2][ft_strlen(av[file->i + 2]) - 2] == 'o') && (av[file->i + 2][ft_strlen(av[file->i + 2]) - 1] == 'r'))))
	{
		file->file_name[file->nb_player] = ft_strdup(av[file->i + 2]);
		file->rank_player[file->nb_player] = file->rk_player;
		if (MAX_PLAYERS && file->rk_player >= file->n)
		{
			file->j = -1;
			while (++file->j < file->nb_player)
				if (file->rank_player[file->j] == file->n)
					ft_swap(&file->rank_player[file->j], &file->rank_player[file->nb_player]);
			file->rk_player++;
		}
		else if (MAX_PLAYERS && file->rk_player < file->n)
			file->rank_player[file->nb_player] = file->n;
		file->nb_player++;
		file->i += 2;
	}
	else
		return (ERROR_USAGE);
	return (SUCCESS);
}

int 	check_argument(t_parse_file *file, int ac, char **av)
{
	if ((file->error = init_usage(file)) < 0)
		return (file->error);
	while (++file->i < ac)
	{
		printf("%s\n", av[file->i]);
		if ((file->error = flag_is_dump(file, ac, av)) < 0)
			return (file->error);
		else if (file->i + 1 < ac && (!ft_strcmp("-n", av[file->i]) && file->nb_player <= MAX_PLAYERS))
		{
			if ((file->error = flag_is_n(file, ac, av)) < 0)
				return (file->error);
		}
		else if (file->nb_player < MAX_PLAYERS && ((av[file->i][ft_strlen(av[file->i]) - 4] == '.') && (av[file->i][ft_strlen(av[file->i]) - 3] == 'c') && (av[file->i][ft_strlen(av[file->i]) - 2] == 'o') && (av[file->i][ft_strlen(av[file->i]) - 1] == 'r')))
		{
			file->file_name[file->nb_player] = ft_strdup(av[file->i]);
			file->rank_player[file->nb_player] = file->rk_player;
			file->rk_player++;
			file->nb_player++;
		}
		else
			return (ERROR_USAGE);
	}
	/*file->i = -1;
	while (++file->i < file->nb_player)
	{

	}*/
	file->i = -1;
	while (++file->i < file->nb_player)
		printf("[%s]->[%d] ", file->file_name[file->i], file->rank_player[file->i]);
	return (SUCCESS);
}

void	print_file_parsing(t_parse_file *file)
{
	int i = -1;
	
	printf("nb_player : |%d|\n", file->nb_player);
	while (++i < file->nb_player)
	{
		printf("player |%s| : rank %d\n", file->file_name[i], file->rank_player[i]);
	}
}
