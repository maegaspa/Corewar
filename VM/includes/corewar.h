#ifndef COREWAR_H
# define COREWAR_H

#include "../../ASM/includes/asm.h"

typedef struct s_parse_file
{
	int 	error;
	int 	dump;
	int 	long_dump;
	int 	n;
	int 	*rank_player;
	int 	nb_player;
	int 	rk_player;
	char 	**file_name;
}				t_parse_file;

#endif