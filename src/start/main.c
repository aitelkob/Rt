/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:46:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/19 10:46:15 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int			main(int ac, char **av)
{
	t_rtv	rtv;
	t_vector *colors;
	int img;
/*	BMP*    bmp;
    UCHAR   r, g, b;
    UINT    width, height;
    UINT    x, y;

	bmp = BMP_ReadFile("./screenshot/1.bmp");
	BMP_CHECK_ERROR( stderr, -1 );
	width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
	printf("this is %lu and %lu \n",width, height);*/
	if (ac == 2 && strncmp(ft_strrev(av[1]), "vtr.", 4) == 0)
	{
		parce(ft_strrev(av[1]), &rtv);
		if (rtv.camera->check != 1)
			syntax_error(&rtv, ".", "camera parce plz  ", rtv.parse.nb_line);
		setup_mlx(&rtv.mlx);
		raytracing(rtv);
		stereoscopy(&rtv.mlx);
		//blur(&rtv.mlx);
		//cartoon(&rtv.mlx,colors);
		display(&rtv, &rtv.mlx);
	}
	else
		syntax_error(&rtv, ".", "please parse file next time ", 0);
	return (0);
}
