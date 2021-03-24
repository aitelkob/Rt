/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:26:32 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 13:35:46 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				init_obj(t_object *obj)
{
	t_vector		v;

	v = (t_vector){0, 0, 0};
	obj->radius = 0;
	obj->origin = v;
	obj->translation = v;
	obj->angle = 60;
	obj->rot = v;
	obj->aim = v;
	obj->direction = v;
	obj->color = v;
	obj->reflection = 0;
	obj->refraction = 0;
	obj->refractionratio = 0.5;
	obj->material = EMPTY;
}

double				input_onearg(t_rtv *rtv, char *data, int nbr, char *head)
{
	char			**lines;
	double			ret;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 1)
	{
		free(data);
		free(head);
		syntax_error(rtv, data, head, nbr);
	}
	free(data);
	ret = ft_atoi(lines[0]);
	free_splited(lines);
	return (ret);
}

int					input_material(t_rtv *rtv, char *data, int nbr, char *head)
{
	char			**lines;
	int				ret;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 1)
	{
		free(data);
		free(head);
		syntax_error(rtv, data, head, nbr);
	}
	if (!ft_strcmp("glass", lines[0]))
		ret = GLASS;
	else if (!ft_strcmp("mirror", lines[0]))
		ret = MIRROR;
	else if (!ft_strcmp("rawmetal", lines[0]))
		ret = RAWMETAL;
	else if (!ft_strcmp("water", lines[0]))
		ret = WATER;
	else if (!ft_strcmp("thinglass", lines[0]))
		ret = THINGLASS;
	else
	{
		free(data);
		free(head);
		syntax_error(rtv, data, head, nbr);
	}
	free(data);
	free_splited(lines);
	return (ret);
}

t_vector			input_vector(t_rtv *rtv, char *data, int nbr, char *head)
{
	char			**lines;
	t_vector		vec;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 3)
	{
		free(data);
		free(head);
		syntax_error(rtv, "reasing", "parameters wrong in", nbr);
	}
	free(data);
	vec.x = ft_atof(lines[0]);
	vec.y = ft_atof(lines[1]);
	vec.z = ft_atof(lines[2]);
	free_splited(lines);
	return (vec);
}
