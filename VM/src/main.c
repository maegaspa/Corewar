/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:56 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/27 00:36:41 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	free_all(t_war *war, t_parse_file *file)
{
	int i;

	i = -1;
	if (file->nb_player > 0)
	{
		while (++i < file->nb_player)
			ft_strdel(&(file->file_name[i]));
		free(file->file_name);
		if (war->nb_player > 0)
		{
			i = -1;
			while (++i < war->nb_player)
				ft_strdel(&war->player[i].file_name);
			free(war->player);
		}
	}
	else if (file->nb_player == 0)
		free(file->file_name);
}

int		free_return_print(int error, t_war *war, t_parse_file *file)
{
	print_error(error);
	free_all(war, file);
	return (error);
}

int		main(int ac, char **av)
{
	t_parse_file	file;
	t_war			war;
	t_header		head;

	if (ac >= 1 && (file.error = check_argument(&file, ac, av)) < 0)
		return (free_return_print(file.error, &war, &file));
	if ((file.error = read_and_place_players(&file, &war, &head)) < 0)
		return (free_return_print(file.error, &war, &file));
	ft_init_war(file, &war);
	if ((file.error = ft_game(&war, &file)) < 0)
		return (free_return_print(file.error, &war, &file));
	return (free_return_print(file.error, &war, &file));
}
