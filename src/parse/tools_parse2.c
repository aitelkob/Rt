/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:09:15 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/16 17:55:03 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_vect(t_vector vec, char *str)
{
	printf("%s->x=%0.2f,%0.2f,%0.2f\n", str, vec.x, vec.y, vec.z);
}

void			error(char *str, char *where)
{
	printf("%s in ===(%s)\n", str, where);
	exit(0);
}

void			rot_trans(t_object *obj)
{
	obj->aim = nrm(obj->aim);
	obj->aim = rotation(obj->aim, obj->rot);
	obj->origin = add(obj->origin, obj->translation);
}

int				color_nrm(double i)
{
	return (i > 255 ? 255 : i);
}

int				rgb_to_int(t_vector v)
{
	int			red;
	int			green;
	int			blue;
	int			rgb;

	red = color_nrm((int)v.x);
	green = color_nrm((int)v.y);
	blue = color_nrm((int)v.z);
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

t_vector		int_to_rgb(int img,int i)
{
	t_vector	rgb;

	rgb.x = color_nrm(img[i] >> 16);
	rgb.y = color_nrm(img[i] >> 8);
	rgb.z = color_nrm(img[i]);

	return (rgb);
}
