/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:56 by seanseau          #+#    #+#             */
/*   Updated: 2020/02/25 21:26:51 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

int 	main(int ac, char **av)
{
	t_parse_file	file;
	t_war			war;
	t_header		head;
	int				error;

	error = 1;
	if (ac > 1 && (file.error = check_argument(&file, ac, av)) < 0)
	{
		printf("ERROR\n");
		return (file.error);
	}
//	print_file_parsing(&file);
	if (read_and_place_players(&file, &war, &head) == -1)
		return (-1);//free et close a la place
	ft_init_war(file, &war);
	if (ft_game(&war) == 0)//A FAIRE: retour erreur
		return (0);//end game (free/close)
	//free_zob
	//printf("ERROR\n");
	return (0);
}
