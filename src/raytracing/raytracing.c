/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:49:04 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/19 10:34:47 by yait-el-         ###   ########.fr       */
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

t_vector 	sepia(t_vector color)
{
	t_vector	output;
	double 		tr;
	double		tg;
	double		tb;
	tr = (color.x * 0.393) + (color.y * 0.769) + (color.z * 0.189);
	tg = (color.x * 0.349) + (color.y * 0.686) + (color.z * 0.168);
	tb = (color.x * 0.272) + (color.y * 0.534) + (color.z * 0.131);
	output.x = color_nrm(tr);
	output.y = color_nrm(tg);
	output.z = color_nrm(tb);
	return (output);
}

t_vector    grey(t_vector color)
{
	t_vector    output;
	double      tr;
	double      tg;
	double      tb;
	tr = (color.x * 0.299) + (color.y * 0.587) + (color.z * 0.114);
	tg = (color.x * 0.299) + (color.y * 0.587) + (color.z * 0.114);
	tb = (color.x * 0.299) + (color.y * 0.587) + (color.z * 0.114);
	output.x = color_nrm(tr);
	output.y = color_nrm(tg);
	output.z = color_nrm(tb);
	return (output);
}

void				Antialiasing(t_rtv *rtv,double x, double y)
{
	int				i = 0;
	t_ray           ray2;
	t_vector		test;
	double			r2 = 0;
	t_vector		color;
	t_vector		up;

	up = (t_vector){0,1,0};
	color = (t_vector){0,0,0};
	ray2.origin = rtv->camera->origin;
	test = (t_vector){0,0,0};

	while (i < 20)
	{
		test.x = (rand() % 3) /10.0;
		test.y = (rand() % 3) /10.0;
		test.z =  0;
		ray2.direction = nrm(camera(rtv->camera, x, y, up,test));
		color = add(color,get_pxl(rtv, ray2));
		i++;
	}

	color = divi(color,20.0);
	rtv->mlx.img[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = rgb_to_int(color);
}

void				raytracing1(t_thread *th)
{
	int				x;
	int				y;
	int				l;
	t_vector		color;
	t_vector		up;
	t_ray			ray2;
	t_rtv           *rtv;
	t_vector		test;
	t_vector		*colors;
	rtv = th->rt;

	l=0;
	test = (t_vector){0,0,0};
	ray2.origin = rtv->camera->origin;
	up = (t_vector){0, 1, 0};
	x = (th->idthread * WIN_W / THREAD_NUMBER);

	y = 0;
	while (x < ((th->ending) * WIN_W / THREAD_NUMBER))
	{
		y = 0;
		while (y < WIN_W)
		{
			//Antialiasing(rtv,(double)x,(double)y);
			ray2.direction = nrm(camera(rtv->camera, x, y, up,test));
			color = get_pxl(rtv, ray2);
			rtv->mlx.colors[(WIN_H - 1 - y) * WIN_W + x] = color;
			rtv->mlx.img[(WIN_H - 1 - y) * WIN_W + x] = rgb_to_int(color);
			y++;
		}
		x++;
	}
	printf("this is %d -- \n",(WIN_H - 1 - x) * WIN_W + y);
	pthread_exit(NULL);
}

void				raytracing(t_rtv rtv)
{
	pthread_t		newthread[THREAD_NUMBER];
	t_thread		th[THREAD_NUMBER];
	t_vector 	colors;
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
	t= 0;
	while( t < i )
	{
		pthread_join(newthread[t],NULL);
		t++;
	}
	//cartoon(rtv.mlx.img,&colors);
}
