/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:29:54 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/04 15:36:24 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3		vec3_mul(t_vec3 p, float x, float y, float z)
{
	p.x *= x;
	p.y *= y;
	p.z *= z;
	return (p);
}

t_vec3		vec3_mulv(t_vec3 p1, t_vec3 p2)
{
	return (vec3_mul(p1, p2.x, p2.y, p2.z));
}