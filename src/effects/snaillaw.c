/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snaillaw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 08:54:03 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/10 11:01:54 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vector		reflection(t_rtv rtv, t_ray ray, t_object *obj)
{
	t_vector	color;
	int			refle;
	t_object	*current;
	double		var;

	current = NULL;
	refle = 1;
	var = 0.25;
	color = (t_vector){0, 0, 0};
	while (refle-- > 0 && var > 0)
	{
		obj = obj_norm(ray, obj, rtv.hit.dst);
		ray.origin = add(multi(multi(obj->normal, dot(ray.origin, obj->normal)), -2.0f), obj->normal);
		ray.direction = rtv.hit.point;
		if(get_dest(&rtv, ray, &obj, current))
		{
			color = multi(color, 0.90 - var);
			color = add(color, multi(obj->color,0.25));
		}
		else
			refle = 0;
		var -=0.03;
	}
	return(color);
}

t_vector		effect(t_rtv rtv, t_ray ray, t_object *obj)
{
	t_vector	color;
	color = reflection(rtv, ray, obj);
	return(color);
}