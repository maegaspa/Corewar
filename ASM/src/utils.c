#include "../includes/asm.h"
#include <fcntl.h>

int 		true_syntaxe_info(t_description *desc, char *str, int select, int chose)
{
	int i;
	int count;
	int tmp;

	i = 0;
	count = 0;
	while (str[select] == ' ' || str[select] == '\t')
		select++;
	if (str[select] == '\"')
	{
		tmp = select;
		while (str[++select])
		{
			if (count > 1 && str[select] != ' ' && str[select] != '\t')
				return (ERROR_INFO);
			if (str[select] == '\"')
			{
				count++;
				if (count > 1)
					return (ERROR_CHAR);
			}
			if (count == 0)
				i++;
		}
		if (chose == 1 && !(desc->name = ft_memalloc(i + 1)))
			return (ERROR_MALLOC);
		if (chose == 2 && !(desc->comment = ft_memalloc(i + 1)))
			return (ERROR_MALLOC);
		i = -1;
		while (str[++tmp] != '\"')
		{
			if (chose == 1)
				desc->name[++i] = str[tmp];
			if (chose == 2)
				desc->comment[++i] = str[tmp];
		}
		if (chose == 1)
				desc->name[++i] = '\0';
			if (chose == 2)
				desc->comment[++i] = '\0';
	}
	return (SUCCES);
}

void 	init_struct_file(t_file *file)
{
	file->name = 0;
	file->comment = 0;
	file->count = -1;
}

int 		is_name_or_comment(char *str, int chose)
{
	if (chose == 1)
		if (str[0] == '.' && str[1] == 'n' && str[2] == 'a' && str[3] == 'm' && str[4] == 'e')
			return (SUCCES);
	if (chose == 2)
		if (str[0] == '.' && str[1] == 'c' && str[2] == 'o' && str[3] == 'm' && str[4] == 'm' && str[5] == 'e' && str[6] == 'n' && str[7] == 't')
			return (SUCCES);
	return (0);
}

char		*strndup(const char *s, size_t n)
{
	char	*str;

	str = ft_memalloc(n + 1);
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

void		*ft_realloc(void *old, size_t old_size, size_t new_size)
{
	void	*new;
	size_t	cpy_size;

	if (!(new = ft_memalloc(new_size)))
		return (NULL);
	cpy_size = (old_size < new_size) ? old_size : new_size;
	if (old && cpy_size)
		ft_memcpy(new, old, cpy_size);
	if (old)
		free(old);
	return (new);
}

char	**get_file(char *filename)
{
	char	**res;
	int		i;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	res = ft_memalloc(sizeof(*res) * (2));
	i = -1;
	while (res && get_next_line(fd, &res[++i]))
		if (res)
			res = ft_realloc(res, sizeof(*res) * (i + 1), sizeof(*res) * (i + 2));
	res[i] = NULL;
	close(fd);
	return (res);
}