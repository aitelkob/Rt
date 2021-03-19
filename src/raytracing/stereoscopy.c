/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:34:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/19 10:44:44 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			stereoscopy(t_mlix *mlx)
{
	int			i;
	int			j;
	t_vector	rgb;
	t_vector	rgb2;
	t_vector	save;
	i = 0;

	rgb = (t_vector){0, 0, 0};
	while (i <  (WIN_W * WIN_H))
	{
		rgb = mlx->colors[i];
		rgb.x = 0;
		rgb.y = 50;
		rgb2 = mlx->colors[i];
		rgb2.y = 0;
		rgb2.x = 50;
		save = add(rgb,rgb2);

		save= divi(save,2);
		mlx->img[i] = rgb_to_int(rgb);
		i++;
	}
}
	
