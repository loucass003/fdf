/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 00:45:59 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 04:24:07 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_bool	project(t_fdf *inst, t_vec3 p, t_zpixel *pi)
{
	float		y;
	t_vec3		vec;

	p = ft_vec3_sub(p, (t_vec3){inst->map->cols * .5, 0, inst->map->rows * .5});
	p = ft_vec3_mul(p, (t_vec3){1, -inst->map->z_factor, 1});
	y = p.y;
	p = ft_vec3_div(p, (t_vec3){inst->map->cols, 1, inst->map->rows});
	vec = ft_mat4_mulv(inst->camera.matrix, p);
	if (vec.x < -2 || vec.x > 2 || vec.y < -2 || vec.y > 2
		|| (inst->perspective_mode && vec.z < -1))
		return (FALSE);
	*pi = ((t_zpixel){
		(int)((vec.x + 1) * 0.5 * inst->size.x),
		(int)((1 - (vec.y + 1) * 0.5) * inst->size.y),
		-y
	});
	return (TRUE);
}

static int		colorize(t_fdf *inst, float l)
{
	float		d;

	if (l == -1)
		return (c_rgb(50, 50, 50));
	if (l <= 0)
		return (c_rgb(171, 201, 253));
	d = inst->map->max_height / 5;
	if (l <= d)
		return (c_gradient(c_rgb(42, 149, 27), c_rgb(247, 241, 114), l / d));
	return (c_gradient(c_rgb(238, 185, 91), c_rgb(49, 32, 17),
	l / inst->map->max_height));
}

t_bool			do_lines(t_fdf *inst, t_pixel p)
{
	t_zpixel	p0;
	t_zpixel	p1;
	t_vec3		a;
	int			i;
	int			c;

	i = (p.y * inst->map->cols) + p.x;
	a = (t_vec3){ p.x, inst->map->points[i], p.y};
	c = colorize(inst, a.y);
	if (!project(inst, a, &p0))
		return (FALSE);
	a = (t_vec3){ p.x + 1, inst->map->points[i + 1], p.y};
	if (p.x + 1 < inst->map->cols && project(inst, a, &p1))
		draw_line(inst->img, p0, p1, (int[2]){c, colorize(inst, a.y)});
	a = (t_vec3){ p.x, inst->map->points[i + inst->map->cols], p.y + 1};
	if (p.y + 1 < inst->map->rows && project(inst, a, &p1))
		draw_line(inst->img, p0, p1, (int[2]){c, colorize(inst, a.y)});
	return (TRUE);
}

void			draw_grid_map(t_fdf *inst)
{
	t_pixel		p;

	p = (t_pixel){-1, -1};
	while (p.y++ < inst->map->rows - 1)
	{
		p.x = -1;
		while (p.x++ < inst->map->cols - 1)
			do_lines(inst, p);
	}
}
