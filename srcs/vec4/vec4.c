/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:32:53 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/03 22:43:39 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4		vec4(float x, float y, float z, float w)
{
	t_vec4 p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.w = w;
	return (p);
}

t_vec4		vec4_cpy(t_vec4 p)
{
	return (vec4(p.x, p.y, p.z, p.w));
}

t_vec4		vec4_3(float x, float y, float z)
{
	return (vec4(x, y, z, 0));
}

t_vec4		vec4_3v(t_vec3 v)
{
	return (vec4_3(v.x, v.y, v.z));
}