/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:17:46 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 03:26:42 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdio.h>

# include "op.h"
# include "../../libft/includes/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <curses.h>
# include <ncurses.h>

# define C_POS					(chariot->pc + chariot->start_pos)
# define REG_TAB				(chariot->registres)
# define COREWAR				21499276478801162

# define ERROR_MALLOC			-1
# define ERROR_NB_PLAYER		-2
# define ERROR_USAGE			-3
# define ERROR_MAGIC			-4
# define ERROR_CHAMP_SIZE		-5
# define ERROR_OPEN				-6
# define ERROR_READ				-7
# define ERROR_NAME				-8
# define ERROR_COMMENT			-9

# define SUCCESS				1
# define FAILURE				0

# define T_DIR_TWO				2
# define T_DIR_FOUR				4

typedef struct			s_parse_file
{
	int					error;
	int					dump;
	int					long_dump;
	int					visu;
	int					n;
	int					sv;
	int					cycles;
	int					verbose[6];
	int					rank_player[MAX_PLAYERS];
	int					nb_player;
	int					rk_player;
	char				**file_name;
	int					arena_segment;
	int					a;
	int					i;
	int					j;
}						t_parse_file;

typedef struct			s_player
{
	int					pos_arena;
	int					fd;
	int					num;
	char				*file_name;
	char				*real_name;
	char				*comment;
	unsigned int		prog_size;
	struct s_header		header;
}						t_player;

typedef struct			s_chariot
{
	int					pc;
	int					live;
	int					carry;
	int					wait;
	int					start_pos;
	int					ope;
	int					registres[REG_NUMBER];
	int					index;
	int					last_live;
	int					prev_cursor;
	int					player;
	int					prev_color;
	struct s_chariot	*next;
}						t_chariot;

typedef struct			s_visual
{
	WINDOW				*arena_win;
	WINDOW				*infos_win;
	WINDOW				*keys_win;
	char				**arena_list;
	int					arena_cursor;
	int					pause;
	int					sleeptime;
	int					process_nb;
}						t_visual;

typedef struct			s_war
{
	int					i_ocp;
	int					nb_chariot;
	int					id_chariot;
	int					back_pc;
	int					visu;
	struct s_player		*player;
	int					nb_player;
	int					op_cycle[16];
	char				arena[MEM_SIZE];
	int					cycles;
	int					dump;
	int					rtype[3];
	int					param[3];
	int					lastlive;
	int					tmp;
	int					aff;
	int					is_live;
	int					status[4];
	char				ocp;
	int					jump;
	char				*ocxp;
	int					verbose[6];
	int					cycles_btw_check;
	int					cycle_to_die;
	int					check_cycles_to_die;
	int					cycle_last_check;
	int					nb_lives;
	int					next_check;
	t_chariot			*begin;
	t_visual			visual;
}						t_war;

typedef int				(*t_opp)(t_war *war, t_chariot *proc);

t_op					g_op_tab[16];

/*
** read_champs.c
*/

int						read_and_place_players(t_parse_file *file, t_war *war,
		t_header *head);

/*
** utils.c
*/
unsigned int			u_int_reverse_octet(unsigned int x);
int						print_arena(t_war *war, t_parse_file *file);
void					ft_init_war(t_parse_file file, t_war *war);
void					init_tab(t_opp *opp_tab);
int						ft_atoi_base(const char *str, int base);
char					*ft_itoa_base(int value, int base);
short					get_2_val(t_war *war, t_chariot *chariot, int i);
int						get_4_val(t_war *war, t_chariot *chariot, int i);
void					print_verbose_16(t_war *war, t_chariot *chariot,
		int size);
int						read_arena(t_war *war, int cell);
void					write_on_arena(t_war *war, int value, int start,
		int size);
void					section_status(t_war *war);
/*
** play_game.c
*/
int						ft_game(t_war *war, t_parse_file *file);
int						ft_game_visu(t_war *war);
int						ft_check_type(int d_type, int type);
int						choose_ope(t_war *war, t_chariot *chariot);
void					get_param(t_war *war, char *str);
int						get_bin_ocp(t_chariot *chariot, t_war *war);
int						get_all_param(t_chariot *chariot, t_war *war);
int						get_val(t_war *war, t_chariot *chariot, int i);

