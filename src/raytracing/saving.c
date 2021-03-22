/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:27:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 09:22:57 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fill_data(t_bmp *bmp)
{
  bmp->size = (WIN_W * WIN_H * 4) + 54;
  bmp->reserved1 = 0;
  bmp->reserved2 = 0;
  bmp->offset = 54;
  bmp->header_size = 40;
  bmp->width_px = WIN_W;
  bmp->height_px= WIN_H;
  bmp->num_planes= 1;
  bmp->bits_per_pixel = 24;
  bmp->compression = 0;
  bmp->image_size_bytes = 0;
  bmp->x_resolution_ppm = 0;
  bmp->y_resolution_ppm= 0;
  bmp->num_colors = 0;
  bmp->important_colors = 0;

}

void          bmp_header(t_bmp *bmp, int fd)
{
  unsigned char str[54];

  ft_bzero(str, 54);
  ft_memcpy(str, "BM", 2);
  ft_memcpy(str + 2, &bmp->size, 4);
  ft_memcpy(str + 10, &bmp->offset, 4);
  ft_memcpy(str + 14, &bmp->header_size, 4);
  ft_memcpy(str + 18, &bmp->width_px, 4);
  ft_memcpy(str + 22, &bmp->height_px, 4);
  ft_memcpy(str + 26, &bmp->num_planes, 2);
  ft_memcpy(str + 28, &bmp->bits_per_pixel, 2);
  ft_memcpy(str + 34, &bmp->image_size_bytes, 4);
  write(fd, &str, 54);

}

/*int		  buf_to_int(char *buf)
{
	int				i;
	int				n;

	n = 0;
	i = -1;
	while (++i < 4)
	{
		n <<= 8;
		n |= buf[i] & 0xFF;
	}
	return (n);
}*/

void			bmp_put(int *img, int fd)
{
  int			color;
  unsigned char  *buf;
  int    x;
  int   col;

  x = WIN_H;
  buf = malloc((WIN_W * WIN_H * 4) + 54);
  while (x > 0)
  {
    col = 0;
    while (col < WIN_W)
    {
      color = img[(WIN_H - x) *
        WIN_W + col];
      buf[x * WIN_W * 3 + col * 3 + 0] = color;
      buf[x * WIN_W * 3 + col * 3 + 1] = color >> 8;
      buf[x * WIN_W * 3 + col * 3 + 2] = color >> 16;
      col++;

    }
    x--;

  }
  write(fd, buf, (WIN_W * WIN_H * 4) + 54);
  free(buf);
}

void		create_bmp(int *img,char l,int i)
{
	int     fd;
    t_bmp   bmp;
    char    t;
    char   local[] = "./screenshot/test.bmp";

	fd = open(local,O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd < 0)
      if (errno == EEXIST)
      {
        t =  ('A' + (random() % 26));
        if (local[13] == t)
          t =('a' + (random() % 26)); 
        local[13]= t;
        fd = open(local,O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
      }
  fill_data(&bmp);
  bmp_header(&bmp,fd);
  bmp_put(img,fd);
}
