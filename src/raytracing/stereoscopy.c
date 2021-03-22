/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:34:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 18:15:28 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				stereoscopy(t_rtv *rtv, double x, double y, t_ray ray2)
{
	int				i;
	t_vector		test;
	t_vector		color;
	t_vector		color2;
	t_vector		up;

	color = (t_vector){0, 0, 0};
	color2 = (t_vector){0, 0, 0};
	test = (t_vector){0, 0, 0};
	i = 0;
	ray2.direction = nrm(camera(rtv->camera, x + 15, y, test));
	color = add(color, get_pxl(rtv, ray2));
	color.x = 0;
	color.y += 50;
	ray2.direction = nrm(camera(rtv->camera, x - 15, y, test));
	color2 = add(color, get_pxl(rtv, ray2));
	color2.x += 50;
	color2.y = 0;
	color = multi(add(color, color2), 0.5);
	rtv->mlx.img[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = rgb_to_int(color);
}
