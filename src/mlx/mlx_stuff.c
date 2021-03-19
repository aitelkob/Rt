/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:18:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/19 10:35:42 by yait-el-         ###   ########.fr       */
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
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, (WIN_W+273), WIN_H, "RTv1");
	//mlx->img_ptr2 = mlx_png_file_to_image(mlx->win_ptr,"./images/img.png", &mlx->w, &mlx->h);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	mlx->img = (int*)mlx_get_data_addr(mlx->img_ptr,&mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
	mlx->colors = (t_vector*)malloc(sizeof(t_vector) * (WIN_W * WIN_H)+1);
	//mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr2, 0, 0);
}

int				key_hook(int keycode, t_rtv *rtv)
{
	if (keycode == KEY_ESC)
	{
		//exiting_program(rtv);
		blur(&rtv->mlx);
		display(rtv, &rtv->mlx);

	}
	 	//create_bmp(rtv->mlx.img);
	return (1);
}

int				red_button(t_rtv *rtv)
{
	//exiting_program(rtv);
	return (0);
}

void			display(t_rtv *rtv, t_mlix *mlx)
{
	mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr, 0, 0);
	 mlx_hook(mlx->win_ptr, 2, 0, key_hook, mlx);
 	mlx_hook(mlx->win_ptr, 17, 0, red_button, rtv);
	mlx_loop(mlx->mlx_ptr);
}
