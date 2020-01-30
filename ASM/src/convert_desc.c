/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_head.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: maegaspa <maegaspa@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 03:08:59 by maegaspa     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 03:08:59 by maegaspa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"
#include <stdio.h>


void	convert_int(unsigned char **str, int nb)
{
	(*str)[0] = (nb >> 24) & 0xFF;
	(*str)[1] = (nb >> 16) & 0xFF;
	(*str)[2] = (nb >> 8) & 0xFF;
	(*str)[3] = nb & 0xFF;
}

void	write_binary_int(int nb, int fd)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	convert_int(&str, nb);
	write(fd, str, 4);
	free(str);
}

char	*add_cor(char *str)
{
	char	*new_name;
	int		i;

	i = ft_strlen(str);
	new_name = ft_strnew(ft_strlen(str) + 4);
	ft_strcat(new_name, str);
	ft_strdel(&str);
	if (new_name[i - 1] == '.')
	{
		new_name[i] = 'c';
		new_name[i + 1] = 'o';
		new_name[i + 2] = 'r';
	}
	return (new_name);
}

int		create_cor(t_header *head, t_file *file)
{
	file->file_name = add_cor(file->file_name);
	printf("%s\n", file->file_name);
	file->fd = open(file->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (write(file->fd, &(*head), sizeof(t_header)) != sizeof(t_header))
		return (ERROR_WRITE);
	return (SUCCESS);
}

int 	convertion(t_header *head, t_file *file)
{
	if ((file->error = create_cor(head, file)) < 1)
		return (file->error);
	return (SUCCESS);
}