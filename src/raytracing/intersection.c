/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:20:45 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/04 15:48:55 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	double			quadratic(double a, double b, double c)
{
	double				determinant;
	double				t0;
	double				t1;

	determinant = b * b - 4 * a * c;
	if (determinant < 0)
		return (-1);
	if (determinant == 0)
		return (-b / (2.0 * a));
	t0 = (-b + sqrtf(determinant)) / (2.0 * a);
	t1 = (-b - sqrtf(determinant)) / (2.0 * a);
	return (min_ray(t1, t0));
}
static	t_quadratic			quadratic_test(double a, double b, double c)
{
	double				determinant;
	t_quadratic			q;
	determinant = b * b - 4 * a * c;
	if (determinant < 0)
	{
		q.t0 = 0;
		q.t1 = 0;
		q.isHit = 0;
	}
	if (determinant == 0)
	{
		q.t0 = -b / (2.0 * a);
		q.t1 = -b / (2.0 * a);
		q.isHit = 1;
	}
	else {
		q.t0 = (-b + sqrtf(determinant)) / (2.0 * a);
		q.t1 = (-b - sqrtf(determinant)) / (2.0 * a);
		q.isHit = 1;
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

double					intersection_triangle(t_ray ray, t_object triangle)
{
	double				d;
	double				dist;
	t_vector			vector_distance;
	t_vector		p_c;
	t_vector		xvec;
	t_vector		v1;
	t_vector		v2;

	//print_vect(triangle.origin,"tri");
	v1 = sub((t_vector) {-50,1,1}, triangle.origin);
	v2 = sub((t_vector) {1,60,1}, triangle.origin);
	d = dot(crossproduct(v1,v2), ray.direction);
	vector_distance = vecto_subvec(triangle.origin, ray.origin);
	dist = dot(vector_distance, crossproduct(v1,v2)) / d;
	xvec = sub(ray.origin, triangle.origin);
	p_c = add(xvec, multi(ray.direction, dist));
	double q = p_c.x/(v1.x * v2.x);
	double p = p_c.y/(v1.y * v2.y);
	
	if(!(q >= 0 && q <= 1 && p >= 0 && p <= 1 && q + p >= 0 && q + p <= 1))
		return (-1);
	if (dist > 0)
		return (dist);
	return (-1);
}

t_quadratic					intersection_cylinder(t_ray ray, t_object cylinder)
{
	t_inters			inter;

	inter.x = vecto_subvec(ray.origin, cylinder.origin);
	inter.a = dot(ray.direction, ray.direction) - dot(ray.direction,
			cylinder.aim) * dot(ray.direction, cylinder.aim);
	inter.b = (dot(ray.direction, inter.x) - dot(ray.direction,
				cylinder.aim) * dot(inter.x, cylinder.aim)) * 2;
	inter.c = dot(inter.x, inter.x) - dot(inter.x, cylinder.aim) *
		dot(inter.x, cylinder.aim) - cylinder.radius * cylinder.radius;
	return (quadratic_test(inter.a, inter.b, inter.c));
}
t_quadratic					intersection_cone(t_ray ray, t_object cone)
{
	double				alpha;
	double				tk;
	t_inters			inter;

	alpha = deg_to_rad(cone.angle);
	inter.x = vecto_subvec(ray.origin, cone.origin);
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
	return (quadratic_test(inter.a, inter.b, inter.c));
}

t_quadratic					intersection_sphere(t_ray ray, t_object sphere)
{
	t_inters			inter;

	inter.x = vecto_subvec(ray.origin, sphere.origin);
	inter.a = dot(ray.direction, ray.direction);
	inter.b = 2 * dot(ray.direction, inter.x);
	inter.c = dot(inter.x, inter.x) - (sphere.radius * sphere.radius);
	return (quadratic_test(inter.a, inter.b, inter.c));
}
