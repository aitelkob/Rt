/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 09:59:39 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/16 18:35:52 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
t_vector		*color_fill2()
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
	colors[39] = ft_itvect(44, 62, 80);

	return (colors);
}

t_vector		*color_fill()
{
	t_vector	*colors;

	colors[0] = ft_itvect(192,57,43);
	colors[1] = ft_itvect(231, 76, 60 );
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
	colors[13] = ft_itvect(211, 84, 0);
	colors[14] = ft_itvect(236, 240, 241);
	colors[15] = ft_itvect(189, 195, 199);
	colors[16] = ft_itvect(149, 165, 166);
	colors[17] = ft_itvect(127, 140, 141);
	colors[18] = ft_itvect(52, 73, 94);
	colors[19] = ft_itvect(44, 62, 80);
	return (colors);
}

/*void			cartoon(double img);
{
	int i,j,copy;
	t_vector save;
  t_vector rgb;
  t_vector *colors

	while (i++ < W * H)
	{
		j = 0;
		d = INFINITY;
		rgb = int_to_rgb(img,i);
		while (j++ < 10)
		{
			copy = sqrt(pow(rgb.x - colors[j].x, 2)
				  	+ pow(rgb.y - colors[j].y, 2)
					+ pow(rgb.z - colors[j].z, 2));
            rgb.r += (img[i + cnt] >> 16);
                  rgb.g += (img[i + cnt] >> 8) % 256;
                        rgb.b += img[i + cnt] % 256;
			if (copy < d)
			{
				save = (t_vector)color[j];
			  d = copy;
			}
		}
		img[i] = rgb_to_int(save);
	}
}*/
