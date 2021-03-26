/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:46:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/25 11:49:44 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>

void			start(t_rtv *rtv)
{
	setup_mlx(&rtv->mlx,rtv);
	rtv->tic = clock();
	rtv->filter = 0;
	rtv->loding = 0;
	rtv->scale = 40;
	rtv->translationx = 0;
	rtv->translationy = 0;
	rtv->start = 0;
	raytracing(*rtv);
	display(rtv, &rtv->mlx);
}

int				main(int ac, char **av)
{
	t_rtv		rtv;
	int			ok;

	ok = 0;
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
	{
		free(rtv.camera);
		syntax_error(".", "please parse file next time ", 0);
	}
	return (0);
}
