/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_desc.c                                   .::    .:/ .      .::   */
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

int 	write_name(t_description *desc, t_file *file)
{
	int 	i;
	int 	len;
	unsigned char 	*hex;
	char 	*nb;

	i = -1;
	len = PROG_NAME_LENGTH - ft_strlen(desc->name) + 2;
	while (desc->name[++i])
	{
		hex = (unsigned char *)ft_strnew(1);
		nb = gettohexa(desc->name[i]);
		hex[0] = ft_atoi_base(nb, "0123456789abcdef") & 0xFF;
		printf("%s-", hex);
		write(file->fd, hex, 1);
		free(nb);
		free(hex);
	}
	while (--len > -1)
		write(file->fd, "", 1);
	return (SUCCES);
}

int 	write_comment(t_description *desc, t_file *file)
{
	int 	i;
	int 	len;
	unsigned char 	*hex;
	char 	*nb;

	i = -1;
	len = COMMENT_LENGTH - ft_strlen(desc->comment);
	while (desc->comment[++i])
	{
		hex = (unsigned char *)ft_strnew(1);
		nb = gettohexa(desc->comment[i]);
		hex[0] = ft_atoi_base(nb, "0123456789abcdef") & 0xFF;
		printf("%s-", hex);
		write(file->fd, hex, 1);
		free(nb);
		free(hex);
	}
	while (--len > -1)
		write(file->fd, "", 1);
	return (SUCCES);
}

int		create_cor(t_description *desc, t_file *file)
{
	desc->file_name = add_cor(desc->file_name);
	file->fd = open(desc->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	write_binary_int(COREWAR_EXEC_MAGIC, file->fd);
	if ((file->error = write_name(desc, file)) < 1)
		return (file->error);
	if ((file->error = write_comment(desc, file)) < 1)
		return (file->error);
	//write_binary_int(0, fd);
	//rite(fd, desc->comment, COMMENT_LENGTH);
	return (SUCCES);
}

int 	convertion(t_description *desc, t_file *file)
{
	if ((file->error = create_cor(desc, file)) < 1)
		return (file->error);
	return (SUCCES);
}