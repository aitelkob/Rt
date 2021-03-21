/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 08:04:18 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/21 17:37:29 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			blur(t_mlix *mlx)
{
	int			i;
	int			j;
	t_vector	rgb;

	i = 0;
	rgb = (t_vector){0, 0, 0};
	while (i < (WIN_W * WIN_H))
	{
		j = 0;
		while (j < 10)
		{
			if (((i + j) % WIN_H) == 0)
				break ;
			rgb = add(rgb, mlx->colors[j + i]);
			j++;
		}
		rgb = divi(rgb, 10.0);
		mlx->img[i] = rgb_to_int(rgb);
		i++;
	}
}
