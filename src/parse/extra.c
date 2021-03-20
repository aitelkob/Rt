/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:49:11 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/20 15:51:42 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void					convertmaterial(t_object *obj)
{
	if (obj->material == MIRROR)
	{
		obj->reflection = 100;
		obj->refraction = 0;
		obj->color = (t_vector){0,0,0};
	}
	if (obj->material == GLASS)
	{
		obj->refraction = 100;
		obj->reflection = 0;
		obj->refractionratio = 1;
		obj->color = (t_vector){0,0,0};
	}
	if (obj->material == RAWMETAL)
	{
		obj->reflection = 0;
		obj->refraction = 0;
	}
	if (obj->material == WATER)
	{
		obj->reflection = 5;
		obj->refraction = 100;
		obj->refractionratio = 0.62;
		obj->color = (t_vector){100,100,200};
	}
}