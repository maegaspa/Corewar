#include "../includes/corewar.h"

int		init_usage(t_parse_file *file)
{
	int i;

	i = -1;
	file->i = 0;
	file->dump = -1;
	file->long_dump = -1;
	file->n = 0;
	file->visu = 0;
	file->nb_player = 0;
	file->rk_player = 1;
	file->cycles = -1;
	file->sv = -1;
	file->a = -1;
	while (++i < 6)
		file->verbose[i] = 0;
	file->verbose[5] = 1;
	i = -1;
	while (++i < MAX_PLAYERS)
		file->rank_player[i] = 0;
	if (!(file->file_name = malloc(sizeof(char*) * MAX_PLAYERS + 1)))
		return (ERROR_MALLOC);
	return (SUCCESS);
}