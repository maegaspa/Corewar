/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:11:04 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:11:35 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../libft/includes/ft_printf.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_parameter
{
	int		reg;
	int		is_direct;
	int		direct;
	char	*direct_str;
	int		is_indirect;
	int		indirect;
	char	*indirect_str;
	int		type_param;
}				t_parameter;

typedef struct	s_instruction
{
	char				*instruction;
	int					id_inst;
	char				**parameter;
	int					nb_parameter;
	char				*label;
	struct s_parameter	*param;
	int					line_error;
}				t_instruction;

typedef struct	s_tab
{
	struct s_instruction	*info_ins;
	int						nb_instruction;
	int						*n_label;
	int						tabyte[CHAMP_MAX_SIZE];
	int						*dir_pos;
	int						*r_pos;
	char					**label_name;
	int						no_prob;
}				t_tab;

typedef struct	s_file
{
	t_op			op[17];
	struct s_tab	*tab;
	unsigned char	op_c;
	char			tmp[2];
	char			*file_name;
	char			**file;
	int				name;
	int				ligne_name;
	int				comment;
	int				ligne_comment;
	int				count;
	int				error;
	int				type;
	int				param_error;
	int				ligne_error;
	int				nb_instruction;
	int				free_cnt;
	int				free_cnt2;
	int				free_cnt3;
	char			**split;
	int				cnt_tab;
	int				cnt_split;
	int				cnt_inst;
	int				fd;
	int				len1;
	int				len2;
	int				len;
	int				i;
	int				j;
	int				k;
	int				i_temp;
	unsigned int	n;
	int				max_byte;
	int				n_param;
	int				f;
}				t_file;

# define MAX_LABEL 50
# define FREE 2
# define SUCCESS 1
# define ERROR_MALLOC 0
# define ERROR_INSTRUCT -1
# define ERROR_CHAR -2
# define ERROR_PARAM -3
# define ERROR_LABEL -4
# define ERROR_EMPTY -5
# define ERROR_DOT_S -6
# define ERROR_INFO -7
# define ERROR_MEMORY -8
# define ERROR_NOINST -9
# define ERROR_USAGE -10
# define ERROR_WRITE -11
# define ERROR_COMMENT -12
# define ERROR_OPEN -13
# define FAILURE -14
# define ERROR_PARAM_C -15
# define TOO_BIG -16
# define ERROR_TYPE_PARAM -17

/*
** PARSING FUNCTIONS
*/

void			delete_hash(t_file *file);
int				lexer_check_instruction(t_file *file, t_tab *tab);
char			**get_file(char *filename);
void			*ft_realloc(void *old, size_t old_size, size_t new_size);
char			*strndup(const char *s, size_t n);
int				is_name_or_comment(char *str, int chose);
void			init_struct_file(t_file *file, t_header *head);
int				true_syntaxe_info(t_header *head, char *str, int select,
				int chose);
int				lexer(t_tab *ins_tab, t_file *file);
int				read_instruction(t_file *file);
int				is_instruction(char *str);
int				init_instruction_tab(t_tab *ins_tab, t_file *file);
char			**ft_strsplitwsp(char const *s, t_file *file);
void			free_split(t_file *file);
int				is_label(char *str);
int				is_instruction_name(char *str, t_file *file, t_tab *tab);
void			set_op_tab(t_file *file);
int				is_label_or_instruction(t_tab *tab, t_file *file);
int				check_param(t_tab *tab, t_file *file);
char			**ft_strsplit2(char const *s);
void			free_error(t_tab *tab, t_file *file, int error);
void			print_line_error(t_file *file);
void			print_error(t_file *file);
void			print_error2(t_file *file);
void			print_error3(t_file *file);
int				file_check(t_file *file, t_header *head, char *file_name);
int				ft_atoi_base(char *str, char *base);
int				init_param(t_tab *tab);
int				lexer_param(t_file *file, t_tab *tab, char *str);
int				ft_check_type(int d_type, int type);
int				define_param(t_tab *tab, t_file *file);
int				check_label(t_tab *tab, char *str);
void			swap_4(unsigned int *nb);
void			swap_2(unsigned short int *nb);
char			*gettohexa(int n);
int				check_errors(char *str, char *base);
int				get_nb(char c, char *base);
t_op			get_op_by_name(t_file *file, char *name);

/*
** WRITE FUNCTIONS
*/

void			get_label_pos2(t_tab *tab, t_file *file);
void			get_label_pos_bis(t_tab *tab, t_file *file);
void			utils_reg_dir_ind(t_file *file, t_tab *tab, int i, int n);
void			free_tab(t_tab *tab, t_file *file, int error);
int				ft_atoi_bis(char const *str);
char			*add_cor(char *str);
int				create_cor(t_header *head, t_file *file, t_tab *tab);
int				convertion(t_header *head, t_file *file, t_tab *tab);
int				which_direct(t_tab *tab, int actual_inst);
int				get_label_init(t_tab *tab);
int				get_label_pos(t_tab *tab, t_file *file);
void			convert_int(unsigned char **str, int nb);
void			write_binary_int(int nb, int fd);
int				get_dir_pos(t_tab *tab, t_file *file);
int				write_dir_int(int n, t_file *file, t_tab *tab,
				int actual_inst);
int				write_short(int n_param, t_file *file, t_tab *tab,
				int actual_inst);
int				write_reg_dir_ind(t_file *file, t_tab *tab, int actual_inst);
void			stock_reg_dir(t_tab *tab, t_file *file, int n_param,
				int actual_inst);
int				write_param(t_file *file, t_tab *tab, int actual_inst);
void			param_fill(t_tab *tab, t_file *file);
void			param_fill_dir(t_tab *tab, t_file *file);
void			param_fill_dir2(t_tab *tab, t_file *file);
void			write_dir_int_lab(int n, t_file *file, t_tab *tab,
				int actual_inst);
void			write_dir_short_lab(int n, t_file *file, t_tab *tab,
				int act_inst);
int				write_header(t_header *head, int fd, t_file *file);

#endif
