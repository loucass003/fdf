/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 01:23:08 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/29 21:58:07 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		translations(int k, t_fdf *inst, t_vec3 *incrt)
{
	if (k == KEY_A || k == KEY_D)
	{
		*incrt = (t_vec3){ .x = cosf(inst->camera.rotation.y),
		.z = sinf(inst->camera.rotation.y) };
		if (!inst->perspective_mode)
			*incrt = (t_vec3){ .x = 5 };
		if (k == KEY_D)
			*incrt = ft_vec3_inv(*incrt);
	}
	if (k == KEY_W || k == KEY_S)
	{
		*incrt = (t_vec3){ sinf(inst->camera.rotation.y),
		-sinf(inst->camera.rotation.x), -cosf(inst->camera.rotation.y) };
		if (!inst->perspective_mode)
			*incrt = (t_vec3){ .z = 5 };
		if (k == KEY_W)
			*incrt = ft_vec3_inv(*incrt);
	}
	if (k == KEY_SHIFT || k == KEY_SPACE)
		incrt->y = (k == KEY_SHIFT ? -2 : 2);
}

static void		rotations(int k, t_fdf *inst, t_vec3 *incrr)
{
	(void)inst;
	if (k == KEY_I || k == KEY_K)
		incrr->x = (k == KEY_I ? 0.05 : -0.05);
	if (k == KEY_J || k == KEY_L)
		incrr->y = (k == KEY_J ? -0.1 : 0.1);
}

static void		misc(int k, t_fdf *inst)
{
	if (k == KEY_PAGE_U || k == KEY_PAGE_D)
		inst->map->z_factor += (k == KEY_PAGE_U ? 0.001 : -0.001);
	if (k == KEY_R)
		inst->grid_mode = !inst->grid_mode;
	if (k == KEY_C)
	{
		inst->perspective_mode = !inst->perspective_mode;
		inst->camera = init_camera(inst);
	}
}

int				key_event(int k, t_fdf *inst)
{
	t_vec3			incrt;
	t_vec3			incrr;
	const float		speed = 0.03;

	incrr = (t_vec3){0, 0, 0};
	incrt = (t_vec3){0, 0, 0};
	if (k == KEY_ESC)
		return (close_main(inst, NULL));
	translations(k, inst, &incrt);
	rotations(k, inst, &incrr);
	misc(k, inst);
	incrt = ft_vec3_mul(incrt, (t_vec3){speed, speed, speed});
	inst->camera.rotation = ft_vec3_add(inst->camera.rotation, incrr);
	inst->camera.pos = ft_vec3_add(inst->camera.pos, incrt);
	apply_matrix(inst, &inst->camera);
	return (0);
}
