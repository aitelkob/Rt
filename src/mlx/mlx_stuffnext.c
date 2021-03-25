/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuffnext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 12:29:39 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/24 19:16:59 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			cammouve_help(int keycode, t_rtv *rtv)
{
	if (keycode == 126)
	{
		displayloading(&rtv->mlx);
		rtv->camera->origin.y += 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == 125)
	{
		displayloading(&rtv->mlx);
		rtv->camera->origin.y -= 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	camfocal(keycode, rtv);
}

void			cammouve(int keycode, t_rtv *rtv)
{
	if (keycode == 124)
	{
		displayloading(&rtv->mlx);
		rtv->camera->origin.x += 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == 123)
	{
		displayloading(&rtv->mlx);
		rtv->camera->origin.x -= 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	cammouve_help(keycode, rtv);
}

void			key_hook_help(int keycode, t_rtv *rtv)
{
	if (keycode == KEY_1)
	{
		rtv->scale += 10;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);

	}
	if (keycode == KEY_3)
	{
		rtv->scale -= 10;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode ==KEY_4)
	{
		rtv->translationx +=10;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_6)
	{
		rtv->translationx -=10;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode ==KEY_5)
	{
		rtv->translationy +=10;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_8)
	{
		rtv->translationy -=10;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
}

int				key_hook(int keycode, t_rtv *rtv)
{
	key_hook_help(keycode,rtv);
	if (keycode == KEY_ESC)
		exiting_program(rtv);
	if (keycode == SPACE)
	{
		displayloading(&rtv->mlx);
		reload(&rtv->mlx);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_C)
	{
		displayloading(&rtv->mlx);
		if (rtv->camera->next)
			rtv->camera = rtv->camera->next;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	cammouve(keycode, rtv);
	if (keycode == SCREEN && rtv->start == 1)
		create_bmp(rtv->mlx.img);
	return (1);
}

int				mouse_pressnext(int key, int x, int y, t_rtv *rtv)
{
	if (key == 1 && x >= 1034 && x <= 1286 && y >= 363 && y <= 452)
	{
		displayloading(&rtv->mlx);
		filter_main(&rtv->mlx, 0);
		display(rtv, &rtv->mlx);
	}
	if (key == 1 && x >= 1029 && x <= 1263 && y >= 821 && y <= 880)
		create_bmp(rtv->mlx.img);
	else if (key == 1 && x >= 1034 && x <= 1286 && y >= 480 && y <= 570)
	{
		displayloading(&rtv->mlx);
		filter_main(&rtv->mlx, 2);
		display(rtv, &rtv->mlx);
	}
	else if (key == 1 && x >= 1034 && x <= 1286 && y >= 599 && y <= 690)
	{
		displayloading(&rtv->mlx);
		filter_main(&rtv->mlx, 1);
		display(rtv, &rtv->mlx);
	}
	return (0);
}

int				mouse_press(int key, int x, int y, t_rtv *rtv)
{
	if (key == 1 && x >= 1034 && x <= 1286 && y >= 12 && y <= 104)
	{
		displayloading(&rtv->mlx);
		rtv->filter = 2;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	else if (key == 1 && x >= 1034 && x <= 1286 && y >= 131 && y <= 221)
	{
		displayloading(&rtv->mlx);
		cartoon(&rtv->mlx, &(t_vector){0, 0, 0});
		display(rtv, &rtv->mlx);
	}
	else if (key == 1 && x >= 1034 && x <= 1286 && y >= 247 && y <= 336)
	{
		displayloading(&rtv->mlx);
		rtv->filter = 1;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	else
		mouse_pressnext(key, x, y, rtv);
	return (0);
}
