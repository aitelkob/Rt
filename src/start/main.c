/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:46:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 15:43:18 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>

t_camera		*cam_init(void)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->origin = (t_vector){50, 40, -400};
	camera->fov = 60;
	camera->depth = 5;
	camera->look_at = (t_vector){0, 0, 0};
	camera->amblgt = 25;
	return (camera);
}

int				main(int ac, char **av)
{
	t_rtv		rtv;
	t_vector	*colors;
	int			img;
	double		time;

	if (ac == 2 && strncmp(ft_strrev(av[1]), "lmy.", 4) == 0)
	{
		parce(ft_strrev(av[1]), &rtv);
		// if (rtv.camera->check != 1)
		// 	syntax_error(&rtv, ".", "camera parce plz  ", rtv.parse.nb_line);
		rtv.camera = cam_init();
		setup_mlx(&rtv.mlx);
		rtv.tic = clock();
		rtv.filter = 0;
		rtv.loding = 0;
		raytracing(rtv);
		display(&rtv, &rtv.mlx);
	}
	else
		syntax_error(&rtv, ".", "please parse file next time ", 0);
	return (0);
}
