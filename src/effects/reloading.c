/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reloading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:16:31 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 18:03:58 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			reload(t_mlix *mlx)
{
	int			i;
	t_vector	rgb;

	i = 0;
	while (i < WIN_W * WIN_H)
	{
		rgb = mlx->colors[i];
		mlx->img[i] = rgb_to_int(rgb);
		i++;
	}
}
