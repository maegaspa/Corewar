/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seanseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 12:42:44 by seanseau          #+#    #+#             */
/*   Updated: 2020/03/09 19:20:34 by seanseau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			get_valid_name(t_war *war)
{
	int i;
	int pos;
	int j;

	i = -1;
	while (++i < war->nb_player)
	{
		j = -1;
		while (++j < (int)ft_strlen(war->player[i].file_name))
			if (war->player[i].file_name[j] == '/')
				pos = j + 1;
		war->player[i].real_name = ft_strdup(pos + war->player[i].file_name);
	}
}
