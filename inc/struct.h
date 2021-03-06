/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:40:46 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/28 15:26:13 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "rtv1.h"

enum						e_type
{
	PLANE = 1,
	SPHERE,
	CYLINDER,
	TRIANGLE,
	CONE
}							t_type;

enum						e_material
{
	GLASS = 1,
	MIRROR,
	RAWMATERIAL,
	WATER,
	THINGLASS,
	EMPTY
}							t_material;

enum						e_disruptions
{
	NORMAL = 1,
	CHECK,
	WAVE,
	PERLIN,
}							t_disruptions;

typedef	struct				s_vector
{
	double					x;
	double					y;
	double					z;
}							t_vector;

typedef	struct				s_camera_vect
{
	t_vector				w;
	t_vector				u;
	t_vector				v;
	double					fov;
}							t_camera_vect;

typedef struct				s_bmp
{
	uint16_t				type;
	uint32_t				size;
	uint16_t				reserved1;
	uint16_t				reserved2;
	uint32_t				offset;
	uint32_t				header_size;
	int32_t					width_px;
	int32_t					height_px;
	uint16_t				num_planes;
	uint16_t				bits_per_pixel;
	uint32_t				compression;
	uint32_t				image_size_bytes;
	int32_t					x_resolution_ppm;
	int32_t					y_resolution_ppm;
	uint32_t				num_colors;
	uint32_t				important_colors;
}							t_bmp;

typedef	struct				s_ray
{
	t_vector				origin;
	t_vector				direction;
	t_vector				direction1;
	t_vector				direction2;
	int						type;
}							t_ray;

typedef	struct				s_parse
{
	int						fd;
	char					*line;
	int						nb_line;
	char					**agv;
	char					*obj_name;
}							t_parse;

typedef struct				s_shadowadv
{
	t_vector				light_dir;
	t_vector				color;
	double					refra;
}							t_shadowadv;

typedef	struct				s_light
{
	double					intensity;
	t_vector				origin;
	struct s_light			*next;
}							t_light;

typedef struct				s_key
{
	double					zoom;
	double					zoom_rn;
	double					zoom_rx;
	double					zoom_in;
	double					zoom_ix;
	int						position_x;
	double					altitude;
	int						position_y;
	unsigned int			parallel;
	double					retation_x;
	double					retation_y;
	double					color_h;
	double					color_l;
	int						menu;
	int						left_button;
}							t_key;

typedef struct				s_mlx_img_list
{
	int						width;
	int						height;
	char					*buffer;
	struct s_mlx_img_list	*next;
}							t_mlx_img_list;

typedef	struct				s_mlix
{
	void					*mlx_ptr;
	void					*win_ptr;
	void					*img_ptr;
	void					*img_ptr3;
	void					*img_ptr2;
	void					*img_ptr4;
	t_mlx_img_list			*img_texture;
	int						w;
	int						h;
	int						*d;
	int						*img;
	t_vector				*colors;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
	double					mouse_x;
	double					mouse_y;
	t_key					key;
	double					tempcount;
	t_vector				tempvec;
}							t_mlix;

typedef	struct				s_inters
{
	double					a;
	double					b;
	double					c;
	double					tmp;
	t_vector				x;
}							t_inters;

typedef	struct				s_quadratic
{
	double					t0;
	double					t1;
}							t_quadratic;

typedef	struct				s_tritemp
{
	t_vector				v0;
	t_vector				v1;
	t_vector				v2;
	t_vector				v0v1;
	t_vector				v0v2;
}							t_tritemp;

typedef struct				s_txtemp
{
	double					x;
	double					y;
	int						ipos;
	double					scale;
}							t_txtemp;

typedef	struct				s_object
{
	int						type;
	double					radius;
	t_vector				origin;
	t_vector				c1;
	t_vector				c2;
	t_vector				rot;
	t_vector				aim;
	t_vector				translation;
	double					angle;
	t_vector				direction;
	t_vector				color;
	t_vector				normal;
	int						w;
	int						h;
	double					reflection;
	double					refraction;
	double					refraratio;
	char					*texture;
	t_mlx_img_list			*img_texture;
	int						disruptions;
	double					negative;
	int						material;
	int						slicing;
	t_tritemp				temp;
	t_txtemp				txt;
	struct s_object			*next;
}							t_object;

typedef struct				s_camera
{
	t_vector				origin;
	double					fov;
	t_vector				look_at;
	int						check;
	double					depth;
	double					amblgt;
	struct s_camera			*next;
}							t_camera;

typedef	struct				s_ambient
{
	double					intensity;
}							t_ambient;

typedef struct				s_slice
{
	t_vector				origin;
	t_vector				vec;
	int						shape;
	struct s_slice			*next;
}							t_slice;

typedef	struct				s_rtv
{
	t_mlix					mlx;
	t_object				*obj;
	t_parse					parse;
	t_camera				*camera;
	t_light					*light;
	t_slice					*slice;
	double					min;
	clock_t					tic;
	int						filter;
	int						start;
	int						loding;
	int						translationx;
	int						translationy;
	double					scale;
	t_camera_vect			camera_vect;
	t_ray					ray;
}							t_rtv;

typedef	struct				s_hit
{
	t_vector				point;
	double					dst;
	int						depth;
	t_object				*current;
	t_vector				normal;
	t_vector				color;
}							t_hit;

typedef struct				s_thread
{
	t_rtv					*rt;
	int						idthread;
	int						ending;
}							t_thread;

#endif
