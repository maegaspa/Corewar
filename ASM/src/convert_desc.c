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
	if (new_name[i - 1] == '.')
	{
		new_name[i] = 'c';
		new_name[i + 1] = 'o';
		new_name[i + 2] = 'r';
	}
	return (new_name);
}

void	create_cor(t_description *desc, t_file *file)
{
	char	*file_name;
	int		fd;

	file_name = add_cor(desc->file_name);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	write_binary_int(COREWAR_EXEC_MAGIC, fd);
	//write(fd, desc->name, PROG_NAME_LENGTH);
	//write_binary_int(0, fd);
	//rite(fd, desc->comment, COMMENT_LENGTH);
}

//int main(void)
//{
//	char	*new_name;
//    int		i;
//    char	*desc = "zork.";
//    int fd;
//    unsigned int	magic = 0xea83f3;
//    char			*name = "zork";
//	int				nam_length = 5;
//
//    i = ft_strlen(desc);
//    new_name = ft_strnew(ft_strlen(desc) + 4);
//    ft_strcat(new_name, desc);
//    if (new_name[i - 1] == '.')
//    {
//    	new_name[i] = 'c';
//    	new_name[i + 1] = 'o';
//    	new_name[i + 2] = 'r';
//    }
//    fd = open(new_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
//    printf("%s\n", new_name);
//    printf("magic = %d\n", magic);
//	write_binary_int(magic, fd);
//	write(fd, name, 5);
//	return (0);
//}