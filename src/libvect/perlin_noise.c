/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:31:53 by selibrah          #+#    #+#             */
/*   Updated: 2021/03/28 15:20:44 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				noise2(int x, int y)
{
	int tmp;

	tmp = set_hash(y % 256);
	return (set_hash((tmp + x) % 256));
}

float			lin_inter(float x, float y, float s)
{
	return (x + s * (y - x));
}

float			smooth_inter(float x, float y, float s)
{
	return (lin_inter(x, y, s * s * (3 - 2 * s)));
}

float			noise2d(float x, float y)
{
	int s;
	int t;
	int u;
	int v;

	s = noise2((int)x, (int)y);
	t = noise2((int)x + 1, (int)y);
	u = noise2((int)x, (int)y + 1);
	v = noise2((int)x + 1, (int)y + 1);
	return (smooth_inter(smooth_inter(s, t, x - (int)x),
	smooth_inter(u, v, x - (int)x), y - (int)y));
}

float			perlin2d(float x, float y, float freq, int depth)
{
	float	xa;
	float	ya;
	float	amp;
	float	fin_div[2];
	int		i;

	xa = x * freq;
	ya = y * freq;
	amp = 1.0;
	fin_div[0] = 0;
	fin_div[1] = 0.0;
	i = 0;
	while (i < depth)
	{
		fin_div[1] += 256 * amp;
		fin_div[0] += noise2d(xa, ya) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
		i++;
	}
	return (fin_div[0] / fin_div[1]);
}
