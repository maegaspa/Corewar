/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:56 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:33 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	swap_char(unsigned char *a, unsigned char *b)
{
	unsigned char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		swap_2(unsigned short int *nb)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)nb;
	swap_char(tmp, tmp + 1);
}

void		swap_4(unsigned int *nb)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)nb;
	swap_char(tmp, tmp + 3);
	swap_char(tmp + 1, tmp + 2);
}

int			check_errors(char *str, char *base)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	while (str[start] != '\0' && (str[start] == ' ' || str[start] == '\t'))
		start++;
	i = start;
	while (str[i])
	{
		j = 0;
		while (base[j] && (str[i] != base[j] ||
					(str[i] == '-' || str[i] == '+')))
			++j;
		if (str[i] != base[j] && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int			check_label(t_tab *tab, char *str)
{
	int	i;

	i = -1;
	while (++i < tab->nb_instruction)
		if (tab->info_ins[i].label)
			if (!ft_strcmp(tab->info_ins[i].label, str))
				return (SUCCESS);
	return (ERROR_LABEL);
}
