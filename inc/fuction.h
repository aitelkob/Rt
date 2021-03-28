/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuction.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:22:35 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/27 16:15:06 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUCTION_H
# define FUCTION_H

# include "rtv1.h"

/*
 ****************   parsing *****************
*/

void			parce(char *av, t_rtv *rtv);
void			parce_obj(char *av, t_rtv *rtv);
void			plan_parce(t_rtv *rtv);
void			plan_checker(char *data, char *arg,
				t_object *plan, t_rtv *rtv);
int				input_noise(char *data, int nbr, char *head);
void			sphere_parce(t_rtv *rtv);
void			sphere_checker(char *data, char *arg,
				t_object *sphere, t_rtv *rtv);
double			intersection_triangle(t_ray ray, t_object triangle);
void			cylinder_parce(t_rtv *rtv);
void			cylinder_checker(char *data, char *arg,
				t_object *cylinder, t_rtv *rtv);
void			triangle_checker(char *data, char *arg, t_object *triangle,\
t_rtv *rtv);
void			free_objects(t_rtv *rtv);
void			free_lights(t_rtv *rtv);
void			cone_parce(t_rtv *rtv);
void			cone_checker(char *data, char *arg, t_object *cone, t_rtv *rtv);
void			triangle_checker(char *data, char *arg, t_object *cone,\
t_rtv *rtv);
void			rot_trans_slice(t_slice *slice,t_object *obj);
void			light_parce(t_rtv *rtv);
void			ambient_parce(t_rtv *rtv);
void			init_obj(t_object *obj);
void			camera_parce(t_rtv *rtv);
char			*settings_cut(t_rtv *rtv, char *variable, char **data);
char			*input_texture(char *data, int nbr, char *head);
char			*name_cut(t_rtv *rtv, char *line);
void			forward(t_rtv *rtv, char *line);
void			syntax_error(char *line, char *reasoning, int nbline);
void			unknown_setting(char *line, int nbline);
void			error(char *str, char *where);
void			first_camera(t_rtv *rtv, t_camera *camera);
void			first_light(t_rtv *rtv, t_light *light);
void			first_obj(t_rtv *rtv, t_object *obj);
void			first_slice(t_rtv *rtv, t_slice *slice);
t_vector		input_vector(char *data, int nbr, char *head);
double			input_onearg(char *data, int nbr, char *head);
int				input_material(char *data, int nbr, char *head);
double			input_radius(char *data, int nbr, char *head);
void			convertmaterial(t_object *obj);
void			ambient_parce(t_rtv *rtv);
void			slice_parce(t_rtv *rtv);
void			init_cam(t_camera *cam);
void			light_check(char *data, char *arg, t_light *light, t_rtv *rtv);
void			key_hook_help(int keycode, t_rtv *rtv);
void			camera_check(char *data, char *arg,
t_camera *camera, t_rtv *rtv);
void			triangle_checker_help(char *data, char *arg,\
t_object *triangle, t_rtv *rtv);

/*
 ******************************* vector lib
*/

void			print_vect(t_vector vec, char *str);
t_vector		add(t_vector vec1, t_vector vec2);
t_vector		sub(t_vector vec1, t_vector vec2);
t_vector		multi(t_vector vec1, double t);
t_vector		normalize(t_vector vector);
t_vector		divi(t_vector vec1, double t);
double			length_squared(t_vector vec1, t_vector vec2);
double			length(t_vector vec1, t_vector vec2);
void			cord(t_vector *vec, double x, double y, double z);
t_vector		ft_itvect(int x, int y, int z);
t_vector		vecto_subvec(t_vector v1, t_vector v2);
double			dot(t_vector v, t_vector b);
double			map(double x, double spw, double step);
t_vector		crossproduct(t_vector vec1, t_vector vec2);
t_vector		nrm(t_vector vec);
t_vector		rotation(t_vector v, t_vector angle);
double			min_ray(double t1, double t2);
double			deg_to_rad(double angle);
int				rgb_to_int(t_vector v);
void			rot_trans(t_object *obj);
int				color_nrm(int i);
t_vector		int_to_rgb(int colors);
void			cartoon(t_mlix *mlix, t_vector *colors);
t_vector		*color_fill();
t_vector		obj_norm(t_ray ray, t_object *obj, double dst);
/*
 ********************************mlx stuff
*/
void			create_bmp(int *img);
void			display(t_rtv *rtv, t_mlix *mlx);
int				displayloading(t_mlix *mlx);
int				key_hook(int keycode, t_rtv *rtv);
void			setup_mlx(t_mlix *mlx, t_rtv *rtv);
void			ft_destroy(t_mlix *mlx);
void			ft_put_pixel(t_mlix *mlx, int x, int y, int color);
double			get_dest(t_rtv *rtv, t_ray ray,
t_object **close, t_object *current);
int				mouse_press(int key, int x, int y, t_rtv *rtv);
int				key_hook(int keycode, t_rtv *rtv);
void			camfocal(int keycode, t_rtv *rtv);
/*
 ********************************** raytracing
*/

void			raytracing(t_rtv rtv);
t_vector		lighting(t_rtv *rtv, t_object *obj, t_hit hit, t_ray ray);
t_vector		get_pxl(t_rtv *rtv, t_ray ray);
void			blur(t_mlix *mlx);
t_vector		camera(t_camera_vect camera_vect, double x,\
double y, t_vector test);
t_vector		gpxadv(t_rtv *rtv, t_ray ray, t_vector direction, int depth);
t_vector		finalcolor(t_vector color1, t_vector color2, double *ratio);
t_vector		reflectandrefract(t_ray ray, t_object *obj,\
t_rtv *rtv, t_hit hit);
t_vector		*initgp(t_object	*obj);
void			darkcheck(t_vector *c, double ref);
t_vector		texture(t_rtv *rtv, t_object *obj, t_vector point);

/*
 ********************************** intersection
*/
double			intersection_plane(t_ray ray, t_object plane);
t_quadratic		intersection_cylinder(t_ray ray, t_object cylinder);
t_quadratic		intersection_cone(t_ray ray, t_object cone);
t_quadratic		intersection_sphere(t_ray ray, t_object sphere);

/*
 ********************************** filtters
*/
void			antialiasing(t_rtv *rtv, double x, double y, t_ray ray2);
t_vector		grey(t_vector color);
t_vector		sepia(t_vector color);
void			stereoscopy(t_rtv *rtv, double x, double y, t_ray ray2);
void			reload(t_mlix *mlx);
void			filter_main(t_mlix *mlx, int filter);
/*
 ********************************** error management
*/

void			exiting_program(t_rtv *rtv);
/*
 ********************************* debugging
*/

void			print_vect(t_vector vec, char *str);
void			loop_print(t_rtv *rtv);
#endif
