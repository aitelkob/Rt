/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:40:46 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 17:13:28 by yait-el-         ###   ########.fr       */
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
	TRIANGLE,
	CONE
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

typedef struct		s_bmp
{             // Total: 54 bytes
  uint16_t			type;             // Magic identifier: 0x4d42
  uint32_t			size;             // File size in bytes
  uint16_t			reserved1;        // Not used
  uint16_t			reserved2;        // Not used
  uint32_t			offset;// Offset to image data in bytes from beginning of file (54 bytes)
  uint32_t			header_size;  // DIB Header size in bytes (40 bytes)
  int32_t			width_px;         // Width of the image
  int32_t			height_px;        // Height of image
  uint16_t			num_planes;       // Number of color planes
  uint16_t			bits_per_pixel;   // Bits per pixel
  uint32_t			compression;      // Compression type
  uint32_t			image_size_bytes; // Image size in bytes
  int32_t			x_resolution_ppm; // Pixels per meter
  int32_t			y_resolution_ppm; // Pixels per meter
  uint32_t			num_colors;       // Number of colors  
  uint32_t			important_colors; // Important colors 
} 					t_bmp;

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

typedef struct	mlx_img_list_s
{
  int			width;
  int			height;
  char			*buffer;
  struct mlx_img_list_s	*next;
} mlx_img_list_t;

typedef	struct		s_mlix
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int			*img_ptr3;
	int			*img_ptr2;
	//int			*img_ptr6;
	mlx_img_list_t			*img_ptr6;
	int				w;
	int				h;
	int				*d;
	char *img;
	t_vector		*colors;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlix;

typedef	struct		s_inters
{
	double			a;
	double			b;
	double			c;
	double			tmp;
	t_vector		x;
}					t_inters;

typedef	struct		s_quadratic
{
	double 			t0;
	double			t1;
	double			u;
	double			v;
}					t_quadratic;


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
	clock_t			tic;
	int				filter;
	int				loding;
	t_ray			ray;
	int				depth;
	double 			scale;
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

typedef struct 		s_cl_obj
{
	t_object		*obj;
	t_vector		color;
}					t_cl_obj;

typedef struct 		s_min_obj
{
	double		min;
	t_quadratic	q;
}					t_min_obj;
#endif
