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

typedef struct		s_proc
{
	int				key;
	int				pc;
	int				live;
	int				carry;
	int				wait;
	int				rdy;
	int				registres[REG_NUMBER];
	struct s_proc	*prev;
	struct s_proc	*next;
}					t_process;

typedef struct		war
{
	struct			s_player *player;
	int				nb_player;
	char			arena[MEM_SIZE];
	int				to_die;
	int				cycles;
	int				pc;
	int				dump;
	t_process		*procs;
}					t_war;

typedef int			(*t_test)(t_war *war, t_process *proc);

/*
** read_champs.c
*/
int					read_and_place_players(t_parse_file *file, t_war *war, t_header *head);

/*
** utils.c
*/
unsigned int		u_int_reverse_octet(unsigned int x);
void				print_arena(t_war *war);

/*
**play_game.c
*/
int					play_game(t_war *war);


/*
**test_function_tab
*/
int					live_fct(t_war *war, t_process *proc);
int				ld_fct(t_war *war, t_process *prc);
int				st_fct(t_war *war, t_process *prc);
int				add_fct(t_war *war, t_process *prc);
int				sub_fct(t_war *war, t_process *prc);
int				and_fct(t_war *war, t_process *prc);
int				or_fct(t_war *war, t_process *prc);
int				xor_fct(t_war *war, t_process *prc);
int				zjmp_fct(t_war *war, t_process *prc);
int				ldi_fct(t_war *war, t_process *prc);
int				sti_fct(t_war *war, t_process *prc);
int				fork_fct(t_war *war, t_process *prc);
int				lld_fct(t_war *war, t_process *prc);
int				lldi_fct(t_war *war, t_process *prc);
int				lfork_fct(t_war *war, t_process *prc);
int				aff_fct(t_war *war, t_process *prc);
int				get_size(unsigned char c, int use);
int				get_arg(t_war *war, t_process *prc, unsigned char *str);
int				get_hexa(unsigned char *str, int pc, int lenght);
int				print_in_arena(t_war *war, t_process *prc, int src, int dst);

#endif
