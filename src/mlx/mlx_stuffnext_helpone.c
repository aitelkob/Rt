/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuffnext_helpone.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:50:30 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/27 15:12:31 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			key_hook_helptwo(int keycode, t_rtv *rtv)
{
	if (keycode == KEY_T)
	{
		rtv->scale -= 10;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_4)
	{
		rtv->translationx -= 2;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_6)
	{
		rtv->translationx += 2;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
}

void			key_hook_helpone(int keycode, t_rtv *rtv)
{
	if (keycode == KEY_1)
	{
		rtv->scale *= 1.2;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_V)
	{
		rtv->light->intensity = !rtv->light->intensity * 100;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_3)
	{
		if (rtv->scale / 1.2 > 2)
		{
			rtv->scale /= 1.2;
			displayloading(&rtv->mlx);
			raytracing(*rtv);
			display(rtv, &rtv->mlx);
		}
	}
	key_hook_helptwo(keycode, rtv);
}

void			key_hook_help(int keycode, t_rtv *rtv)
{
	if (keycode == KEY_5)
	{
		rtv->translationy += 2;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_8)
	{
		rtv->translationy -= 2;
		displayloading(&rtv->mlx);
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	key_hook_helpone(keycode, rtv);
}
