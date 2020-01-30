#include "../includes/corewar.h"
#include <stdio.h>

int 	check_argument(t_parse_file *file, int ac, char **av)
{
	int i;
	int j;

	i = 0;
	file->dump = -1;
	file->long_dump = -1;
	file->n = 0;
	file->nb_player = 0;
	file->rk_player = 0;
	if (!(file->file_name = malloc(sizeof(char*) * MAX_PLAYERS + 1)))
		return (ERROR_MALLOC);
	if (!(file->rank_player = malloc(sizeof(int) * MAX_PLAYERS)))
		return (ERROR_MALLOC);
	ft_bzero(&file->rank_player, MAX_PLAYERS);
	while (++i < ac)
	{
		printf("%s\n", av[i]);
		if ((file->dump == -1) && (!ft_strcmp("-dump", av[i]) || !ft_strcmp("-d", av[i])))
		{
			file->dump = ft_atoi(av[i + 1]);
			if (i + 1 < ac && (file->dump > 0 || (file->dump == 0 && !ft_strcmp("0", av[i + 1]))))
				i += 2;
			else
				return (ERROR_USAGE);
		}
		else if ((file->long_dump == -1) && (!ft_strcmp("-dump-long", av[i]) || !ft_strcmp("-dl", av[i])))
		{
			file->long_dump = ft_atoi(av[i + 1]);
			if (i + 1 < ac && (file->long_dump > 0 || (file->long_dump == 0 && !ft_strcmp("0", av[i + 1]))))
				i += 2;
			else
				return (ERROR_USAGE);
		}
		else if (!ft_strcmp("-n", av[i]) && file->nb_player <= MAX_PLAYERS)
		{
			file->n = ft_atoi(av[i + 1]);
			if (i + 1 < ac && (file->n > 0 || (file->n == 0 && !ft_strcmp("0", av[i + 1]))))
			{
				if (i + 2 < ac && ((av[i + 2][ft_strlen(av[i + 2]) - 4] == '.') && (av[i + 2][ft_strlen(av[i + 2]) - 3] == 'c') && (av[i + 2][ft_strlen(av[i + 2]) - 2] == 'o') && (av[i + 2][ft_strlen(av[i + 2]) - 1] == 'r')))
				{
					file->file_name[file->nb_player] = ft_strdup(av[i + 2]);
					file->rank_player[file->nb_player] = file->n;
					if (file->rk_player <= file->n)
					{
						j = -1;
						while (++j < (MAX_PLAYERS && file->n))
							if (file->rank_player[j] == file->rk_player)
								ft_swap(&file->rank_player[j], &file->rank_player[file->nb_player]);
					}
					file->nb_player++;
					i += 3;
				}
				else
					return (ERROR_USAGE);
			}
			else
				return (ERROR_USAGE);
		}
		else if (file->nb_player <= MAX_PLAYERS && ((av[i][ft_strlen(av[i]) - 4] == '.') && (av[i][ft_strlen(av[i]) - 3] == 'c') && (av[i][ft_strlen(av[i]) - 2] == 'o') && (av[i][ft_strlen(av[i]) - 1] == 'r')))
		{
			file->file_name[file->nb_player] = ft_strdup(av[i]);
			file->rank_player[file->nb_player] = file->rk_player;
			file->rk_player++;
		}
		else
			return (ERROR_USAGE);
	}
	i = -1;
	while (++i < MAX_PLAYERS)
		printf("[%d]", file->rank_player[i]);
	return (SUCCESS);
}

int 	main(int ac, char **av)
{
	t_parse_file file;

	if ((file.error = check_argument(&file, ac, av)) < 0)
	{
		printf("ERROR\n");
		return (file.error);
	}
	return (0);
}