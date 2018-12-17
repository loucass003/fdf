/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:56:27 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/17 15:20:25 by llelievr         ###   ########.fr       */
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

int		close_main(t_fdf *inst, char *msg)
{
	if (!inst)
		return (0);
	if (inst->map)
		ft_memdel((void **)inst->map->points);
	ft_memdel((void **)inst->map);
	if (inst->mlx && inst->win)
	{
		clear_img(inst, inst->img);
		mlx_destroy_window(inst->mlx, inst->win);
	}
	ft_putendl(msg);
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf inst;

	if (argc != 2)
		return (close_main(&inst, "Error: Bad arguments. Usage: ./fdf <map>"));
	inst.win = NULL;
	inst.mlx = NULL;
	if (!(inst.map = init_map(argv[1])))
		return (close_main(&inst, "Error: impossible de lire la map"));
	inst.size = (t_pixel){ 1000, 1000 };
	inst.mlx = mlx_init();
	inst.win = mlx_new_window(inst.mlx, inst.size.x, inst.size.y, "|| FDF ||");
	if (!(inst.img = new_img(&inst, inst.size)))
		return (close_main(&inst, "Error: impossible de creer une image"));
	inst.grid_mode = TRUE;
	inst.perspective_mode = TRUE;
	inst.camera = init_camera(&inst);
	mlx_do_key_autorepeaton(inst.mlx);
	mlx_hook(inst.win, 2, 1, key_event, &inst);
	mlx_hook(inst.win, 17, 0, close_main, &inst);
	mlx_expose_hook(inst.win, draw_map, &inst);
	mlx_loop_hook(inst.mlx, draw_map, &inst);
	mlx_loop(inst.mlx);
	return (close_main(&inst, "Bye Bye."));
}
