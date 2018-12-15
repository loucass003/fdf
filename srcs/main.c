/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:56:27 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 02:11:43 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <unistd.h>

int		draw_map(t_fdf *inst)
{
	refresh_img(inst->img);
	if (inst->grid_mode)
		draw_grid_map(inst);
	else
		draw_filled_map(inst);
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img->img_ptr, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf inst;

	if (argc != 2)
		return (0);
	if (!(inst.map = init_map(argv[1])))
	{
		ft_putstr("Error: impossible de lire la map\n");
		return (0);
	}
	inst.size = (t_pixel){ 1000, 1000 };
	inst.grid_mode = TRUE;
	inst.perspective_mode = TRUE;
	inst.mlx = mlx_init();
	inst.win = mlx_new_window(inst.mlx, inst.size.x, inst.size.y, "|| FDF ||");
	inst.img = new_img(&inst, inst.size);
	inst.camera = init_camera(&inst);
	draw_map(&inst);
	mlx_hook(inst.win, 2, 1, key_event, &inst);
	mlx_expose_hook(inst.win, &draw_map, &inst);
	mlx_loop(inst.mlx);
	return (0);
}
