#ifndef ASM_H
# define ASM_H

# include "../libft/includes/ft_printf.h"

typedef struct s_description
{
	char	*name;
	char	*comment;
}				t_description;

typedef struct s_info_label
{
	char	*instruction;
	char	**parameter;
	int 	nb_parameter;
	int 	nb_instruction;
}				t_info_label;

typedef struct s_label_tab
{
	struct s_info_label **info_label;
	int 				nb_label;
	char 				*label;
}				t_label_tab;

#define SUCCES 1
#define ERROR_MALLOC 0
#define ERROR_INSTRUCT -1
#define ERROR_CHAR -2
#define ERROR_PARAM -3
#define ERROR_LABEL -4
#define ERROR_EMPTY -5
#define ERROR_DOT_S -6
#define ERROR_INFO -7
#define ERROR_MEMORY -8

#endif