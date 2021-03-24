/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:46:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/24 10:06:02 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>

t_camera		*cam_init(void)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->origin = (t_vector){100, 100, 500};
	camera->fov = 60;
	camera->depth = 5;
	camera->look_at = (t_vector){0, 0, 0};
	camera->amblgt = 100;
	return (camera);
}

void			start(t_rtv *rtv)
{
	setup_mlx(&rtv->mlx);
	rtv->tic = clock();
	rtv->filter = 0;
	rtv->loding = 0;
	raytracing(*rtv);
	display(rtv, &rtv->mlx);
}

int				main(int ac, char **av)
{
	t_rtv		rtv;
	t_vector	*colors;
	int			img;
	double		time;
	int			ok;

	ok = 0;
	rtv.camera = cam_init();
	if (ac == 2 && strncmp(ft_strrev(av[1]), "lmy.", 4) == 0)
	{
		parce(ft_strrev(av[1]), &rtv);
		ok++;
	}
	else if (ac == 2 && strncmp((av[1]), "jbo.", 4) == 0)
	{
		parce_obj(ft_strrev(av[1]), &rtv);
		ok++;
	}
	if (ok)
		start(&rtv);
	else
		syntax_error(&rtv, ".", "please parse file next time ", 0);
	return (0);
}
