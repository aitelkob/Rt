/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:34:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 13:56:58 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			stereoscopy(t_rtv *rtv,double x, double y,t_ray ray2)
{
	int             i = 0;
	t_vector        test;
	t_vector        color,color2;
	t_vector        up;

	up = (t_vector){0,1,0};
	color = (t_vector){0,0,0};
	color2 = (t_vector){0,0,0};
	test = (t_vector){0,0,0};

	ray2.direction = nrm(camera(rtv->camera, x+15, y, up,test));
	color = add(color,get_pxl(rtv, ray2));
	color.x = 0;
	color.y += 50;
	ray2.direction = nrm(camera(rtv->camera, x-15, y, up,test));
	color2 = add(color,get_pxl(rtv, ray2));
	color2.x += 50;
	color2.y = 0;
	color = multi(add(color, color2),0.5);
	rtv->mlx.img[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = rgb_to_int(color);
}


