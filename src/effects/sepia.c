/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:06:33 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/22 17:30:40 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vector		sepia(t_vector color)
{
	t_vector	output;
	double		tr;
	double		tg;
	double		tb;

	tr = (color.x * 0.393) + (color.y * 0.769) + (color.z * 0.189);
	tg = (color.x * 0.349) + (color.y * 0.686) + (color.z * 0.168);
	tb = (color.x * 0.272) + (color.y * 0.534) + (color.z * 0.131);
	if (tr > 255.0)
		output.x = 255.0;
	else
		output.x = tr;
	if (tg > 255.0)
		output.y = 255.0;
	else
		output.y = tg;
	if (tb > 255.0)
		output.z = 255.0;
	else
		output.z = tb;
	return (output);
}
