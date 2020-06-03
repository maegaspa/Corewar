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

int		check_flag(t_parse_file *file, int ac, char **av)
{
	if ((!ft_strcmp("-a", av[file->i])))
	{
		if (file->a == -1)
			file->a = 1;
		else
			return (ERROR_USAGE);
	}
	else if (file->i + 1 < ac && (!ft_strcmp("-v", av[file->i])) &&
			((file->error = flag_is_verbose(file, ac, av)) < 0))
		return (file->error);
	else if (file->i + 1 < ac && (!ft_strcmp("-c", av[file->i])) &&
			((file->error = flag_is_cycles(file, ac, av)) < 0))
		return (file->error);
	else if ((!ft_strcmp("-visu", av[file->i]) && file->visu == 0))
		file->visu = 1;
	else if (file->i + 1 < ac && (!ft_strcmp("-n", av[file->i]) &&
				file->nb_player <= MAX_PLAYERS) &&
			(file->error = flag_is_n(file, ac, av)) < 0)
		return (file->error);
	return (SUCCESS);
}

int		check_argument(t_parse_file *file, int ac, char **av)
{
	if (ac == 1)
		return (ERROR_USAGE);
	if ((file->error = init_usage(file)) < 0)
		return (file->error);
	while (++file->i < ac)
	{
		if ((file->error = flag_is_dump(file, ac, av)) < 0)
			return (file->error);
		else if ((file->error = check_flag(file, ac, av)) < 0)
			return (file->error);
		else if (file->nb_player < MAX_PLAYERS &&
			is_file_cor(file, av, 0) == SUCCESS)
		{
			file->file_name[file->nb_player] = ft_strdup(av[file->i]);
			file->rank_player[file->nb_player] = file->rk_player;
			file->rk_player++;
			file->nb_player++;
		}
		else if (file->error < 0)
			return (ERROR_USAGE);
	}
	if (file->nb_player < 1 || file->nb_player > 4)
		return (ERROR_USAGE);
	return (SUCCESS);
}
