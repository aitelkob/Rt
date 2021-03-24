/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:01:37 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 19:21:21 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define WIN_H 1000
# define WIN_W 1000
# define FOV 30
# define KEY_ESC 53
# define SS 1
# define SCREEN 50
# define SPACE 49
# define CC 8
# define NN 45
# define QQ 0
# define ONE 83
# define TWO 84
# define DD 85
# define LL 86
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define SCENES 1
# define PI 3.14159
# define THREAD_NUMBER 6
# define OBJ6 "scenes/objback.yml"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <pthread.h>
# include "../library/qdbmp_1.0.0/qdbmp.h"
# include "../library/mlx/mlx.h"
# include "../library/Libft/include/libft.h"
# include "struct.h"
# include "fuction.h"

#endif
