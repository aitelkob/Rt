/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:49:11 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/24 10:51:48 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void					convertmaterialnext(t_object *obj)
{
	if (obj->material == WATER)
	{
		obj->reflection = 5;
		obj->refraction = 100;
		obj->refraratio = 1.33;
		obj->color = (t_vector){100, 100, 200};
	}
	else if (obj->material == THINGLASS)
	{
		obj->reflection = 30;
		obj->refraction = 100;
		obj->refraratio = 0;
	}
}

void					convertmaterial(t_object *obj)
{
	if (obj->material == MIRROR)
	{
		obj->reflection = 100;
		obj->refraction = 0;
		obj->color = (t_vector){0, 0, 0};
	}
	else if (obj->material == GLASS)
	{
		obj->refraction = 100;
		obj->reflection = 0;
		obj->refraratio = 1.0;
		if (obj->type == SPHERE)
			obj->refraratio = 10.00;
		obj->color = (t_vector){0, 0, 0};
	}
	else if (obj->material == RAWMETAL)
	{
		obj->reflection = 0;
		obj->refraction = 0;
	}
	else
		convertmaterialnext(obj);
}
