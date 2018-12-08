/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:35:04 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/07 20:30:39 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
