/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:02:19 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/05 18:57:31 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "stdlib.h"
# include "math.h"

typedef enum	e_bool
{
	TRUE			= 1,
	FALSE			= 0,
	TRUENT			= 0,
	FALSENT			= 1,
	LA_TETE_A_TOTO	= 0
}				t_bool;

typedef struct	s_line
{
	int			*values;
	size_t		len;
}				t_line;

typedef struct	s_map
{
	t_list		*lines;
	size_t		cols;
	size_t		rows;
}				t_map;

/*
** Vectors
*/

typedef struct	s_vec2
{
	int		x;
	int		y;
}				t_vec2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

t_vec2			vec2(int x, int y);
t_vec2			vec2_cpy(t_vec2 p);

t_vec2			vec2_mul(t_vec2 p, int x, int y);
t_vec2			vec2_mulv(t_vec2 p1, t_vec2 p2);
t_vec2			vec2_div(t_vec2 p, int x, int y);
t_vec2			vec2_divv(t_vec2 p1, t_vec2 p2);
t_vec2			vec2_sub(t_vec2 p, int x, int y);
t_vec2			vec2_subv(t_vec2 p1, t_vec2 p2);
t_vec2			vec2_add(t_vec2 p, int x, int y);
t_vec2			vec2_addv(t_vec2 p1, t_vec2 p2);
t_vec2			*vec2_set(t_vec2 *p, int x, int y);
t_vec2			*vec2_setv(t_vec2 *p1, t_vec2 p2);

t_vec3			vec3(float x, float y, float z);
t_vec3			vec3_cpy(t_vec3 p);

float			vec3_len(t_vec3 p);
t_vec3			vec3_norm(t_vec3 p);
t_vec3			vec3_cross(t_vec3 self, t_vec3 v);
t_vec3			vec3_mul(t_vec3 p, float x, float y, float z);
t_vec3			vec3_mulv(t_vec3 p1, t_vec3 p2);
t_vec3			vec3_div(t_vec3 p, float x, float y, float z);
t_vec3			vec3_divv(t_vec3 p1, t_vec3 p2);
t_vec3			vec3_sub(t_vec3 p, float x, float y, float z);
t_vec3			vec3_subv(t_vec3 p1, t_vec3 p2);
t_vec3			vec3_add(t_vec3 p, float x, float y, float z);
t_vec3			vec3_addv(t_vec3 p1, t_vec3 p2);
t_vec3			*vec3_set(t_vec3 *p, float x, float y, float z);
t_vec3			*vec3_setv(t_vec3 *p1, t_vec3 p2);

t_vec4			vec4(float x, float y, float z, float w);
t_vec4			vec4_cpy(t_vec4 p);
t_vec4			vec4_3(float x, float y, float z);
t_vec4			vec4_3v(t_vec3 v);

t_vec4			vec4_mul(t_vec4 p, float x, float y, float z, float w);
t_vec4			vec4_mulv(t_vec4 p1, t_vec4 p2);
t_vec4			vec4_div(t_vec4 p, float x, float y, float z, float w);
t_vec4			vec4_divv(t_vec4 p1, t_vec4 p2);
t_vec4			vec4_sub(t_vec4 p, float x, float y, float z, float w);
t_vec4			vec4_subv(t_vec4 p1, t_vec4 p2);
t_vec4			vec4_add(t_vec4 p, float x, float y, float z, float w);
t_vec4			vec4_addv(t_vec4 p1, t_vec4 p2);
t_vec4			*vec4_set(t_vec4 *p, float x, float y, float z, float w);
t_vec4			*vec4_setv(t_vec4 *p1, t_vec4 p2);

/*
** Matrices
*/

typedef struct 	s_mat4
{
	t_vec4		x;
	t_vec4		y;
	t_vec4		z;
	t_vec4		w;
}				t_mat4;

t_mat4			mat4(t_vec4 x, t_vec4 y, t_vec4 z, t_vec4 w);
t_mat4			mat4_identity();
//t_mat4			mat4_rotation(float angle, t_vec3 axis);
t_mat4			mat4_rotate_x(float a);
t_mat4			mat4_mul_saclar(t_mat4 self, float v);
t_mat4			mat4_mul(t_mat4 self, t_mat4 m);
t_vec3			mat4_mulv(t_mat4 m, t_vec3 src);
t_mat4			mat4_projection(float angleView, float near, float far);
t_mat4			mat4_cam_transform(t_vec3 target, t_vec3 up);

/*
** Camera
*/

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		target;
	t_vec3		up;
}				t_cam;

int				c_rgb(int r, int g, int b);

void			draw_line(void *mlx, void *window, t_vec2 p1, t_vec2 p2, int color);

t_map			*read_map(char *file);

int				m_value(t_map *map, size_t col, size_t row);

#endif