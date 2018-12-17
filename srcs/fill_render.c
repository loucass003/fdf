/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:15:45 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/17 13:30:10 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_bool	project(t_fdf *inst, t_vec3 p, t_vec3 *raster)
{
	t_vec3	vec;

	p = ft_vec3_sub(p, (t_vec3){inst->map->cols * .5, 0, inst->map->rows * .5});
	p = ft_vec3_mul(p, (t_vec3){1, -inst->map->z_factor, 1});
	p = ft_vec3_div(p, (t_vec3){inst->map->cols, 1, inst->map->rows});
	vec = ft_mat4_mulv(inst->camera.matrix, p);
	if (vec.x < -2 || vec.x > 2 || vec.y < -2 || vec.y > 2
		|| (inst->perspective_mode && (vec.z < -1)))
		return (FALSE);
	*raster = ((t_vec3){
		((vec.x + 1) * 0.5 * inst->size.x),
		((1 - (vec.y + 1) * 0.5) * inst->size.y),
		vec.z
	});
	return (TRUE);
}

static int		colorize(t_fdf *inst, t_vec3 vert[3])
{
	const float	l = max3f(vert[0].y, vert[1].y, vert[2].y);
	const float	m_level = min3f(vert[0].y, vert[1].y, vert[2].y);
	float		d;

	if (m_level == -1 && l == -1)
		return (c_rgb(50, 50, 50));
	if (l <= 0)
		return (c_rgb(171, 201, 253));
	d = inst->map->max_height / 5;
	if (l <= d)
		return (c_gradient(c_rgb(42, 149, 27), c_rgb(247, 241, 114), l / d));
	return (c_gradient(c_rgb(238, 185, 91), c_rgb(49, 32, 17),
	l / inst->map->max_height));
}

static void		do_pixel(t_fdf *inst, float a, t_pixel p, t_vec3 *v_r[2])
{
	int			c;
	float		z;
	t_vec3		w;
	t_vec3		s;
	t_vec3		*rast;

	rast = v_r[1];
	s = (t_vec3){p.x + 0.5, p.y + 0.5, 0};
	w = (t_vec3){ edgef(rast[1], rast[2], s),
	edgef(rast[2], rast[0], s), edgef(rast[0], rast[1], s) };
	if (w.x >= 0 && w.y >= 0 && w.z >= 0)
	{
		w = ft_vec3_div(w, (t_vec3){ a, a, a });
		z = rast[0].z * w.x + rast[1].z * w.y + rast[2].z * w.z;
		c = colorize(inst, v_r[0]);
		put_pixel(inst->img, (t_zpixel){ p.x, p.y, z }, c);
	}
}

static t_bool	fill_vert(t_fdf *inst, t_vec3 vert[3])
{
	t_pixel	p;
	t_vec3	rast[3];
	t_vec2	born_x;
	t_vec2	born_y;
	float	area;

	if (!project(inst, vert[0], &rast[0]) || !project(inst, vert[1], &rast[1])
		|| !project(inst, vert[2], &rast[2]))
		return (FALSE);
	born_x = (t_vec2){ fmax(0, min3f(rast[0].x, rast[1].x, rast[2].x)),
	fmin(inst->size.x - 1, max3f(rast[0].x, rast[1].x, rast[2].x)) };
	born_y = (t_vec2){ fmax(0, min3f(rast[0].y, rast[1].y, rast[2].y)),
	fmin(inst->size.y - 1, max3f(rast[0].y, rast[1].y, rast[2].y)) };
	area = edgef(rast[0], rast[1], rast[2]);
	p = (t_pixel){ .y = born_y.x - 1 };
	while (++p.y <= born_y.y)
	{
		p.x = born_x.x - 1;
		while (++p.x <= born_x.y)
			do_pixel(inst, area, p, (t_vec3 *[2]){ vert, rast });
	}
	return (TRUE);
}

void			draw_filled_map(t_fdf *inst)
{
	t_pixel	p;
	t_vec3	vert[3];
	int		i;

	p = (t_pixel){-1, -1};
	while (p.y++ < inst->map->rows - 2)
	{
		p.x = -1;
		while (p.x++ < inst->map->cols - 2)
		{
			i = (p.y * inst->map->cols) + p.x;
			vert[2] = (t_vec3){p.x, inst->map->points[i], p.y};
			vert[1] = (t_vec3){p.x + 1, inst->map->points[i + 1], p.y};
			vert[0] = (t_vec3){p.x, inst->map->points[i + inst->map->cols],
			p.y + 1};
			if (fill_vert(inst, vert) == 0)
				continue ;
			vert[1] = vert[0];
			vert[2] = (t_vec3){p.x + 1,
			inst->map->points[i + inst->map->cols + 1], p.y + 1};
			vert[0] = (t_vec3){p.x + 1, inst->map->points[i + 1], p.y};
			if (fill_vert(inst, vert) == 0)
				continue ;
		}
	}
}
