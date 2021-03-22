/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:46:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 11:37:00 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>

int			main(int ac, char **av)
{
	t_rtv		rtv;
	t_vector	*colors;
	int			img;
	double		time;

	if (ac == 2 && strncmp(ft_strrev(av[1]), "lmy.", 4) == 0)
	{
		parce(ft_strrev(av[1]), &rtv);
		if (rtv.camera->check != 1)
			syntax_error(&rtv, ".", "camera parce plz  ", rtv.parse.nb_line);
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
