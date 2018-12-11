/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:02:19 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/11 13:22:52 by llelievr         ###   ########.fr       */
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
	int		min;
	int		max;
}				t_line;

typedef struct	s_map
{
	t_list		*lines;
	size_t		cols;
	size_t		rows;
	int		min;
	int		max;
	float		a;
}				t_map;

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		rotation;
	t_mat4		matrix;
}				t_cam;

typedef struct	s_zpixel
{
	int		x;
	int		y;
	int		z_index;
	int		color;
}				t_zpixel;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	t_zpixel	*p_img;
	void		*img;
	t_pixel		size;
	t_map		*map;
	t_cam		*camera;
	t_mat4		projection;
}				t_fdf;



t_zpixel		zpixel(t_pixel p);

t_mat4			cam_view(t_cam *cam, float yaw, float pitch);

int				c_rgb(int r, int g, int b);

t_bool			put_pixel(t_fdf *inst, t_zpixel p);
void			draw_line(t_fdf *inst, t_zpixel p1, t_zpixel p2);
void			draw_map(t_fdf *inst);

t_map			*read_map(char *file);

int				m_value(t_map *map, size_t col, size_t row);

#endif
