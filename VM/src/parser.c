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

void	print_file_parsing(t_parse_file *file)
{
	int i = -1;
	
	printf("nb_player : |%d|\n", file->nb_player);
	while (++i < file->nb_player)
	{
		printf("player |%s| : rank %d\n", file->file_name[i], file->rank_player[i]);
	}
}

int 	init_usage(t_parse_file *file)
{
	file->i = 0;
	file->dump = -1;
	file->long_dump = -1;
	file->n = 0;
	file->visu = 0;
	file->nb_player = 0;
	file->rk_player = 1;
	file->cycles = -1;
	file->sv = -1;
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

int 	flag_is_verbose(t_parse_file *file, int ac, char **av)
{
	int 	mod;
	int 	i;
	int 	j;

	
		file->sv = ft_atoi(av[file->i + 1]);
		ft_bzero(&file->verbose, 5);
		i = 0;
		if ((file->sv < 32) && (file->i + 1 < ac && (file->sv > 0 || (file->sv == 0 && !ft_strcmp("0", av[file->i + 1])))))
		{
			mod = 16;
			while (file->sv != 0)
			{
				if (file->sv >= mod && mod <= 31)
				{
					j = 0;
					file->sv = file->sv - mod;
					file->verbose[i] = 1;
					i++;
				}
				else if (mod >= 0)
				{
					mod /= 2;
					j++;
				}
				if (j > 1)
					i++;
			}
			file->i++;
			file->sv = 1;
			return (SUCCESS);
		}
		else
			return (ERROR_USAGE);
}

int 	flag_is_cycles(t_parse_file *file, int ac, char **av)
{
	file->cycles = ft_atoi(av[file->i + 1]);
	if ((file->i + 1 < ac && (file->cycles > 0 || (file->cycles == 0 && !ft_strcmp("0", av[file->i + 1])))))
	{
		file->i++;
		printf("GAYYYY\n");
		return (SUCCESS);
	}
	else
		return (ERROR_USAGE);
}

int 	check_argument(t_parse_file *file, int ac, char **av)
{
	if ((file->error = init_usage(file)) < 0)
		return (file->error);
	while (++file->i < ac)
	{
		if ((file->error = flag_is_dump(file, ac, av)) < 0)
			return (file->error);
		else if (file->i + 1 < ac && (!ft_strcmp("-v", av[file->i])))
		{
			if (((file->error = flag_is_verbose(file, ac, av)) < 0))
				return (file->error);
		}
		else if (file->i + 1 < ac && (!ft_strcmp("-c", av[file->i])))
		{
			if (((file->error = flag_is_cycles(file, ac, av)) < 0))
				return (file->error);
		}
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
		else if ((!ft_strcmp("-visu", av[file->i]) && file->visu == 0))
			file->visu = 1;
		else if (file->error < 0)
			return (ERROR_USAGE);
	}
	return (SUCCESS);
}
