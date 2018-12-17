/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 00:36:51 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/17 15:03:59 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img			*new_img(t_fdf *inst, t_pixel size)
{
	t_img	*img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	img->img_ptr = mlx_new_image(inst->mlx, size.x, size.y);
	img->img_buf = mlx_get_data_addr(img->img_ptr, &img->s_pixel, &img->s_line,
		&img->endian);
	if (!(img->z_buff = (float *)malloc(sizeof(float) *
		(inst->size.x * inst->size.y))))
	{
		clear_img(inst, img);
		return (NULL);
	}
	img->size = size;
	return (img);
}

t_img			*refresh_img(t_img *img)
{
	if (img->img_buf)
		ft_bzero(img->img_buf, (img->size.y * img->s_line));
	ft_memset(img->z_buff, 1000, img->size.x * img->size.y * sizeof(float));
	return (img);
}

void			clear_img(t_fdf *inst, t_img *img)
{
	if (!img)
		return ;
	mlx_destroy_image(inst->mlx, img->img_ptr);
	if (img->z_buff)
		ft_memdel((void **)&img->z_buff);
	ft_memdel((void **)&img);
}

t_bool			put_pixel(t_img *img, t_zpixel p, int c)
{
	int			i;

	if (p.x < 0 || p.x >= img->size.x - 1 || p.y < 0 || p.y >= img->size.y - 1)
		return (FALSE);
	i = p.y * img->size.x + p.x;
	if (p.z_index > img->z_buff[i])
	{
		img->z_buff[i] = p.z_index;
		ft_memmove(img->img_buf + (p.y * img->s_line) + (p.x * 4), &c, 4);
	}
	return (TRUE);
}
