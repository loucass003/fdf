/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:15:45 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/12 17:56:40 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_bool	project(t_fdf *inst, t_vec3 p_raster, t_vec3 *raster)
{
	t_vec3 vec;
	vec = ft_vec3_mul(p_raster, (t_vec3){1, 1, 1});
	vec = ft_mat4_mulv(inst->camera->matrix, vec);
	//printf("point -> %f\n", );
	if (vec.x < -2 || vec.x > 2 || vec.y < -2 || vec.y > 2 || vec.z < -1)
		return (FALSE);

	*raster = ((t_vec3){
		((vec.x + 1) * 0.5 * inst->size.x),
		((1 - (vec.y + 1) * 0.5) * inst->size.y),
		-vec.z
	});
	return (TRUE);
}


t_bool			put_pixel(t_fdf *inst, t_zpixel p_raster)
{
	char 	*img;
	int		s_pixel;
	int		s_line;
	int		endian;

	if (!(img = mlx_get_data_addr(inst->img, &s_pixel, &s_line, &endian)))
		return (FALSE);
	if (p_raster.x < 0 || p_raster.x >= inst->size.x - 1 || p_raster.y < 0 || p_raster.y >= inst->size.y - 1)
		return (FALSE);
/*	if (p_raster.z_index < inst->p_img[(p_raster.y * inst->size.x) + p_raster.x].z_index)
		return (FALSE);*/
	inst->p_img[(p_raster.y * inst->size.x) + p_raster.x] = p_raster;
	return (TRUE);
}

float min3(float a, float b, float c) 
{ 
	return fmin(a, fmin(b, c));
}  
 
float max3(float a, float b, float c) 
{ 
	return fmax(a, fmax(b, c)); 
}

void			draw_map(t_fdf *inst)
{
	const t_list *lst = (inst->map)->lines;
	t_line *line;
	size_t row = 0;
	size_t col;
	t_vec3 p_raster;
	t_zpixel p2;
	t_vec3	a;
	char 	*img;
	int		s_pixel;
	int		s_line;
	int		endian;
	
	int x = 0;
	int y = 0;
	while (y < (inst->size.y))
	{
		x = 0;
		while (x < (inst->size.x))
		{
			inst->p_img[(y * inst->size.x) + x] = (t_zpixel){ x, y, inst->map->min, 0};
			x++;
		}
		y++;
	}
	if (!!(img = mlx_get_data_addr(inst->img, &s_pixel, &s_line, &endian)))
		ft_bzero(img, (inst->size.y * s_line));
	t_line *l_line = NULL;
	while (lst)
	{
		line = lst->content;
		col = 0;
		while (col < (inst->map)->cols)
		{
			t_vec3 a = (t_vec3){col, -(line->values[col]), row};
			t_line *n_line = lst->next ? (lst->next)->content : NULL;
			if (col + 1 >= (inst->map)->cols)
				continue ;
			t_vec3 b = (t_vec3){(col + 1), -(line->values[col + 1]), row};
			int even = (y % 2 == 0);
			t_vec3 c = (t_vec3){col + (!even), -(n_line->values[col]), row + 1};

			t_vec3 a_r, b_r, c_r;
			project(inst, a, &a_r);
			project(inst, b, &b_r);
			project(inst, b, &b_r);

			a_r.z = 1 / a_r.z;
			b_r.z = 1 / b_r.z;
			c_r.z = 1 / c_r.z;

			t_vec2 born_x = (t_vec2){ min4(a.x, b.x, c.x), max4(a.x, b.x, c.x) };
			t_vec2 born_y = (t_vec2){ min4(a.y, b.y, c.y), max4(a.y, b.y, c.y) };

			if (born_x.x > inst->size.x - 1 || born_x.y < 0 || born_y.x > inst->size.y - 1 || born_y.y < 0)
				continue ;
			
			int x0 = fmax(0, (int)(floor(born_x.x))); 
			int x1 = fmin(inst->size.x - 1, (int)(floor(born_x.y))); 
			int y0 = fmax(0, (int)(floor(born_y.x))); 
			int y1 = fmin(inst->size.y - 1, (int)(floor(born_y.y)));

			float area = 0;
			for (int y = y0; y <= y1; ++y) 
			{ 
				for(int x = x0; x <= x1; ++x) 
				{
					
				}
			}
			col++;
		}
		l_line = line; 
		lst = lst->next;
		row++;
	}

	y = 0;
	while (y < (inst->size.y))
	{
		x = 0;
		while (x < (inst->size.x))
		{
			int color = inst->p_img[(y * inst->size.x) + x].color;
			ft_memmove(img + (y * s_line) + (x * 4), &color, 4);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
}
