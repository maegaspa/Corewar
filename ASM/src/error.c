/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maegaspa <maegaspa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:08:18 by maegaspa          #+#    #+#             */
/*   Updated: 2020/05/22 17:10:28 by maegaspa         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_line_error(t_file *file)
{
	ft_putstr_fd("Line ", 2);
	ft_putnbr_fd(file->ligne_error + 1, 2);
	ft_putstr_fd(": \"", 2);
	ft_putstr_fd(file->file[file->ligne_error], 2);
	ft_putstr_fd("\"", 2);
	ft_putstr_fd("\n", 2);
}

void	print_error(t_file *file)
{
	if (file->error == TOO_BIG)
	{
		ft_putstr_fd("ERROR: Champion is > 682 bytes, VM will not compile.\n",
		2);
		print_line_error(file);
	}
	if (file->error == ERROR_MALLOC)
	{
		ft_putstr_fd("ERROR: Malloc failed\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_INSTRUCT)
	{
		ft_putstr_fd("ERROR: Bad instruction\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_CHAR)
	{
		ft_putstr_fd("ERROR: Unexpected char\n", 2);
		print_line_error(file);
	}
	print_error2(file);
	print_error3(file);
}

void	print_error2(t_file *file)
{
	if (file->error == ERROR_PARAM || file->error == ERROR_PARAM_C
			|| file->error == ERROR_TYPE_PARAM)
	{
		ft_putstr_fd("ERROR: Bad parameter\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_LABEL)
	{
		ft_putstr_fd("ERROR: Label not declare\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_EMPTY)
		ft_putstr_fd("ERROR: Empty file\n", 2);
	if (file->error == ERROR_INFO)
	{
		ft_putstr_fd("ERROR: Unexpected CMD string\n", 2);
		print_line_error(file);
	}
}

void	print_error3(t_file *file)
{
	if (file->error == ERROR_MEMORY)
	{
		ft_putstr_fd("ERROR: Lot of memory use\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_NOINST)
	{
		ft_putstr_fd("ERROR: No instruction\n", 2);
		print_line_error(file);
	}
	if (file->error == ERROR_WRITE)
		ft_putstr_fd("ERROR: Can't write file.cor\n", 2);
	if (file->error == ERROR_COMMENT)
	{
		ft_putstr_fd("ERROR: Comment bad format : #your comment\n", 2);
		print_line_error(file);
	}
}
