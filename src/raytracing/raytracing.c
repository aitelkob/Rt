/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:49:04 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/15 18:55:57 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fixexposure(t_vector *color)
{
	double exposure = -0.66;
	color->x = (1.0 - expf(color->x * exposure));
	color->y = (1.0 - expf(color->y * exposure));
	color->z = (1.0 - expf(color->z * exposure));
}

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

void				blurinit(t_blur *blur, int x, int y, t_vector up)
{
	blur->x = x;
	blur->y = y;
	blur->up = up;
}

void				raytracing1(t_thread *th)
{
	int				x;
	int				y;
	t_vector		color;
	t_vector		up;
	t_ray			ray2;
	t_rtv           *rtv;
	t_blur			blur;
	rtv = th->rt;

	ray2.origin = rtv->camera->origin;
	up = (t_vector){0, 1, 0};
	x = (th->idthread * WIN_W / THREAD_NUMBER);
	printf("this is %d --- %d \n",((th->ending) * WIN_W / THREAD_NUMBER),x);
	while (x < ((th->ending) * WIN_W / THREAD_NUMBER))
	{
		y = -1;
		while (++y < WIN_W)
		{
			ray2.direction = nrm(camera(rtv->camera, x, y, up));
			blurinit(&blur,x, y, up);
			color = get_pxl(rtv, ray2, blur);
			rtv->mlx.img[(WIN_H - 1 - y) * WIN_W + x] = rgb_to_int(color);
		}
		x++;
	}
	pthread_exit(NULL);
}

void			raytracing(t_rtv rtv)
{
	pthread_t		newthread[THREAD_NUMBER];
	t_thread		th[THREAD_NUMBER];

	int  i = 0;
	int t = 1;

	while (i < THREAD_NUMBER)
	{
		th[i].rt = &rtv;
		th[i].idthread = i;
		th[i].ending = t;
		pthread_create(&newthread[i],NULL,(void*)raytracing1,(void*)&th[i]);
		i++;
		t++;
	}
	t = 0;
	while (t < i)
	{
		pthread_join(newthread[t],NULL);
		t++;
	}
}
