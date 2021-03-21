/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 09:59:39 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/21 17:46:07 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			color_fill2(t_vector *colors)
{
	colors[20] = ft_itvect(217, 136, 128);
	colors[21] = ft_itvect(241, 148, 138);
	colors[22] = ft_itvect(195, 155, 211);
	colors[23] = ft_itvect(187, 143, 206);
	colors[24] = ft_itvect(127, 179, 213);
	colors[25] = ft_itvect(133, 193, 233);
	colors[26] = ft_itvect(118, 215, 196);
	colors[27] = ft_itvect(115, 198, 182);
	colors[28] = ft_itvect(125, 206, 160);
	colors[29] = ft_itvect(247, 220, 111);
	colors[30] = ft_itvect(248, 196, 113);
	colors[31] = ft_itvect(240, 178, 122);
	colors[32] = ft_itvect(229, 152, 102);
	colors[33] = ft_itvect(244, 246, 247);
	colors[34] = ft_itvect(229, 231, 233);
	colors[35] = ft_itvect(213, 219, 219);
	colors[36] = ft_itvect(204, 209, 209);
	colors[37] = ft_itvect(174, 182, 191);
	colors[38] = ft_itvect(128, 139, 150);
	colors[39] = ft_itvect(23, 32, 42);
}

t_vector		*color_fill(void)
{
	t_vector	*colors;

	colors = (t_vector*)malloc(sizeof(t_vector) * 40);
	colors[0] = ft_itvect(192, 57, 43);
	colors[1] = ft_itvect(231, 76, 60);
	colors[2] = ft_itvect(155, 89, 182);
	colors[3] = ft_itvect(142, 68, 173);
	colors[4] = ft_itvect(41, 128, 185);
	colors[5] = ft_itvect(52, 152, 219);
	colors[6] = ft_itvect(26, 188, 156);
	colors[7] = ft_itvect(22, 160, 133);
	colors[8] = ft_itvect(39, 174, 96);
	colors[9] = ft_itvect(46, 204, 113);
	colors[10] = ft_itvect(241, 196, 15);
	colors[11] = ft_itvect(243, 156, 18);
	colors[12] = ft_itvect(230, 126, 34);
	colors[13] = ft_itvect(1, 1, 0);
	colors[14] = ft_itvect(236, 240, 241);
	colors[15] = ft_itvect(189, 195, 199);
	colors[16] = ft_itvect(149, 165, 166);
	colors[17] = ft_itvect(127, 140, 141);
	colors[18] = ft_itvect(52, 73, 94);
	colors[19] = ft_itvect(44, 62, 80);
	color_fill2(colors);
	return (colors);
}

void			cartoon(t_mlix *mlx, t_vector *colors)
{
	int			i;
	int			j;
	double		copy;
	int			d;
	t_vector	save;
	t_vector	rgb;

	colors = color_fill();
	i = -1;
	save = (t_vector){0, 0, 0};
	while (++i < WIN_W * WIN_H)
	{
		j = -1;
		d = INFINITY;
		rgb = mlx->colors[i];
		while (++j < 40)
		{
			copy = sqrt(pow(rgb.z - colors[j].x, 2)+
						pow(rgb.y - colors[j].y, 2)+
						pow(rgb.x - colors[j].z, 2));
			if (copy < d)
			{
					save = colors[j];
					d = copy;
			}
		}
		mlx->img[i] = rgb_to_int(save);
	}
}

