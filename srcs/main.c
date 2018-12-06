/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:56:27 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/05 20:48:37 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		key(int k, void *pram)
{
	(void)k;
	(void)pram;
	return (0);
}

/*t_vec2	project(t_mat4 world_2_cam, t_mat4 projection, t_vec3 a)
{
	t_vec3 c = mat4_mulv(world_2_cam, a);
	t_vec3 projected = mat4_mulv(projection, c);
	int x = fmin(500, (((projected.x + 1) * 0.5) * 500));
	int y = fmin(500, ((1 - (projected.y + 1) * 0.5) * 500));
	return (vec2(x, y));
}*/

t_vec2		project(t_vec3 c, t_vec3 a)
{
	//t_vec3 e = vec3(0, 0, 0.1);
	t_mat4 m = mat4_identity();
	t_vec3 d = mat4_mulv(m, vec3_subv(a, c));
	t_vec2 b = vec2((d.x * 500) / (d.z * 500) * 100, (d.y * 500) / (d.z * 500) * 100);
	printf("project (%d, %d)\n", b.x, b.y);
	return (b);
}

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_map	*map;

	if (argc != 2)
		return (0);
	map = read_map(argv[1]);
	if (!map)
	{
		ft_putstr("Error: impossible de lire la map\n");
		return (0);
	}
	//printf("%d\n", m_value(map, 5, 5));
	
	mlx = mlx_init();
	window = mlx_new_window(mlx, 500, 500, "test");
	t_list *lst = map->lines;
	size_t row = 0;
	size_t col;
	//t_mat4 projection = mat4_projection(30, 1, 1000);
	/*t_mat4 world_2_cam = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(0, 1, 1, 0)
	);*/
	t_vec3 c = vec3(0, 0, -10);
	
	while (lst)
	{
		t_line *line = lst->content;
		col = 0;
		while (col < map->cols)
		{
			t_vec3 a = vec3(col * 2, row * 2, (line->values[col]) * 0.05);
			t_vec2 pixel = project(c, a);
			t_vec2 pixel2;
			t_line *n_line = lst->next ? (lst->next)->content : NULL;
			if (col + 1 < map->cols)
			{
				a = vec3((col + 1) * 2, row * 2, (line->values[col + 1]) * 0.05);
				pixel2 = project(c, a);
				int c = line->values[col + 1] > 0 ? 0x0000FF00 : 0x00FF0000;
				//draw Hline (to ((col + 1) * 2, row * 2))
				draw_line(mlx, window, pixel, pixel2, c);
			}
			if (col < map->cols && n_line)
			{
				a = vec3(col * 2, (row + 1) * 2, (n_line->values[col]) * 0.05);
				pixel2 = project(c, a);
				//draw Vline (to (col * 2, (row + 1) * 2))
				int c = n_line->values[col] > 0 ? 0x0000FF00 : 0x00FF0000;
				draw_line(mlx, window, pixel, pixel2, c);
			}
			col++;
		}
		lst = lst->next;
		row++;
	}
	mlx_pixel_put(mlx, window, 250, 250, 0x00FF0000);
	/*draw_line(mlx, window, vec2(0,0), vec2(500, 500), 0x00FF00FF);
	draw_line(mlx, window, vec2(0,500), vec2(500, 0), 0x00FF00FF);
	draw_line(mlx, window, vec2(250,250), vec2(0, 15), 0x0000FF00);
	draw_line(mlx, window, vec2(250,250), vec2(0, 485), c_rgb(0, 0, 255));*/
	mlx_key_hook(window, key, (void *)0);
	mlx_loop(mlx);
	return (0);
}