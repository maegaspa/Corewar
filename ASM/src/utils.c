#include "../includes/asm.h"
#include <fcntl.h>
#include <stdio.h>

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	rev;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		rev = str[i];
		str[i] = str[j];
		str[j] = rev;
		j--;
		i++;
	}
	return (str);
}

char	*gettohexa(int n)
{
	int temp;
	int tmp;
	int len;
	int i;
	int neg;
	char *hex;

	i = 0;
	len = 0;
	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	tmp = n;
	while (tmp /= 10)
		len++;
	if (!(hex = ft_strnew(len + neg)))
		return (NULL);
    while(n != 0) 
    {    
		temp = n % 16; 
		if (temp < 10) 
        { 
			hex[i] = temp + 48; 
			i++; 
		} 
		else
		{
			hex[i] = temp + 87; 
			i++; 
		} 
        n = n/16; 
    }
    hex[i] = '\0';
	return (ft_strrev(hex));
}

int	get_base_length(char *base)
{
	int	base_length;
	int	j;

	base_length = 0;
	while (base[base_length])
	{
		if (base[base_length] == '-' || base[base_length] == '+')
			return (0);
		j = base_length + 1;
		while (base[j])
		{
			if (base[base_length] == base[j])
				return (0);
			++j;
		}
		++base_length;
	}
	if (base_length < 2)
		return (0);
	return (base_length);
}

int	check_errors(char *str, char *base)
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

int	get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int 	check_label(t_tab *tab, char *str)
{
	int 	i;

	i = -1;
	while (++i < tab->nb_instruction)
		if (tab->info_ins[i].label)
			if (!ft_strcmp(tab->info_ins[i].label, str))
				return (SUCCESS);
	return (ERROR_LABEL);
}

int	ft_atoi_base(char *str, char *base)
{
	int	s;
	int	i;
	int	res;
	int	negative;
	int	base_length;

	if (!(base_length = get_base_length(base)) || !check_errors(str, base))
		return (0);
	s = 0;
	while (str[s] != '\0' && (str[s] == ' ' || str[s] == '\t'))
		s++;
	i = s - 1;
	res = 0;
	negative = 1;
	while (str[++i] && (((str[i] == '-' || str[i] == '+') && i == s) ||
			(str[i] != '-' && str[i] != '+')))
	{
		if (str[i] == '-')
			negative = -1;
		else if (str[i] != '+')
			res = (res * base_length) + (get_nb(str[i], base));
	}
	return (res * negative);
}

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
		res = ft_realloc(res, sizeof(*res) * (i + 1), sizeof(*res) * (i + 2));
	res[i] = NULL;
	close(fd);
	return (res);
}