/*
** ft_process.c
*/
int						ft_start_chariot(t_war *war, t_chariot **begin,
		t_parse_file *file);
t_chariot				*ft_creat_chariot(int index, int pc, int start_pos,
		int player);

/*
** parse_usage.c
*/
int						check_argument(t_parse_file *file, int ac, char **av);
int						check_flag(t_parse_file *file, int ac, char **av);

/*
** parse_flag.c
*/
int						flag_is_dump(t_parse_file *file, int ac, char **av);
int						flag_is_n(t_parse_file *file, int ac, char **av);
int						flag_is_cycles(t_parse_file *file, int ac, char **av);
int						flag_is_verbose(t_parse_file *file, int ac, char **av);

/*
** utils_flags.c
*/
void					check_n_verbose(t_parse_file *file);
int						is_file_cor(t_parse_file *file, char **av, int i);

/*
** init.c
*/
int						init_usage(t_parse_file *file);

/*
** operande.c
*/

int						ft_get_op(t_war *war, t_chariot *chariot);
void					ft_exec_opp(t_chariot *chariot, t_war *war,
		t_opp *opp_tab);
int						calc_addr(int addr);

/*
** operande_2.c
*/

int						is_conform(unsigned char ocp, t_chariot *chariot,
		t_war *war);

/*
** test_function_tab
*/

int						live_fct(t_war *war, t_chariot *proc);
int						ld_fct(t_war *war, t_chariot *prc);
int						st_fct(t_war *war, t_chariot *prc);
int						add_fct(t_war *war, t_chariot *prc);
int						sub_fct(t_war *war, t_chariot *prc);
int						and_fct(t_war *war, t_chariot *prc);
int						or_fct(t_war *war, t_chariot *prc);
int						xor_fct(t_war *war, t_chariot *prc);
int						zjmp_fct(t_war *war, t_chariot *prc);
int						ldi_fct(t_war *war, t_chariot *prc);
int						sti_fct(t_war *war, t_chariot *prc);
int						fork_fct(t_war *war, t_chariot *prc);
int						lld_fct(t_war *war, t_chariot *prc);
int						lldi_fct(t_war *war, t_chariot *prc);
int						lfork_fct(t_war *war, t_chariot *prc);
int						aff_fct(t_war *war, t_chariot *prc);
int						get_size(unsigned char c, int use);
int						get_arg(t_war *war, t_chariot *prc,
		unsigned char *str);
int						get_hexa(unsigned char *str, int pc, int lenght);
int						print_in_arena(t_war *war, t_chariot *prc, int src,
		int dst);

/*
** error.c
*/

void					print_error(int error);

/*
** tous les visu.c
*/

void					print_cursor(t_war *war);
void					refresh_arena(t_war *war);
int						visu_body(t_war *war);
int						update_visu(t_war *war);
void					color_arena(t_war *war, int p, WINDOW *arena_win,
		char *arena);
void					get_keys(t_war *war);
void					get_valid_name(t_war *war);

/*
** verif_endgame.c
*/

int						verif_endgame(t_war *war, t_chariot *chariot);
int						check_cycle(t_war *war);
int						v_alive_chariot(t_chariot *chariot, t_war *war);
void					reset_lives_chariot(t_war *war);
void					verbose(t_war *war, t_chariot *chariot);
int						ft_load(t_war *war, int size, int adress);
void					delete_chariot(t_war *war, t_chariot *current);

/*
** jump.c
*/

int						ft_jump(t_war *war, t_chariot *chariot);

/*
** binary_op_carry.c
*/

void					verif_carry_and(t_chariot *chariot, int p1, int p2);
void					verif_carry_or(t_chariot *chariot, int p1, int p2);
void					verif_carry_xor(t_chariot *chariot, int p1, int p2);

#endif
