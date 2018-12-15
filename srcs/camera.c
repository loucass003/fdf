/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:35:04 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 05:39:57 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_mat4	mat4_projection_perspective(float angle, float near, float far)
{
	const float	scale = 1 / tanf(angle * 0.5 * M_PI / 180);
	const float	a = -far / (far - near);
	const float	b = -far * near / (far - near);

	return ((t_mat4)((t_mat4_data) {
		-scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, a, b,
		0, 0, 1, 0}));
}

t_cam			init_camera(t_fdf *inst)
{
	t_cam	camera;

	if (inst->perspective_mode)
	{
		camera.rotation = (t_vec3){ -M_PI_4, 0, 0 };
		camera.pos = (t_vec3){ 0, 1, -.8 };
		camera.projection = mat4_projection_perspective(70, 0.1, 100);
	}
	else
	{
		camera.rotation = (t_vec3){ -M_PI_2, 0, 0 };
		camera.pos = (t_vec3){ 0, 0, -1 };
		camera.projection = ft_mat4_identity();
		camera.projection.a[0][0] = -1;
		camera.projection.a[2][2] = -1;
		camera.projection.a[3][3] = -1;
	}
	apply_matrix(inst, &camera);
	return (camera);
}

void			apply_matrix(t_fdf *inst, t_cam *cam)
{
	t_mat4	a;
	t_mat4	b;
	float	z;

	a = ft_mat4_rotation(cam->rotation);
	b = ft_mat4_translation(cam->pos);
	cam->matrix = ft_mat4_mul(cam->projection,
		ft_mat4_mul((inst->perspective_mode ? a : b),
		(inst->perspective_mode ? b : a)));
	if (!inst->perspective_mode)
	{
		z = -cam->pos.z;
		cam->matrix = ft_mat4_mul(cam->matrix,
			ft_mat4_scale((t_vec3){ z, z, z }));
	}
}
