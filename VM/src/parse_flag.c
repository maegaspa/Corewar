/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:52:17 by hmichel           #+#    #+#             */
/*   Updated: 2020/06/03 16:52:19 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		flag_is_verbose(t_parse_file *file, int ac, char **av)
{
	file->sv = ft_atoi(av[file->i + 1]);
	if ((file->sv < 32) && (file->i + 1 < ac &&
		(file->sv > 0 || (file->sv == 0 && !ft_strcmp("0", av[file->i + 1])))))
	{
		check_n_verbose(file);
		file->i++;
		file->sv = 1;
		return (SUCCESS);
	}
	else
		return (ERROR_USAGE);
}

int		flag_is_cycles(t_parse_file *file, int ac, char **av)
{
	file->cycles = ft_atoi(av[file->i + 1]);
	if ((file->i + 1 < ac && (file->cycles > 0 ||
		(file->cycles == 0 && !ft_strcmp("0", av[file->i + 1])))))
	{
		file->i++;
		return (SUCCESS);
	}
	else
		return (ERROR_USAGE);
}

int		flag_is_n(t_parse_file *file, int ac, char **av)
{
	file->n = ft_atoi(av[file->i + 1]);
	if ((file->i + 1 < ac && (file->n > 0 || (file->n == 0 &&
		!ft_strcmp("0", av[file->i + 1])))) && (file->i + 2 < ac &&
		is_file_cor(file, av, 2)))
	{
		file->file_name[file->nb_player] = ft_strdup(av[file->i + 2]);
		file->rank_player[file->nb_player] = file->rk_player;
		if (MAX_PLAYERS && file->rk_player >= file->n)
		{
			file->j = -1;
			while (++file->j < file->nb_player)
				if (file->rank_player[file->j] == file->n)
					ft_swap(&file->rank_player[file->j],
						&file->rank_player[file->nb_player]);
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

int		flag_is_dump(t_parse_file *file, int ac, char **av)
{
	if (file->i + 1 < ac && (file->dump == -1) &&
		(!ft_strcmp("-dump", av[file->i]) || !ft_strcmp("-d", av[file->i])))
	{
		file->dump = ft_atoi(av[file->i + 1]);
		if (file->i + 1 < ac && (file->dump > 0 ||
			(file->dump == 0 && !ft_strcmp("0", av[file->i + 1]))))
			file->i += 2;
		else
			return (ERROR_USAGE);
	}
	else if (file->i + 1 < ac && (file->long_dump == -1) &&
	(!ft_strcmp("-dump-long", av[file->i]) || !ft_strcmp("-dl", av[file->i])))
	{
		file->long_dump = ft_atoi(av[file->i + 1]);
		if (file->i + 1 < ac && (file->long_dump > 0 ||
		(file->long_dump == 0 && !ft_strcmp("0", av[file->i + 1]))))
			file->i += 2;
		else
			return (ERROR_USAGE);
	}
	return (SUCCESS);
}
