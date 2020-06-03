/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:52:28 by hmichel           #+#    #+#             */
/*   Updated: 2020/06/03 16:52:30 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		is_file_cor(t_parse_file *file, char **av, int i)
{
	if (ft_strlen(av[file->i + i]) > 4)
		if ((av[file->i + i][ft_strlen(av[file->i + i]) - 4] == '.') &&
			(av[file->i + i][ft_strlen(av[file->i + i]) - 3] == 'c') &&
			(av[file->i + i][ft_strlen(av[file->i + i]) - 2] == 'o') &&
			(av[file->i + i][ft_strlen(av[file->i + i]) - 1] == 'r'))
			return (SUCCESS);
	return (FAILURE);
}

void	check_n_verbose(t_parse_file *file)
{
	int		mod;
	int		i;
	int		j;

	j = 1;
	i = 0;
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
}
