/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:02:19 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/28 15:23:09 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		add(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vector		sub(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_vector		multi(t_vector vec1, double t)
{
	t_vector	result;

	result.x = vec1.x * t;
	result.y = vec1.y * t;
	result.z = vec1.z * t;
	return (result);
}

t_vector		divi(t_vector vec1, double t)
{
	t_vector	result;

	result.x = vec1.x / t;
	result.y = vec1.y / t;
	result.z = vec1.z / t;
	return (result);
}

double			length_squared(t_vector vec1, t_vector vec2)
{
	double		result;

	result = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (result);
}
