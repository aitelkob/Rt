/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliceandneg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:03:27 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/28 14:11:46 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				slice(t_ray ray, t_quadratic q, t_slice *slice,\
t_object *obj)
{
	t_vector		xvec;
	t_vector		p_c;
	double			is_sliced;
	t_slice			*tmp;

	tmp = slice;
	is_sliced = q.t0;
	while (tmp)
	{
		if (tmp->shape == obj->slicing)
		{
			xvec = sub(ray.origin, tmp->origin);
			p_c = add(xvec, multi(ray.direction, q.t0));
			is_sliced = dot(p_c, tmp->vec) > 0 ? q.t0 : -1;
			if (is_sliced < 0)
			{
				p_c = add(xvec, multi(ray.direction, q.t1));
				is_sliced = dot(p_c, tmp->vec) > 0 ? q.t1 : -1;
			}
		}
		tmp = tmp->next;
	}
	return (is_sliced);
}

int					isnegativeobj(t_rtv *rtv, t_ray ray, double dst)
{
	t_object		*tmp;
	t_quadratic		q;

	tmp = rtv->obj;
	while (tmp)
	{
		if (tmp->negative == 1)
		{
			q = intersection(ray, *tmp);
			if ((dst > q.t0 && dst < q.t1))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

double				negativeobj(t_rtv *rtv, t_ray ray, t_quadratic q,\
double min)
{
	if ((isnegativeobj(rtv, ray, q.t0) ||\
		(isnegativeobj(rtv, ray, q.t1) && q.t1)))
	{
		if (isnegativeobj(rtv, ray, q.t0))
			return (q.t0);
		else
			return (q.t1);
	}
	return (min);
}
