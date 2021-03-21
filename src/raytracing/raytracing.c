/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:49:04 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/21 12:23:28 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector			camera(t_camera *camera, double x, double y, t_vector up,t_vector test)
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
	p.x = map(x+test.x, -1, ((1.0 - (-1.0)) / (WIN_W - 0.0)));
	p.y = map(y+test.y, 1, ((-1.0 - (1.0)) / (WIN_W - 0.0)));
	return (add(add(multi(u_vector, p.x * p.z)
					, multi(v_vector, p.y * p.z)), w_vector));
}

void				start_draw(t_rtv *rtv,double x, double y,t_ray ray2)
{
	t_vector        up;
	t_vector        color;
	t_vector		test;

	test = (t_vector){0,0,0};
	up = (t_vector){0,1,0};
	ray2.direction = nrm(camera(rtv->camera, x, y, up,test));
	color = get_pxl(rtv, ray2);
	rtv->mlx.colors[(WIN_H - 1 -(int)y) * WIN_W + (int)x] = color;
	rtv->mlx.img[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = rgb_to_int(color);
}

void				raytracing1(t_thread *th)
{
	int				x;
	int				y;
	t_vector		color;
	t_ray			ray2;
	t_rtv           *rtv;
	t_vector		test;
	t_vector		*colors;
	rtv = th->rt;

	test = (t_vector){0,0,0};
	ray2.origin = rtv->camera->origin;
	x = (th->idthread * WIN_W / THREAD_NUMBER);
	while (x < ((th->ending) * WIN_W / THREAD_NUMBER))
	{
		y = 0;
		while (y < WIN_W)
		{
			if (rtv->filter == 0)
				start_draw(rtv,(double)x,(double)y,ray2);
			if (rtv->filter == 1)
				stereoscopy(rtv,(double)x,(double)y,ray2);
			if (rtv->filter == 2)
				antialiasing(rtv,(double)x,(double)y,ray2);

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
