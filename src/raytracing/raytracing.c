/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:49:04 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/27 16:05:51 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_camera_vect		camera_init(t_camera *camera)
{
	t_camera_vect	camera_vect;
	t_ray			ray;

	ray.origin = camera->origin;
	ray.direction = camera->look_at;
	ray.origin.x += 0.000000001;
	camera_vect.w = nrm(sub(ray.direction, ray.origin));
	camera_vect.u = nrm(crossproduct(camera_vect.w, (t_vector){0, 1, 0}));
	camera_vect.v = crossproduct(camera_vect.w, camera_vect.u);
	camera_vect.fov = camera->fov;
	return (camera_vect);
}

t_vector			camera(t_camera_vect camera_vect, double x, double y,\
t_vector test)
{
	t_vector		p;

	p.z = tan(deg_to_rad(camera_vect.fov) / 2.0);
	p.x = map(x + test.x, -1, ((1.0 - (-1.0)) / (WIN_W - 0.0)));
	p.y = map(y + test.y, 1, ((-1.0 - (1.0)) / (WIN_W - 0.0)));
	return (add(add(multi(camera_vect.u, p.x * p.z)
					, multi(camera_vect.v, p.y * p.z)), camera_vect.w));
}

void				start_draw(t_rtv *rtv, double x, double y, t_ray ray2)
{
	t_vector		up;
	t_vector		color;
	t_vector		test;

	test = (t_vector){0, 0, 0};
	up = (t_vector){0, 1, 0};
	ray2.direction = nrm(camera(rtv->camera_vect, x, y, test));
	color = get_pxl(rtv, ray2);
	rtv->mlx.colors[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = color;
	rtv->mlx.img[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = rgb_to_int(color);
}

void				raytracing1(t_thread *th)
{
	int				x;
	int				y;
	t_ray			ray2;
	t_rtv			*rtv;

	rtv = th->rt;
	ray2.origin = rtv->camera->origin;
	x = (th->idthread * WIN_W / THREAD_NUMBER);
	while (x < ((th->ending) * WIN_W / THREAD_NUMBER))
	{
		y = 0;
		while (y < WIN_W)
		{
			if (rtv->filter == 0)
				start_draw(rtv, (double)x, (double)y, ray2);
			if (rtv->filter == 1)
				stereoscopy(rtv, (double)x, (double)y, ray2);
			if (rtv->filter == 2)
				antialiasing(rtv, (double)x, (double)y, ray2);
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}

void				raytracing(t_rtv rtv)
{
	pthread_t		newthread[THREAD_NUMBER];
	t_thread		th[THREAD_NUMBER];
	int				i;
	int				t;

	i = 0;
	t = 1;
	displayloading(&rtv.mlx);
	rtv.camera_vect = camera_init(rtv.camera);
	while (i < THREAD_NUMBER)
	{
		th[i].rt = &rtv;
		th[i].idthread = i;
		th[i].ending = t;
		pthread_create(&newthread[i], NULL, (void*)raytracing1, (void*)&th[i]);
		i++;
		t++;
	}
	t = 0;
	while (t < i)
	{
		pthread_join(newthread[t], NULL);
		t++;
	}
}
