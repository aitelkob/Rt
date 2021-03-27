/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:26:32 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/27 17:02:00 by babdelka         ###   ########.fr       */
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
	obj->refraratio = 0.5;
	obj->texture = "";
	obj->h = -1;
	obj->w = -1;
	obj->material = EMPTY;
}

double				input_onearg(char *data, int nbr, char *head)
{
	char			**lines;
	double			ret;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 1)
	{
		free(data);
		free(head);
		syntax_error(data, head, nbr);
	}
	free(data);
	ret = ft_atoi(lines[0]);
	free_splited(lines);
	return (ret);
}

char				*input_texture(char *data, int nbr, char *head)
{
	char			**lines;
	char			*ret;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 1 || (ft_strncmp(ft_strrev(lines[0]),\
	"gnp.", 4) != 0))
	{
		free(data);
		free(head);
		syntax_error(data, head, nbr);
	}
	free(data);
	ret = ft_strdup(ft_strrev(lines[0]));
	free_splited(lines);
	return (ret);
}

t_vector			input_vector(char *data, int nbr, char *head)
{
	char			**lines;
	t_vector		vec;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 3)
	{
		free(data);
		free(head);
		syntax_error("reasing", "parameters wrong in", nbr);
	}
	free(data);
	vec.x = ft_atof(lines[0]);
	vec.y = ft_atof(lines[1]);
	vec.z = ft_atof(lines[2]);
	free_splited(lines);
	return (vec);
}
