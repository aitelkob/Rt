/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia_grey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:36:46 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 18:12:42 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		sepia(t_vector color)
{
	t_vector	output;
	double		tr;
	double		tg;
	double		tb;

	tr = (color.x * 0.393) + (color.y * 0.769) + (color.z * 0.189);
	tg = (color.x * 0.349) + (color.y * 0.686) + (color.z * 0.168);
	tb = (color.x * 0.272) + (color.y * 0.534) + (color.z * 0.131);
	output.x = color_nrm(tr);
	output.y = color_nrm(tg);
	output.z = color_nrm(tb);
	return (output);
}

t_vector		grey(t_vector color)
{
	t_vector	output;
	double		tr;
	double		tg;
	double		tb;

	tr = (color.x * 0.299) + (color.y * 0.587) + (color.z * 0.114);
	tg = (color.x * 0.299) + (color.y * 0.587) + (color.z * 0.114);
	tb = (color.x * 0.299) + (color.y * 0.587) + (color.z * 0.114);
	output.x = color_nrm(tr);
	output.y = color_nrm(tg);
	output.z = color_nrm(tb);
	return (output);
}

void			filter_main(t_mlix *mlx, int filter)
{
	int			i;
	t_vector	rgb;

	i = 0;
	while (i < WIN_W * WIN_H)
	{
		rgb = mlx->colors[i];
		if (filter == 0)
			break ;
		if (filter == 1)
			mlx->img[i] = rgb_to_int(grey(rgb));
		if (filter == 2)
			mlx->img[i] = rgb_to_int(sepia(rgb));
		i++;
	}
	if (filter == 0)
		blur(mlx);
}
