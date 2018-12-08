/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:56:27 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/08 23:37:11 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <unistd.h>

#define KEY_ESC (53)
#define KEY_W (13)
#define KEY_A (0)
#define KEY_S (1)
#define KEY_D (2)
#define KEY_I (34)
#define KEY_J (38)
#define KEY_K (40)
#define KEY_L (37)
#define KEY_SHIFT (257)
#define KEY_SPACE (49)
#define KEY_PAGE_U (116)
#define KEY_PAGE_D (121)

int		key(int k, t_fdf *inst)
{
	t_vec3	incrt = (t_vec3){0, 0, 0};
	t_vec3	incrr = (t_vec3){0, 0, 0};
	const float		speed = 2;

	if (k == KEY_ESC)
	{
		exit(0);//TODO exit -> clear all vars;
	}
	if (k == KEY_A || k == KEY_D)
	{
		incrt = (t_vec3){
			.x = cosf(inst->camera->rotation.y), 
			.z = sin(inst->camera->rotation.y),
			.y = 0
		};
		if (k == KEY_D)
			incrt = ft_vec3_inv(incrt);
	}
	if (k == KEY_W || k == KEY_S)
	{
		//incrt.z = (k == KEY_S ? -speed : speed);
		incrt = (t_vec3){
			sin(inst->camera->rotation.y),
			-sin(inst->camera->rotation.x),
			-cos(inst->camera->rotation.y) 
		};
		if (k == KEY_W)
			incrt = ft_vec3_inv(incrt);
	}
	if (k == KEY_SHIFT || k == KEY_SPACE)
		incrt.y = (k == KEY_SHIFT ? -1 : 1);
	if (k == KEY_I || k == KEY_K)
		incrr.x = (k == KEY_I ? 0.05 : -0.05);
	if (k == KEY_J || k == KEY_L)
		incrr.y = (k == KEY_J ? -0.05 : 0.05);
	if (k == KEY_PAGE_U || k == KEY_PAGE_D)
		inst->map->a += (k == KEY_PAGE_U ? 0.1 : -0.1);
	ft_putnbr(k);
	ft_putendl("");
	incrt = ft_vec3_mul(incrt, (t_vec3){speed, speed, speed});
	inst->camera->rotation = ft_vec3_add(inst->camera->rotation, incrr);
	inst->camera->pos = ft_vec3_add(inst->camera->pos, incrt);
	inst->camera->matrix = ft_mat4_mul(
		ft_mat4_rotation(inst->camera->rotation),
		ft_mat4_translation(inst->camera->pos)
	);
	/*cam_view(inst->camera, inst->camera->rotation.x, inst->camera->rotation.y)*/;
	draw_map(inst);
	return (0);
}

t_mat4	mat4_projection_perspective(float angle, float near, float far)
{
	const float	scale = 1 / tanf(angle * 0.5 * M_PI / 180);
	const float	a = (-far + near) / (far - near);
	const float	b = 2 * (far * near) / (far - near);
	const t_mat4 perspective = ((t_mat4)((t_mat4_data) {
		-scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, a, -1,
		0, 0, b, 0
	}));
	return ft_mat4_mul(perspective, ft_mat4_scale((t_vec3){1, 1, 1}));
}

#define SQRT36 (0.70710678118)
#define SQRT26 (0.57735026919)

/*t_mat4	mat4_isometric()
{
	return ((t_mat4)(t_mat4_data) {
		-SQRT36, 0, 0, -SQRT36,
		1     , 1, 2, 0,
		-SQRT26, SQRT26, SQRT26, 0,
		0    , 0    , 1 , 0
	});

}*/

int		main(int argc, char **argv)
{
	t_fdf inst;

	if (argc != 2)
		return (0);
	if (!(inst.map = read_map(argv[1])))
	{
		ft_putstr("Error: impossible de lire la map\n");
		return (0);
	}
	inst.size = (t_pixel){ 1000, 1000 };

	inst.mlx = mlx_init();
	inst.win = mlx_new_window(inst.mlx, inst.size.x, inst.size.y, "test");
	inst.img = mlx_new_image(inst.mlx, inst.size.x, inst.size.y);
	t_cam camera;
	camera.rotation = (t_vec3){0, 0, 0};
	camera.pos = (t_vec3){0, 0, -100};
	t_mat4 matrix = ft_mat4_mul(
		ft_mat4_rotation(camera.rotation), 
		ft_mat4_translation(camera.pos)
	);
	camera.matrix = matrix;
	inst.camera = &camera;
	//inst.projection = mat4_isometric();
	inst.projection = mat4_projection_perspective(120, 0.1, 100);

	draw_map(&inst);
	mlx_hook(inst.win, 2, 1, key, &inst);
	mlx_loop(inst.mlx);
	return (0);
}
