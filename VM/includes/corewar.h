/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:17:46 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/28 18:27:09 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdio.h>

//#include "../../ASM/includes/asm.h"
# include "op.h"
# include "../../libft/includes/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>

# define ERROR_MALLOC -1
# define ERROR_NB_PLAYER -2
# define ERROR_USAGE -3
# define ERROR_MAGIC -4
# define ERROR_CHAMP_SIZE -5
# define ERROR_OPEN -6
# define ERROR_READ -7

# define SUCCESS 1
# define FAILURE 0

# define T_DIR_TWO 2
# define T_DIR_FOUR 4

typedef struct 			s_parse_file
{
	int					error;
	int					dump;
	int					long_dump;
	int 				visu;
	int					n;
	int					*rank_player;
	int					nb_player;
	int					rk_player;
	char				**file_name;
	int					arena_segment;
	int					i;
	int					j;
}						t_parse_file;

typedef struct			s_player
{
	int					pos_arena;
	int					fd;
	int					num;
	char				*file_name;
	struct				s_header header;
}						t_player;

typedef struct			s_chariot
{
	int					pc;
	int					live;
	int					carry;
	int					wait;
	int					start_pos;
	int					ope;
	int					registres[REG_NUMBER]; //char?
	int					index;
	struct s_chariot	*next;
}						t_chariot;

typedef struct			war
{
	struct				s_player *player;
	int					nb_player;
	int					op_cycle[16];
	char				arena[MEM_SIZE];
	int					to_die;
	int					cycles;
	int					dump;
	t_chariot			**begin;
}						t_war;

typedef int			(*t_opp)(t_war *war, t_chariot *proc);

t_op		g_op_tab[16];

/*
** read_champs.c
*/
int					read_and_place_players(t_parse_file *file, t_war *war, t_header *head);

/*
** utils.c
*/
unsigned int		u_int_reverse_octet(unsigned int x);
int					print_arena(t_war *war, t_parse_file *file);
void				ft_init_war(t_parse_file file, t_war *war);
void				init_tab(t_opp *opp_tab);

/*
** play_game.c
*/
int					ft_game(t_war *war);

/*
** ft_process1.c
*/
int					ft_start_chariot(t_war *war, t_chariot **begin);

/*
** parser.c
*/
int					check_argument(t_parse_file *file, int ac, char **av);

/*
** operande.c
*/
int					ft_get_op(t_war *war, t_chariot *chariot);
int					ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab);

/*
** test_function_tab
*/
int				live_fct(t_war *war, t_chariot *proc);
int				ld_fct(t_war *war, t_chariot *prc);
int				st_fct(t_war *war, t_chariot *prc);
int				add_fct(t_war *war, t_chariot *prc);
int				sub_fct(t_war *war, t_chariot *prc);
int				and_fct(t_war *war, t_chariot *prc);
int				or_fct(t_war *war, t_chariot *prc);
int				xor_fct(t_war *war, t_chariot *prc);
int				zjmp_fct(t_war *war, t_chariot *prc);
int				ldi_fct(t_war *war, t_chariot *prc);
int				sti_fct(t_war *war, t_chariot *prc);
int				fork_fct(t_war *war, t_chariot *prc);
int				lld_fct(t_war *war, t_chariot *prc);
int				lldi_fct(t_war *war, t_chariot *prc);
int				lfork_fct(t_war *war, t_chariot *prc);
int				aff_fct(t_war *war, t_chariot *prc);
int				get_size(unsigned char c, int use);
int				get_arg(t_war *war, t_chariot *prc, unsigned char *str);
int				get_hexa(unsigned char *str, int pc, int lenght);
int				print_in_arena(t_war *war, t_chariot *prc, int src, int dst);

/*
** debug.c
*/
void		ft_print_chariot(t_chariot *chariot, int reg);
void		ft_print_war(t_war *war);

/*
** error.c
*/
void 		print_error(int error);

#endif
