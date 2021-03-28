/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:59:48 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/28 14:12:17 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				maptex(double x)
{
	return (fmod(x, 1000));
}

void				txtinit(t_txtemp *txt)
{
	txt->x = 0;
	txt->y = 0;
	txt->ipos = 0;
}

double				min(double a, double b)
{
	return (b > a ? a : b);
}

double				max(double a, double b)
{
	return (b < a ? a : b);
}

int					png_to_rgb(int value)
{
	return (value < 0 ? 255 + value : value);
}
