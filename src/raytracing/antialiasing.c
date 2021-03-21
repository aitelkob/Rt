/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:34:28 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/21 14:27:09 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void                antialiasing(t_rtv *rtv,double x, double y,t_ray ray2)
{
    int             i = 0;
    t_vector        test;
    double          r2 = 0;
    t_vector        color;
    t_vector        up;

    up = (t_vector){0,1,0};
    color = (t_vector){0,0,0};
    test = (t_vector){0,0,0};

    while (i < 20)
    {
        test.x = (rand() % 10) /10.0;
        test.y = (rand() % 10) /10.0;
        test.z =  0;
        ray2.direction = nrm(camera(rtv->camera, x, y, up,test));
        color = add(color,get_pxl(rtv, ray2));
        i++;
    }

    color = divi(color,20.0);
    rtv->mlx.colors[(WIN_H - 1 -(int)y) * WIN_W + (int)x] = color;
    rtv->mlx.img[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = rgb_to_int(color);
}
