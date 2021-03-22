/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:20:45 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/19 17:56:35 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	t_quadratic			quadratic(double a, double b, double c)
{
	double				determinant;
	t_quadratic			q;
	determinant = b * b - 4 * a * c;
	if (determinant < 0)
		q.t0 = -1;
	if (determinant == 0)
	{
		q.t0 = -b / (2.0 * a);
		q.t1 = -b / (2.0 * a);
	}
	else {
		q.t1 = (-b - sqrtf(determinant)) / (2.0 * a);
		q.t0 = min_ray((-b + sqrtf(determinant)) / (2.0 * a), q.t1);
		q.t1 = q.t0 == q.t1 ? (-b + sqrtf(determinant)) / (2.0 * a) : q.t1;
	}
	return q;
}

double					intersection_plane(t_ray ray, t_object plane)
{
	double				d;
	double				dist;
	t_vector			vector_distance;

	d = dot(plane.aim, ray.direction);
	vector_distance = vecto_subvec(plane.origin, ray.origin);
	dist = dot(vector_distance, plane.aim) / d;
	if (dist > 0)
		return (dist);
	return (-1);
}

double triangle_side(t_vector v1, t_vector v0, t_vector p, t_vector normal)
{
	t_vector edge0 =sub(v1, v0); 
    t_vector vp0 = sub(p, v0); 
    t_vector C = crossproduct(sub(v1, v0), sub(p, v0));

	edge0 =sub(v1, v0); 
    vp0 = sub(p, v0); 
    C = crossproduct(sub(v1, v0), sub(p, v0));
	return dot(normal, C);
}

t_quadratic					intersection_triangle(t_ray ray, t_object triangle)
{
	double				d;
	double				dist;
	t_vector			vector_distance;
	t_vector			normal;
	t_vector			P;
	t_vector		xvec;
	t_vector		p_c;
	double			u;
	double			v;
	double			api = 1;			
	t_vector v0 = triangle.origin;
	t_vector v1 = triangle.c1;
	t_vector v2 = triangle.c2;
	t_quadratic			q;
	
	t_vector v0v1 = sub(v1,v0); 
    t_vector v0v2 = sub(v2, v0);
	normal = crossproduct(v0v1, v0v2);
	// if (dot(ray.direction, normal) < 0)
	// 	normal = multi(normal, -1);

	q.u = 0;
	q.v = 0;
	float denom = dot(normal, normal);
	d = dot(normal, ray.direction);
	vector_distance = vecto_subvec(triangle.origin, ray.origin);
	dist = dot(vector_distance, normal) / d;
	t_vector p = add(ray.origin, multi(ray.direction, dist));
	q .t0= -1;
	if (   triangle_side(v1, v0, p, normal) < 0
		|| (u = triangle_side(v2, v1, p, normal)) < 0
		|| (v = triangle_side(v0, v2, p, normal)) < 0 ) return q;

	u /= denom;
    v /= denom;
	q.u = u;
	q.v = v;
	if (dist > 0)
		q.t0 = dist;
	return q;
}

t_quadratic					intersection_cylinder(t_ray ray, t_object cylinder)
{
	t_inters			inter;

	inter.x = sub(ray.origin, cylinder.origin);
	inter.a = dot(ray.direction, ray.direction) - dot(ray.direction,
			cylinder.aim) * dot(ray.direction, cylinder.aim);
	inter.b = (dot(ray.direction, inter.x) - dot(ray.direction,
				cylinder.aim) * dot(inter.x, cylinder.aim)) * 2;
	inter.c = dot(inter.x, inter.x) - dot(inter.x, cylinder.aim) *
		dot(inter.x, cylinder.aim) - cylinder.radius * cylinder.radius;
	return (quadratic(inter.a, inter.b, inter.c));
}

t_quadratic					intersection_cone(t_ray ray, t_object cone)
{
	double				alpha;
	double				tk;
	t_inters			inter;

	alpha = deg_to_rad(cone.angle);
	inter.x = sub(ray.origin, cone.origin);
	inter.a = dot(ray.direction, ray.direction);
	inter.b = 2 * dot(ray.direction, inter.x);
	inter.c = dot(inter.x, inter.x) - (cone.radius * cone.radius);
	tk = 1 + tan(alpha / 2.0) * tan(alpha / 2.0);
	inter.a = dot(ray.direction, ray.direction) - tk * dot(ray.direction,
			cone.aim) * dot(ray.direction, cone.aim);
	inter.b = (dot(ray.direction, inter.x) - tk * dot(ray.direction,
				cone.aim) * dot(inter.x, cone.aim)) * 2;
	inter.c = dot(inter.x, inter.x) - tk * dot(inter.x,
			cone.aim) * dot(inter.x, cone.aim);
	return (quadratic(inter.a, inter.b, inter.c));
}

t_quadratic					intersection_sphere(t_ray ray, t_object sphere)
{
	t_inters			inter;

	inter.x = sub(ray.origin, sphere.origin);
	inter.a = dot(ray.direction, ray.direction);
	inter.b = 2 * dot(ray.direction, inter.x);
	inter.c = dot(inter.x, inter.x) - (sphere.radius * sphere.radius);
	return (quadratic(inter.a, inter.b, inter.c));
}
