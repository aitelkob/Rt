/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:01:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/24 18:47:25 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		syntax_error(char *line, char *reasoning, int nbline)
{
	ft_putstr("\033[0;35m");
	ft_putstr("Syntax Error : ");
	ft_putstr("\033[0m");
	ft_putstr("\033[1;31m");
	ft_putstr(reasoning);
	ft_putstr("\033[0m");
	ft_putstr("\033[1;33m");
	ft_putstr(line);
	ft_putstr("\033[0m");
	ft_putstr(" at line ");
	ft_putstr("\033[0;31m");
	ft_putnbr(nbline);
	ft_putstr("\033[0m");
	ft_putchar('\n');
	exit(0);
}

void		unknown_setting(char *line, int nbline)
{
	ft_putstr("\033[0;35m");
	ft_putstr("Unknown setting ");
	ft_putstr("\033[0m");
	ft_putstr("\033[1;31m");
	ft_putstr(line);
	ft_putstr("\033[0m");
	ft_putstr(" at line ");
	ft_putstr("\033[0;31m");
	ft_putnbr(nbline);
	ft_putchar('\n');
	ft_putstr("\033[0m");
	exit(0);
}
