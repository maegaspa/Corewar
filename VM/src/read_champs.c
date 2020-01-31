/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 12:28:39 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 18:34:03 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

int				get_player_data(t_header *header, t_war *war, int player_nb)
{
	if (!(war->player[player_nb].comment = ft_strdup(header->comment)))
		return (0);
	header->magic = u_int_reverse_octet(header->magic);
	//inverse les octets 4 et 1
	if (header->magic != COREWAR_EXEC_MAGIC)
	{
		printf("Wrong Magic\n");
		return (0);
	}
	header->prog_size = u_int_reverse_octet(header->prog_size);
	if (header->prog_size > CHAMP_MAX_SIZE)
	{
		printf("Wrong prog_size (too big)\n");
		return (0);
	}
	war->player[player_nb].prog_size = header->prog_size;
	return (1);
}

void			add_player_to_arena(t_war *war, int player_nb, char *file_buff)
{
	ft_memcpy(&war->arena[war->player[player_nb].pos_arena], &file_buff[16 +
		PROG_NAME_LENGTH + COMMENT_LENGTH], war->player[player_nb].prog_size);
}

int				get_new_player(t_war *war, t_parse_file *file, t_header *header,
		int nb)
{
	char buff[CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 20];

	errno = 0;
	if (!(war->player[nb].file_name = ft_strdup(file->file_name[nb])))
		return (0);
	if ((war->player[nb].fd = open(war->player[nb].file_name, O_RDONLY)) < 0)
	{
		printf("|%s|\n", strerror(errno));
		return (0);
	}
	war->player[nb].pos_arena = file->arena_segment * nb;
	war->player[nb].num = nb;
	if (!(read(war->player[nb].fd, &buff, CHAMP_MAX_SIZE + PROG_NAME_LENGTH +
					COMMENT_LENGTH + 20)))
		return (0);
	ft_memcpy(header, buff, sizeof(*header));
	if (!(get_player_data(header, war, nb)))
		return (0);
	add_player_to_arena(war, nb, buff);
	if (close(war->player[nb].fd) < 0)
		return (0);
	return (1);
}

int			ft_read_player_code(t_parse_file *file, t_war *war, t_header *head)
{
	int		act_player;

	act_player = -1;
	if (!(war->player = malloc(sizeof(t_player) * file->nb_player)))//alloue le nb de joueurs precise
		return (ERROR_MALLOC);
	file->arena_segment = MEM_SIZE / file->nb_player;//valeur du segment de l'arena entre chaque player
	while (++act_player < file->nb_player)
		get_new_player(war, file, head, act_player);//recupere les infos player + le place dans l'arena
	print_arena(war);//print vitef de l'arena -> ca marche
	printf("\nname 0 : |%s|\nComment :\t |%s|\nnum %d\npos_arena %d\nprog_size : %d\n\n", war->player[0].file_name, war->player[0].comment, war->player[0].num, war->player[0].pos_arena, war->player[0].prog_size);
	printf("name 1 : |%s|\nComment :\t |%s|\nnum %d\npos_arena %d\nprog_size : %d\n\n", war->player[1].file_name, war->player[1].comment, war->player[1].num, war->player[1].pos_arena, war->player[1].prog_size);
//	printf("name 2 : |%s|\nComment :\t |%s|\nnum %d\npos_arena %d\nprog_size : %d\n\n", war->player[2].file_name, war->player[2].comment, war->player[2].num, war->player[2].pos_arena, war->player[2].prog_size);
//	printf("name 3 : |%s|\nComment :\t |%s|\nnum %d\npos_arena %d\nprog_size : %d\n\n", war->player[3].file_name, war->player[3].comment, war->player[3].num, war->player[3].pos_arena, war->player[3].prog_size);
	return (1);
}
