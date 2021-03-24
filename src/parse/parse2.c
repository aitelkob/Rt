/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:43:51 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 18:08:18 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector				input_vector_obj(t_rtv *rtv, char *data, int nbr)
{
	char				**lines;
	t_vector			vec;
	char				*head;

	head = "tringle ";
	lines = ft_strsplit(data + 1, ' ');
	if (ft_lentab(lines) != 3)
	{
		free(data);
		syntax_error(rtv, data, head, nbr);
	}
	vec = (t_vector){0, 0, 0};
	vec.x = ft_atof(lines[0]);
	vec.y = ft_atof(lines[1]);
	vec.z = ft_atof(lines[2]);
	free_splited(lines);
	return (vec);
}

void					triangle_obj(t_rtv *rtv, t_vector *tab)
{
	static	t_object	*triangle;
	char				*arg;
	char				*data;
	t_vector			face;

	if (!triangle)
	{
		if (!(triangle = (t_object *)malloc(sizeof(t_object))))
			error("obj error allocat", "just alloct");
		init_obj(triangle);
	}
	triangle->type = TRIANGLE;
	if (get_next_line(rtv->parse.fd, &data) == 1)
	{
		face = input_vector_obj(rtv, data, rtv->parse.nb_line);
		triangle->origin = tab[((int)face.x) - 1];
		triangle->c1 = tab[(int)face.y - 1];
		triangle->c2 = tab[(int)face.z - 1];
		triangle->color = (t_vector) {rand() % 250, rand() % 250, rand() % 250};
		first_obj(rtv, triangle);
		triangle = NULL;
		free(data);
		triangle_obj(rtv, tab);
	}
}

void					stock_point(t_rtv *rtv, char *av)
{
	static	t_object	*triangle;
	t_vector			tab[rtv->parse.nb_line];
	int					index_v;
	char				*data;
	int					i;

	index_v = 0;
	if (!(rtv->parse.fd = open(av, O_RDONLY)))
		error("this is fd error !", "fd ");
	while (get_next_line(rtv->parse.fd, &data))
	{
		if (data[0] == 'v' && data[1] == ' ')
		{
			tab[index_v] = input_vector_obj(rtv, data, rtv->parse.nb_line);
			index_v++;
		}
		if (data[0] == 's')
			triangle_obj(rtv, tab);
		free(data);
	}
	free(data);
	if (rtv->parse.fd == -1)
		error("fd matsedche \n", "fd matsedch");
}

void					parce_obj(char *av, t_rtv *rtv)
{
	int					i;

	parce(OBJ6,rtv);
	if (!(rtv->parse.fd = open(av, O_RDONLY)))
		error("this is fd error !", "fd ");
	rtv->parse.nb_line = 0;
	/*rtv->light = NULL;
	rtv->obj = NULL;*/
	i = 0;
	while (get_next_line(rtv->parse.fd, &rtv->parse.line))
	{
		if (i == 1 && (ft_strcmp(rtv->parse.line, "# www.blender.org") != 0))
			syntax_error(rtv, "name of obj", "note good", rtv->parse.nb_line);
		if (rtv->parse.line[0] == 'v')
			rtv->parse.nb_line++;
		i++;
		free(rtv->parse.line);
	}
	free(rtv->parse.line);
	if (rtv->parse.fd == -1)
		error("fd matsedche \n", "fd matsedch");
	stock_point(rtv, av);
}
