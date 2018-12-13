/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:35:04 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/13 03:26:52 by llelievr         ###   ########.fr       */
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
		0, 0, 1, 0
	}));
}

t_cam		init_camera(void)
{
	t_cam camera;
	
	camera.rotation = (t_vec3){0, 0, 0};
	camera.pos = (t_vec3){0, 0, -2};
	camera.projection = mat4_projection_perspective(70, 0.1, 100);
	apply_matrix(&camera);
	return (camera);
}

void		apply_matrix(t_cam *cam)
{
	cam->matrix = ft_mat4_mul(
		cam->projection,
		ft_mat4_mul(
			ft_mat4_rotation(cam->rotation),
			ft_mat4_translation(cam->pos)
		)
	);
}

t_mat4		cam_view(t_cam *cam, float pitch, float yaw)
{
	const t_vec3	v_yaw = (t_vec3){cosf(yaw), sinf(yaw), 0};
	const t_vec3	v_pitch = (t_vec3){cosf(pitch), sinf(pitch), 0};
	const t_vec3	xaxis = (t_vec3){v_yaw.x, 0, -v_yaw.y};
	const t_vec3	yaxis = (t_vec3){
		v_yaw.y * v_pitch.y,
		v_pitch.x, 
		v_yaw.x * v_pitch.y
	};
	const t_vec3	zaxis = (t_vec3){
		v_yaw.y * v_pitch.x, 
		-v_pitch.y,
		v_pitch.x * v_yaw.x
	};

	return ((t_mat4)((t_mat4_data){
		xaxis.x, xaxis.y, xaxis.z, ft_vec3_dot(xaxis, cam->pos),
		yaxis.x, yaxis.y, yaxis.z, ft_vec3_dot(yaxis, cam->pos),
		zaxis.z, zaxis.y, zaxis.z, ft_vec3_dot(zaxis, cam->pos),
		0, 0, 0, 1
	}));
}
