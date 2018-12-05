/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:10:30 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/03 22:29:55 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4		vec4_div(t_vec4 p, float x, float y, float z, float w)
{
	p.x /= x;
	p.y /= y;
	p.z /= z;
	p.w /= w;
	return (p);
}

t_vec4		vec4_divv(t_vec4 p1, t_vec4 p2)
{
	return (vec4_div(p1, p2.x, p2.y, p2.z, p2.w));
}