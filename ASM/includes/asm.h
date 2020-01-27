#ifndef ASM_H
# define ASM_H

# include "../../libft/includes/ft_printf.h"
# include "op.h"

typedef struct s_description
{
	char	*name;
	char	*comment;
	char 	*file_name;
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

typedef struct s_file
{
	char 	**file;
	int 	name;
	int 	comment;
	int 	count;
	int 	error;
}				t_file;

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
#define FAILURE -9

char	**get_file(char *filename);
void	*ft_realloc(void *old, size_t old_size, size_t new_size);
char	*strndup(const char *s, size_t n);
int 	is_name_or_comment(char *str, int chose);
void 	init_struct_file(t_file *file);
int 	true_syntaxe_info(t_description *desc, char *str, int select, int chose);

#endif