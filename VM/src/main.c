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
#include <stdio.h>

int 	main(int ac, char **av)
{
	t_parse_file	file;
	t_war			war;
	t_header		head;

	if (ac >= 1 && (file.error = check_argument(&file, ac, av)) < 0)
	{
		print_error(file.error);
		return (file.error);
	}
	if ((file.error = read_and_place_players(&file, &war, &head)) < 0)
	{
		print_error(file.error);
		return (file.error);
	}
	ft_init_war(file, &war);
	if (ft_game(&war, &file) == 0)//A FAIRE: retour erreur
		return (0);
	return (0);
}
