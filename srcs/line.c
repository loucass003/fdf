/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:11:14 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 01:53:31 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_img *img, t_zpixel p0, t_zpixel p1, int c[2])
{
	t_pixel		d;
	t_pixel		s;
	int			e[2];

	d = (t_pixel){ ft_abs(p1.x - p0.x), ft_abs(p1.y - p0.y) };
	s = (t_pixel){ (p0.x < p1.x ? 1 : -1), (p0.y < p1.y ? 1 : -1) };
	e[0] = (d.x > d.y ? d.x : -d.y) / 2;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		p0.z_index = fmax(p0.z_index, p1.z_index);
		put_pixel(img, p0, c_gradient(c[0], c[1], 1 - (d.x > d.y ? (p1.x - p0.x)
		* s.x / (double)d.x : (p1.y - p0.y) * s.y / (double)d.y)));
		e[1] = e[0];
		if (e[1] > -d.x)
		{
			e[0] -= d.y;
			p0.x += s.x;
		}
		if (e[1] < d.y)
		{
			e[0] += d.x;
			p0.y += s.y;
		}
	}
}
