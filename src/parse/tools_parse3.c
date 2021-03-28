/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:33:58 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/27 15:45:47 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					materialret(char **lines)
{
	int				ret;

	ret = -5;
	if (!ft_strcmp("glass", lines[0]))
		ret = GLASS;
	else if (!ft_strcmp("mirror", lines[0]))
		ret = MIRROR;
	else if (!ft_strcmp("rawmaterial", lines[0]))
		ret = RAWMATERIAL;
	else if (!ft_strcmp("water", lines[0]))
		ret = WATER;
	else if (!ft_strcmp("thinglass", lines[0]))
		ret = THINGLASS;
	return (ret);
}

int					input_material(char *data, int nbr, char *head)
{
	char			**lines;
	int				ret;

	ret = -5;
	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 1)
	{
		free(data);
		free(head);
		syntax_error(data, head, nbr);
	}
	ret = materialret(lines);
	if (ret == -5)
	{
		free(data);
		free(head);
		syntax_error(data, head, nbr);
	}
	free(data);
	free_splited(lines);
	return (ret);
}

int					noiseret(char **lines)
{
	int ret;

	ret = -5;
	if (!ft_strcmp("normal", lines[0]))
		ret = NORMAL;
	else if (!ft_strcmp("check", lines[0]))
		ret = CHECK;
	else if (!ft_strcmp("wave", lines[0]))
		ret = WAVE;
	else if (!ft_strcmp("perlin", lines[0]))
		ret = PERLIN;
	return (ret);
}

int					input_noise(char *data, int nbr, char *head)
{
	char			**lines;
	int				ret;

	ret = -5;
	lines = ft_strsplit(data, ' ');
	if (ft_lentab(lines) != 1)
	{
		free(data);
		free(head);
		syntax_error(data, head, nbr);
	}
	ret = noiseret(lines);
	if (ret == -5)
	{
		free(data);
		free(head);
		syntax_error(data, head, nbr);
	}
	free(data);
	free_splited(lines);
	return (ret);
}
