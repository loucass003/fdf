/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:11:53 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 01:03:56 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vec3	v_rgb(int c)
{
	return ((t_vec3){(int)((c & 0xFF0000) >> 16),
		(int)((c & 0xFF00) >> 8),
		(int)(c & 0xFF)});
}

int				c_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int				c_gradient(int a, int b, float percent)
{
	const t_vec3	a_c = v_rgb(a);
	const t_vec3	b_c = v_rgb(b);

	return (c_rgb((int)(a_c.x + (b_c.x - a_c.x) * percent),
		(int)(a_c.y + (b_c.y - a_c.y) * percent),
		(int)(a_c.z + (b_c.z - a_c.z) * percent)));
}
