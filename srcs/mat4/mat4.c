/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 22:50:43 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/05 20:20:29 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4		mat4(t_vec4 x, t_vec4 y, t_vec4 z, t_vec4 w)
{
	t_mat4	m;

	m.x = x;
	m.y = y;
	m.z = z;
	m.w = w;
	return (m);
}

t_mat4		mat4_identity()
{
	return (mat4(
		vec4_3(1, 0, 0),
		vec4_3(0, 1, 0),
		vec4_3(0, 0, 1),
		vec4(0, 0, 0, 1)
	));
}

t_mat4		mat4_projection(float angleView, float near, float far)
{
	float	tan_fov;
	float	ar;

	ar = 500 / 500;
	tan_fov = tan(angleView * (M_PI / 180));
	return (mat4(
		vec4_3	(1 / (tan_fov * ar)	, 0		, 0),
		vec4_3	(0		, 1 / tan_fov , 0),
		vec4	(0		, 0		, (-near - far) / (far - near), 2. * far * near / (far - near)),
		vec4	(0		, 0		, 1, 0)
	));
}

t_vec3		mat4_mulv(t_mat4 m, t_vec3 v)
{
	float 	w;
	v.x = v.x * m.x.x + v.y * m.x.y + v.z * m.x.z + m.x.w;
	v.y = v.x * m.y.x + v.y * m.y.y + v.z * m.y.z + m.y.w;
	v.z = v.x * m.z.x + v.z * m.z.y + v.z * m.z.z + m.z.w;
	w = v.x * m.w.x + v.y * m.w.y + v.z * m.w.z + m.w.w;

	if (w != 1)
		v = vec3_div(v, w, w, w);
	return (v);
}

t_mat4		mat4_cam_transform(t_vec3 target, t_vec3 up)
{
	const t_vec3	n = vec3_norm(target);
	const t_vec3	u = vec3_norm(vec3_cross(up, target));
	const t_vec3	v = vec3_cross(n, u);

	return (mat4(
		vec4_3v(u),
		vec4_3v(v),
		vec4_3v(n),
		vec4(0, 0, 0, 1)
	));
}