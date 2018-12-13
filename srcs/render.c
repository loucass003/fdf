/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:15:45 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/12 21:35:00 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "fdf.h"
#include <stdio.h>

static t_bool	project(t_fdf *inst, t_vec3 p, t_zpixel *pi)
{
	int y;
	t_vec3 vec;
	p = ft_vec3_sub(p, (t_vec3){inst->map->cols * 0.5, 0, inst->map->rows * 0.5});
	y = p.y;
	p = ft_vec3_mul(p, (t_vec3){1, inst->map->a, 1});
	p = ft_vec3_div(p, (t_vec3){inst->map->cols, 1, inst->map->rows});
	vec = ft_mat4_mulv(inst->camera->matrix, p);
	//printf("point -> %f\n", );
	if (vec.x < -2 || vec.x > 2 || vec.y < -2 || vec.y > 2 || vec.z < -1)
		return (FALSE);

	*pi = ((t_zpixel){
		(int)((vec.x + 1) * 0.5 * inst->size.x),
		(int)((1 - (vec.y + 1) * 0.5) * inst->size.y),
		-y,
		0
	});
	return (TRUE);
}

t_bool			put_pixel(t_fdf *inst, t_zpixel p)
{
	char 	*img;
	int		s_pixel;
	int		s_line;
	int		endian;

	if (!(img = mlx_get_data_addr(inst->img, &s_pixel, &s_line, &endian)))
		return (FALSE);
	if (p.x < 0 || p.x >= inst->size.x - 1 || p.y < 0 || p.y >= inst->size.y - 1)
		return (FALSE);
	if (p.z_index < inst->p_img[(p.y * inst->size.x) + p.x].z_index)
		return (FALSE);
	inst->p_img[(p.y * inst->size.x) + p.x] = p;
	return (TRUE);
}

void			draw_map(t_fdf *inst)
{
	const t_list *lst = (inst->map)->lines;
	t_line *line;
	size_t row = 0;
	size_t col;
	t_zpixel p;
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
	while (lst)
	{
		line = lst->content;
		col = 0;
		while (col < (inst->map)->cols)
		{
			a = (t_vec3){col, -(line->values[col]), row};
			if (!project(inst, a, &p))
			{
				col++;
				continue ;
			}
			t_line *n_line = lst->next ? (lst->next)->content : NULL;
			if (col + 1 < (inst->map)->cols)
			{
				a = (t_vec3){(col + 1), -(line->values[col + 1]), row};
				if (!project(inst, a, &p2))
				{
					col++;
					continue ;
				}
				draw_line(inst, p, p2);
			}
			if (col < (inst->map)->cols && n_line)
			{
				a = (t_vec3){col, -(n_line->values[col]), row + 1};
				if (!project(inst, a, &p2))
				{
					col++;
					continue ;
				}
				draw_line(inst, p, p2);
			}
			col++;
		}
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
}*/
