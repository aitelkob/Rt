/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:18:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 18:00:46 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_destroy(t_mlix *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
}

void			setup_mlx(t_mlix *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, (WIN_W+290), WIN_H, "RTv1");
	mlx->img_ptr2 = mlx_png_file_to_image(mlx->mlx_ptr,"./images/cartoon.png", &mlx->w, &mlx->h);
	mlx->img_ptr3 = mlx_png_file_to_image(mlx->mlx_ptr,"./images/cartoon1.png", &mlx->w, &mlx->h);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	mlx->img = (int*)mlx_get_data_addr(mlx->img_ptr,&mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
	mlx->colors = (t_vector*)malloc(sizeof(t_vector) * (WIN_W * WIN_H)+1);
}

int				key_hook(int keycode, t_rtv *rtv)
{
	t_vector *colors;
	char	l;

	if (keycode == KEY_ESC)
		exiting_program(rtv);
	if (keycode == NN)
	{
		reload(&rtv->mlx);
		display(rtv, &rtv->mlx);
	}
	if (keycode == QQ)
	{
		filter_main(&rtv->mlx,0);
		display(rtv, &rtv->mlx);
	}
	if (keycode == one)
	{
		filter_main(&rtv->mlx,1);
		display(rtv, &rtv->mlx);
	}
	if (keycode == two)
	{
		filter_main(&rtv->mlx,2);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_D)
	{
		rtv->filter = 1;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == KEY_W)
	{
		rtv->filter = 2;
		raytracing(*rtv);
	}
	if (keycode == SCREEN)
	 	create_bmp(rtv->mlx.img,l,0);
	return (1);
}

int				red_button(t_rtv *rtv)
{
	exiting_program(rtv);
	return (0);
}

void			display(t_rtv *rtv, t_mlix *mlx)
{
	mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr2, 20,0);
	mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 0, key_hook, mlx);
 	mlx_hook(mlx->win_ptr, 17, 0, red_button, rtv);
	mlx_loop(mlx->mlx_ptr);
}
