/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:29:32 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/05 20:47:12 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4	mat4_rotate_x(float angle)
{
	return (mat4(
		vec4_3(1, 0, 0),
		vec4_3(0, cosf(angle), -sinf(angle)),
		vec4_3(0, sinf(angle), cosf(angle)),
		vec4(0, 0, 0, 1)
	));
}

t_mat4	rotate_y(float angle)
{
	return (mat4(
		vec4_3(cosf(angle), 0, sinf(angle)),
		vec4_3(0, 1, 0),
		vec4_3(-sinf(angle), 0, cosf(angle)),
		vec4(0, 0, 0, 1)
	));
}

t_mat4	rotate_z(float angle)
{
	return (mat4(
		vec4_3(cosf(angle), -sinf(angle), 0),
		vec4_3(sinf(angle), cosf(angle), 0),
		vec4_3(0, 0, 1),
		vec4(0, 0, 0, 1)
	));
}

/*t_mat4			mat4_rotation(float angle, t_vec3 axes)
{
	t_mat4	x;
	t_mat4	y;
	t_mat4	z;

	x = mat4_identity();
	y = mat4_identity();
	z = mat4_identity();
	if (axes.x != 0)
		x = mat4_mul_saclar(rotate_x(angle), axes.x);
	if (axes.y != 0)
		y = mat4_mul_saclar(rotate_y(angle), axes.y);
	if (axes.z != 0)
		z = mat4_mul_saclar(rotate_z(angle), axes.z);
	return (mat4_mul(mat4_mul(x, y), z));
}*/