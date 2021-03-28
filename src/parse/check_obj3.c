/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:16:17 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/27 15:47:17 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void						camera_check(char *data, char *arg,
t_camera *camera, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		camera->origin = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-fov", data))
		camera->fov = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-look_at", data))
		camera->look_at = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-depth", data))
		camera->depth = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-ambient", data))
		camera->amblgt = input_onearg(arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting("camera", rtv->parse.nb_line);
	}
	free(data);
}

double				input_radius(char *data, int nbr, char *head)
{
	char			**lines;
	double			ret;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 1 || ft_atoi(lines[0]) > 0)
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

t_vector			input_vector_color(char *data, int nbr, char *head)
{
	char			**lines;
	t_vector		vec;

	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 3 || ft_atof(lines[0]) > -1 ||
	ft_atof(lines[1]) > -1 || ft_atof(lines[2]) > -1)
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
