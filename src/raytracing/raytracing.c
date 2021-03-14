/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:49:04 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/14 17:56:54 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector			camera(t_camera *camera, int x, int y, t_vector up)
{
	t_ray			ray;
	t_vector		w_vector;
	t_vector		u_vector;
	t_vector		v_vector;
	t_vector		p;

	ray.origin = camera->origin;
	ray.direction = camera->look_at;
	ray.origin.x += 0.000000001;
	w_vector = nrm(sub(ray.direction, ray.origin));
	u_vector = nrm(crossproduct(w_vector, up));
	v_vector = crossproduct(w_vector, u_vector);
	p.z = tan(deg_to_rad(camera->fov) / 2.0);
	p.x = map(x, -1, ((1.0 - (-1.0)) / (WIN_W - 0.0)));
	p.y = map(y, 1, ((-1.0 - (1.0)) / (WIN_W - 0.0)));
	return (add(add(multi(u_vector, p.x * p.z)
	, multi(v_vector, p.y * p.z)), w_vector));
}

void	stereoscopic_render(t_rtv *rtv)
{
	t_vector		color;
	t_vector		color2;
	t_ray			ray2;

	ray2.origin = rtv->camera->origin;
	rtv->up = (t_vector){0, 1, 0};
	rtv->x = -1;
	while (++rtv->x < WIN_H)
	{
		rtv->y = -1;
		while (++rtv->y < WIN_W)
		{
			ray2.direction = nrm(camera(rtv->camera, rtv->x-15, rtv->y, rtv->up));
			color = get_pxl(rtv, ray2);
			color.y = 0;
			color.x += 60;
			ray2.direction = nrm(camera(rtv->camera, rtv->x+15, rtv->y, rtv->up));
			color2 = get_pxl(rtv, ray2);
			color2.x = 0;
			color2.y += 60;
			color.x = (color.x + color2.x) / 2;
			color.y = (color.y + color2.y) / 2;
			color.z = (color.z + color2.z) / 2;
			rtv->mlx.img[(WIN_H - 1 - (int)rtv->y) * WIN_W + (int)rtv->x] = rgb_to_int(color);
		}
	}
}

void			render(t_rtv *rtv)
{
	t_vector		color;
	t_ray			ray2;

	ray2.origin = rtv->camera->origin;
	rtv->up = (t_vector){0, 1, 0};
	rtv->x = -1;
	while (++rtv->x < WIN_H)
	{
		rtv->y = -1;
		while (++rtv->y < WIN_W)
		{
			ray2.direction = nrm(camera(rtv->camera, rtv->x, rtv->y, rtv->up));
			color = get_pxl(rtv, ray2);
			rtv->mlx.img[(WIN_H - 1 - (int)rtv->y) * WIN_W + (int)rtv->x] = rgb_to_int(color);
		}
	}
}

void				raytracing(t_rtv *rtv)
{
	int stereo = 0;
	if (stereo)
		stereoscopic_render(rtv);
	else
		render(rtv);
}
