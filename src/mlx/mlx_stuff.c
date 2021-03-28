/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:18:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/24 18:40:01 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			obj_rotation_slice(t_mlix *mlx, t_rtv *rtv)
{
	t_object	*tmp;
	t_slice		*tmp2;

	tmp = rtv->obj;
	while (tmp)
	{
		if (tmp->rot.x != 0 || tmp->rot.y != 0 || tmp->rot.z != 0)
		{
			tmp2 = rtv->slice;
			while (tmp2)
			{
				if (tmp2->shape == tmp->slicing)
					rot_trans_slice(tmp2, tmp);
				tmp2 = tmp2->next;
			}
		}
		if (ft_strlen(tmp->texture) > 10)
			tmp->img_texture = mlx_png_file_to_image(mlx->mlx_ptr,\
			tmp->texture, &tmp->w, &tmp->h);
		tmp = tmp->next;
	}
}

void			setup_mlx(t_mlix *mlx, t_rtv *rtv)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, (WIN_W + 290), WIN_H, "RT");
	mlx->img_ptr2 = mlx_png_file_to_image(mlx->mlx_ptr,
	"./images/cartoon.png", &mlx->w, &mlx->h);
	mlx->img_ptr3 = mlx_png_file_to_image(mlx->mlx_ptr,
	"./images/cartoon1.png", &mlx->w, &mlx->h);
	obj_rotation_slice(mlx, rtv);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	mlx->img = (int*)mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel,\
	&mlx->size_line, &mlx->endian);
	mlx->colors = (t_vector*)malloc(sizeof(t_vector) * (WIN_W * WIN_H) + 1);
}

int				red_button(t_rtv *rtv)
{
	exiting_program(rtv);
	return (0);
}

void			display(t_rtv *rtv, t_mlix *mlx)
{
	mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr2, 20, 0);
	mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 0, key_hook, mlx);
	mlx_hook(mlx->win_ptr, 4, 0, mouse_press, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, red_button, rtv);
	mlx_loop(mlx->mlx_ptr);
}

int				displayloading(t_mlix *mlx)
{
	mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr3, 20, 0);
	mlx_put_image_to_window(mlx, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_do_sync(mlx->mlx_ptr);
	return (0);
}
