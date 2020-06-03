/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:47 by seanseau          #+#    #+#             */
/*   Updated: 2020/04/03 18:56:20 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			get_player_data(t_header *header, t_war *war, int player_nb)
{
	header->magic = u_int_reverse_octet(header->magic);
	if (header->magic != COREWAR_EXEC_MAGIC)
		return (ERROR_MAGIC);
	header->prog_size = u_int_reverse_octet(header->prog_size);
	if (header->prog_size > CHAMP_MAX_SIZE)
		return (ERROR_CHAMP_SIZE);
	war->player[player_nb].header = *header;
	return (SUCCESS);
}

int			add_player_to_arena(t_war *war, int player_nb,
	char *file_buff, t_header *header)
{
	ft_memcpy(&war->arena[war->player[player_nb].pos_arena],
		&file_buff[sizeof(*header)], war->player[player_nb].header.prog_size);
	return (SUCCESS);
}

int			get_new_player(t_war *war, t_parse_file *file, t_header *header,
		int nb)
{
	char buff[MEM_SIZE + 1];

	ft_bzero(&buff, MEM_SIZE);
	if (!(war->player[nb].file_name = ft_strdup(file->file_name[nb])))
		return (ERROR_MALLOC);
	if ((war->player[nb].fd = open(war->player[nb].file_name, O_RDONLY)) < 0)
		return (ERROR_OPEN);
	war->player[nb].pos_arena = file->arena_segment * nb;
	war->player[nb].num = nb;
	if (!(read(war->player[nb].fd, &buff, MEM_SIZE)))
		return (ERROR_READ);
	ft_memcpy(header, buff, sizeof(*header));
	if ((file->error = get_player_data(header, war, nb)) < 1)
		return (file->error);
	if ((file->error = add_player_to_arena(war, nb, buff, header) < 1))
		return (file->error);
	if (close(war->player[nb].fd) < 0)
		return (ERROR_OPEN);
	return (SUCCESS);
}

void		print_info_players(t_war *war, t_parse_file *file)
{
	int i;
	int j;
	int max;

	j = -1;
	max = -1;
	while (++j < file->nb_player)
	{
		i = -1;
		while (++i < file->nb_player)
			if (max < file->rank_player[i])
				max = file->rank_player[i];
	}
	i = -1;
	while (++i <= max + 1)
	{
		j = -1;
		while (++j < file->nb_player)
			if (i == file->rank_player[j] - 1)
				printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				file->rank_player[j], war->player[j].header.prog_size,
				war->player[j].header.prog_name, war->player[j].header.comment);
	}
}

int			read_and_place_players(t_parse_file *file, t_war *war,
		t_header *head)
{
	int		act_player;

	act_player = -1;
	if (!(war->player = malloc(sizeof(t_player) * file->nb_player)))
		return (ERROR_MALLOC);
	file->arena_segment = MEM_SIZE / file->nb_player;
	ft_bzero(war->arena, MEM_SIZE);
	while (++act_player < file->nb_player)
		if ((file->error = get_new_player(war, file, head, act_player)) < 1)
			return (file->error);
	printf("Introducing contestants...\n");
	print_info_players(war, file);
	return (SUCCESS);
}
