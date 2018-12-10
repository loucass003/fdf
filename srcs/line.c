/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:11:14 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/10 17:34:31 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_fdf *inst, t_pixel p0, t_pixel p1, int color)
{
	t_pixel		delta;
	t_pixel		s;
	int 		e2;
	int			err;

	delta = (t_pixel){
		ft_abs(p1.x - p0.x),
		ft_abs(p1.y - p0.y)
	};
	s = (t_pixel){(p0.x < p1.x ? 1 : -1), (p0.y < p1.y ? 1 : -1)};
	err = (delta.x > delta.y ? delta.x : -delta.y) / 2;
	while(!TRUENT)
	{
		if (p0.x < 0 || p0.x > inst->size.x || p0.y < 0 || p0.y > inst->size.y)
			if (p1.x < 0 || p1.x > inst->size.x || p1.y < 0 || p1.y > inst->size.y)	
				return ;
		put_pixel(inst, p0, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break;
		e2 = err;
		if (e2 > -delta.x)
		{
			err -= delta.y;
			p0.x += s.x;
		}
		if (e2 < delta.y)
		{
			err += delta.x;
			p0.y += s.y;
		}
	}
}
