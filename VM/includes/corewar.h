#ifndef COREWAR_H
# define COREWAR_H

#include "../../ASM/includes/asm.h"

typedef struct s_parse_file
{
	int				error;
	int				dump;
	int				long_dump;
	int				n;
	int				*rank_player;
	int				nb_player;
	int				rk_player;
	char			**file_name;
	int				arena_segment;
	int				i;
	int				j;
}					t_parse_file;

typedef struct s_player
{
	int				pos_arena;
	int				fd;
	int				num;
	char			*file_name;
	char			*comment;
	unsigned int	prog_size;
}					t_player;

typedef struct		war
{
	struct			s_player *player;
	int				nb_player;
	char			arena[MEM_SIZE];
}					t_war;

/*
** read_champs.c
*/
int					ft_read_player_code(t_parse_file *file, t_war *war, t_header *head);

/*
** utils.c
*/
unsigned int		u_int_reverse_octet(unsigned int x);
void				print_arena(t_war *war);

#endif
