/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:40:46 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 17:36:19 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "rtv1.h"

enum				e_type
{
	PLANE = 1,
	SPHERE,
	CYLINDER,
	CONE,
	TRIANGLE
};
enum				e_material
{
	GLASS = 1,
	MIRROR,
	RAWMETAL,
	WATER,
	EMPTY
}					t_material;
typedef	struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef	struct		s_ray
{
	t_vector		origin;
	t_vector		direction;
	t_vector		direction1;
	t_vector		direction2;
}					t_ray;

typedef	struct		s_parse
{
	int				fd;
	char			*line;
	int				nb_line;
	char			**agv;
	char			*obj_name;
}					t_parse;

typedef struct 		s_shadowadv
{
	t_vector		light_dir;
	t_vector		color;
	double			refra;
}					t_shadowadv;

typedef	struct		s_light
{
	double			intensity;
	t_vector		origin;
	struct s_light	*next;
}					t_light;

typedef	struct		s_mlix
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img;
	int				*d;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlix;

typedef	struct		s_inters
{
	double			a;
	double			b;
	double			c;
	double			t0;
	double			t1;
	double			tmp;
	t_vector		x;
}					t_inters;

typedef	struct		s_object
{
	int				type;
	double			radius;
	t_vector		origin;
	t_vector		c1;
	t_vector		c2;
	t_vector		rot;
	t_vector		aim;
	t_vector		translation;
	double			angle;
	t_vector		direction;
	t_vector		color;
	t_vector		normal;
	double			reflection;
	double			refraction;
	double			refractionratio;
	double			negative;
	int				material;
	struct s_object	*next;
}					t_object;
typedef struct		s_camera
{
	t_vector		origin;
	double			fov;
	t_vector		look_at;
	int				check;
	double			depth;
}					t_camera;
typedef	struct		s_rtv
{
	t_mlix			mlx;
	t_object		*obj;
	t_parse			parse;
	t_camera		*camera;
	t_light			*light;
	double			min;
	t_ray			ray;
	int				depth;
}					t_rtv;

typedef	struct 		s_hit
{
	t_vector		point;
	double			dst;
	int				depth;
	t_vector		normal;
}					t_hit;

typedef struct      s_thread
{
    t_rtv           *rt;
    int             idthread;
    int             ending;
}                   t_thread;

#endif
