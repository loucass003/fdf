/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:56:27 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/06 22:47:44 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <unistd.h>

int		key(int k, void *pram)
{
	(void)k;
	(void)pram;
	return (0);
}

t_mat4	mat4_projection_perspective(float angle, float near, float far)
{
	const float	scale = 1 / tanf(angle * 0.5 * M_PI / 180);
	const float	a = -far / (far - near);
	const float	b = (-far * near) / (far - near);
	return ((t_mat4)((t_mat4_data) {
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, a, b,
		0, 0, -1, 0
	}));
}

#define SQRT36 (0.70710678118)
#define SQRT26 (0.57735026919)

t_mat4	mat4_isometric()
{
	return ((t_mat4)(t_mat4_data) {
		SQRT36, 0, 0, -SQRT36,
		1     , 2, 1, 0,
		SQRT26, -SQRT26, SQRT26, 0,
		0    , 0    , -1 , 0
	});
}

/*static t_mat4	s_rotate_x(float a)
{
	return ((t_mat4)((t_mat4_data){
		1, 0, 0, 0,
		0, cosf(a), -sinf(a), 0,
		0, sinf(a), cosf(a), 0,
		0, 0, 0, 1
	}));
}*/

/*static t_mat4	s_rotate_y(float a)
{
	return ((t_mat4)((t_mat4_data) {
		cosf(a), 0, sinf(a), 0,
		0, 1, 0, 0,
		-sinf(a), 0, cosf(a), 0,
		0, 0, 0, 1
	}));
}*/

/*static t_mat4	s_rotate_z(float a)
{
	return ((t_mat4)((t_mat4_data) {
		cosf(a), -sinf(a), 0, 0,
		sinf(a), cosf(a), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	}));
}*/

t_pixel	project(t_cam cam, t_mat4 projection, t_vec3 p)
{
	t_vec3 vec;
	//vec = ft_mat4_mulv(s_rotate_y(M_PI), p);
	//vec = ft_mat4_mulv(s_rotate_z(M_PI_4), p);
	vec = ft_mat4_mulv(cam.pos, p);
	vec = ft_mat4_mulv(projection, vec);
	t_pixel pi = (t_pixel){ 
		(int)((vec.x + 1) * 0.5 * 500), 
		(int)((1 - (vec.y + 1) * 0.5) * 500)
	};
	printf("(%d, %d)", pi.x, pi.y);
	return (pi);
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
	t_cam cam;
	cam.rotation = ft_mat4_rotation((t_vec3){0, 0, 0});
	cam.pos = ft_mat4_translation((t_vec3){5, 0, -20});

	//t_mat4 projection = mat4_isometric();
	t_mat4 projection = mat4_projection_perspective(90, 0.1, 100);
	while (lst)
	{
		t_line *line = lst->content;
		col = 0;
		while (col < map->cols)
		{
			t_vec3 a = (t_vec3){col, row, (line->values[col]) * 0.2};
			t_pixel pixel = project(cam, projection, a);
			t_pixel pixel2;
			t_line *n_line = lst->next ? (lst->next)->content : NULL;
			if (col + 1 < map->cols)
			{
				a = (t_vec3){(col + 1), row, (line->values[col + 1]) * 0.2};
				pixel2 = project(cam, projection, a);
				int c = line->values[col + 1] > 0 ? 0x0000FF00 : 0x00FF0000;
				//draw Hline (to ((col + 1), row))
				draw_line(mlx, window, pixel, pixel2, c);
			}
			if (col < map->cols && n_line)
			{
				a = (t_vec3){col, (row + 1), (n_line->values[col]) * 0.2};
				pixel2 = project(cam, projection, a);
				//draw Vline (to (col, (row + 1)))
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
