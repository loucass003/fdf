/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mul_scalar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:06:14 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/05 15:06:25 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4	mat4_mul_saclar(t_mat4 m, float v)
{
	m.x = vec4_mul(m.x, v, v, v, v);
	m.y = vec4_mul(m.y, v, v, v, v);
	m.z = vec4_mul(m.z, v, v, v, v);
	m.w = vec4_mul(m.w, v, v, v, v);
	return (m);
}