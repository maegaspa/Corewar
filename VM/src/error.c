/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:51:34 by hmichel           #+#    #+#             */
/*   Updated: 2020/06/03 16:51:49 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	print_usage(void)
{
	ft_putstr_fd("Usage: ./corewar [-a] [-c N] [-d N] [[-n number] ", 2);
	ft_putstr_fd("<champion1.cor> <...>]\n", 2);
	ft_putstr_fd("\t-a :\n\t\tPrints output from \"aff\" ", 2);
	ft_putstr_fd("(Default is to hide it)\n", 2);
	ft_putstr_fd("\t-d N, -dump N :\n\t\tDumps memory after N cycles ", 2);
	ft_putstr_fd("then exits x32\n", 2);
	ft_putstr_fd("\t-dl N, -dump-long N :\n\t\tDumps memory after N ", 2);
	ft_putstr_fd("cycles then exits x64\n", 2);
	ft_putstr_fd("\t-c N :\n\t\tRuns N cycles\n", 2);
	ft_putstr_fd("\t-v N :\n\t\tVerbosity levels, can be added together ", 2);
	ft_putstr_fd("to enable several\n", 2);
	ft_putstr_fd("\t\t\t- 1 : Show lives\n", 2);
	ft_putstr_fd("\t\t\t- 2 : Show cycles\n", 2);
	ft_putstr_fd("\t\t\t- 4 : Show operations ", 2);
	ft_putstr_fd("(Params are NOT litteral ...)\n", 2);
	ft_putstr_fd("\t\t\t- 8 : Show deaths\n", 2);
	ft_putstr_fd("\t\t\t- 16 : Show PC movements (Except for jumps)\n", 2);
	ft_putstr_fd("\t-n number champ :\n\t\tChange the order per N\n", 2);
}

void	print_error(int error)
{
	if (error == ERROR_MALLOC)
		ft_putstr_fd("ERROR: Malloc failed\n", 2);
	if (error == ERROR_NB_PLAYER)
		ft_putstr_fd("ERROR: Max players is 4\n", 2);
	if (error == ERROR_USAGE)
		print_usage();
	if (error == ERROR_MAGIC)
		ft_putstr_fd("ERROR: Wrong Magic number\n", 2);
	if (error == ERROR_CHAMP_SIZE)
		ft_putstr_fd("ERROR: Wrong prog_size (too big, MAX = 682 bytes)\n", 2);
	if (error == ERROR_OPEN)
		ft_putstr_fd("ERROR: Can't open file\n", 2);
	if (error == ERROR_READ)
		ft_putstr_fd("ERROR: Can't read file\n", 2);
	if (error == ERROR_NAME)
		ft_putstr_fd("ERROR: Wrong name\n", 2);
	if (error == ERROR_COMMENT)
		ft_putstr_fd("ERROR: Wrong comment\n", 2);
}
