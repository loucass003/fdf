/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:29:54 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/03 22:30:14 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4		vec4_mul(t_vec4 p, float x, float y, float z, float w)
{
	p.x *= x;
	p.y *= y;
	p.z *= z;
	p.w *= w;
	return (p);
}

t_vec4		vec4_mulv(t_vec4 p1, t_vec4 p2)
{
	return (vec4_mul(p1, p2.x, p2.y, p2.z, p2.w));
}