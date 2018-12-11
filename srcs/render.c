/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:15:45 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/11 00:52:36 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_zpixel	project(t_fdf *inst, t_vec3 p)
{
	int y;
	t_vec3 vec;
	p = ft_vec3_sub(p, (t_vec3){inst->map->cols * 0.5, 0, inst->map->rows * 0.5});
	y = p.y;
	p = ft_vec3_mul(p, (t_vec3){1, inst->map->a, 1});
	vec = ft_mat4_mulv(/*ft_mat4_mul(inst->projection, inst->camera->matrix)*/inst->camera->matrix, p);
	//printf("%f\n", vec.z);
	t_zpixel pi = (t_zpixel){ 
		(int)((vec.x + 1) * 0.5 * inst->size.x),
		(int)((1 - (vec.y + 1) * 0.5) * inst->size.y),
		-y
	};
	return (pi);
}

t_bool			put_pixel(t_fdf *inst, t_zpixel p, int color)
{
	char 	*img;
	int		s_pixel;
	int		s_line;
	int		endian;

	if (!(img = mlx_get_data_addr(inst->img, &s_pixel, &s_line, &endian)))
		return (FALSE);
	if (p.x < 0 || p.x >= inst->size.x - 1 || p.y < 0 || p.y >= inst->size.y - 1)
		return (FALSE);
	
	//color = inst->p_img[(p.y * inst->size.x) + p.x].z_index <= p.z_index ? color : (int)(img[(p.y * s_line) + (p.x * 4)]);
	ft_memmove(img + (p.y * s_line) + (p.x * 4), &color, 4);
	inst->p_img[(p.y * inst->size.x) + p.x] = p;
	return (TRUE);
}


t_bool			can_compute(t_fdf *inst, t_vec3 p)
{
	(void)p;
	(void)inst;
	return (TRUE);
}

void			draw_map(t_fdf *inst)
{
	const t_list *lst = (inst->map)->lines;
	t_line *line;
	size_t row = 0;
	size_t col;
	t_zpixel p;
	t_vec3	a;
	char 	*img;
	int		s_pixel;
	int		s_line;
	int		endian;
	
	if (!!(img = mlx_get_data_addr(inst->img, &s_pixel, &s_line, &endian)))
		ft_bzero(img, (inst->size.y * s_line));
	ft_bzero(inst->p_img, (inst->size.x * inst->size.y));
	while (lst)
	{
		line = lst->content;
		col = 0;
		while (col < (inst->map)->cols)
		{
			a = (t_vec3){col, -(line->values[col]), row};
			p = project(inst, a);
			t_line *n_line = lst->next ? (lst->next)->content : NULL;
			if (col + 1 < (inst->map)->cols)
			{
				a = (t_vec3){(col + 1), -(line->values[col + 1]), row};
				int c = line->values[col] > 0 || line->values[col + 1] > 0 ? 0x0000FF00 : 0x000000CC;
				draw_line(inst, p, project(inst, a), c);
			}
			if (col < (inst->map)->cols && n_line)
			{
				a = (t_vec3){col, -(n_line->values[col]), row + 1};
				int c = line->values[col] > 0 || n_line->values[col] > 0 ? 0x0000FF00 : 0x000000CC;
				draw_line(inst, p, project(inst, a), c);
			}
			col++;
		}
		lst = lst->next;
		row++;
	}
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img, 0, 0);
}
