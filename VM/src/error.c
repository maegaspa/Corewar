#include "../includes/corewar.h"
#include <stdio.h>

void 	print_error(int error)
{
	if (error == ERROR_MALLOC)
		ft_putstr_fd("ERROR: Malloc failed\n", 2);
	if (error == ERROR_NB_PLAYER)
		ft_putstr_fd("ERROR: Max players is 4\n", 2);
	if (error == ERROR_USAGE)
		ft_putstr_fd("Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor]\n", 2);
	if (error == ERROR_NB_PLAYER)
		ft_putstr_fd("ERROR: Max players is 4\n", 2);
	if (error == ERROR_MAGIC)
		ft_putstr_fd("ERROR: Wrong Magic number\n", 2);
	if (error == ERROR_CHAMP_SIZE)
		ft_putstr_fd("ERROR: Wrong prog_size (too big)\n", 2);
	if (error == ERROR_OPEN)
		ft_putstr_fd("ERROR: Can't open file\n", 2);
	if (error == ERROR_READ)
		ft_putstr_fd("ERROR: Can't read file\n", 2);
	if (error == ERROR_NAME)
    	ft_putstr_fd("ERROR: Wrong name\n", 2);
    if (error == ERROR_COMMENT)
        ft_putstr_fd("ERROR: Wrong comment\n", 2);
}