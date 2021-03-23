/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectiontri.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:26:29 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/23 14:27:24 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int						triangle_side(t_vector v1, t_vector v0,\
t_vector p, t_vector normal)
{
	t_vector			edge0;
	t_vector			vp0;
	t_vector			c;

	edge0 = sub(v1, v0);
	vp0 = sub(p, v0);
	c = crossproduct(sub(v1, v0), sub(p, v0));
	return (dot(normal, c) < 0);
}

double					intersection_triangle(t_ray ray, t_object tri)
{
	double				d;
	double				dist;
	t_vector			vector_distance;
	t_vector			normal;
	t_vector			p;

	tri.temp.v0 = tri.origin;
	tri.temp.v1 = tri.c1;
	tri.temp.v2 = tri.c2;
	tri.temp.v0v1 = sub(tri.temp.v1, tri.temp.v0);
	tri.temp.v0v2 = sub(tri.temp.v2, tri.temp.v0);
	normal = crossproduct(tri.temp.v0v1, tri.temp.v0v2);
	d = dot(normal, ray.direction);
	vector_distance = vecto_subvec(tri.origin, ray.origin);
	dist = dot(vector_distance, normal) / d;
	p = add(ray.origin, multi(ray.direction, dist));
	if (triangle_side(tri.temp.v1, tri.temp.v0, p, normal)
		|| triangle_side(tri.temp.v2, tri.temp.v1, p, normal)
		|| triangle_side(tri.temp.v0, tri.temp.v2, p, normal))
		return (-1);
	if (dist > 0)
		return (dist);
	return (-1);
}
