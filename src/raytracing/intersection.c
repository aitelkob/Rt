/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:20:45 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/18 09:40:17 by babdelka         ###   ########.fr       */
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
		return (-b / (2 * a));
	t0 = (-b + sqrt(determinant)) / (2 * a);
	t1 = (-b - sqrt(determinant)) / (2 * a);
	return (min_ray(t1, t0));
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

// int			plane_intersect(t_object *plane, t_ray *ray, float *tmin)
// {
// 	t_vector	x;
// 	float	a;
// 	float	b;
// 	float	t;

// 	x = ft_vectorsub(ray->source, plane->pos);
// 	a = -1.0 * ft_dotproduct(x, plane->normal);
// 	b = ft_dotproduct(ray->direction, plane->normal);
// 	if (fabs(b) <= 1e-6)
// 		return (0);
// 	t = a / b;
// 	if (t > 1e-2 && t < *tmin)
// 	{
// 		*tmin = t;
// 		return (1);
// 	}
// 	return (0);
// }

double					intersection_cylinder(t_ray ray, t_object cylinder)
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

double					intersection_cone(t_ray ray, t_object cone)
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

double					intersection_sphere(t_ray ray, t_object sphere)
{
	t_inters			inter;

	inter.x = sub(ray.origin, sphere.origin);
	inter.a = dot(ray.direction, ray.direction);
	inter.b = 2 * dot(ray.direction, inter.x);
	inter.c = dot(inter.x, inter.x) - (sphere.radius * sphere.radius);
	return (quadratic(inter.a, inter.b, inter.c));
}
