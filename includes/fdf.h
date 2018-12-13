/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:02:19 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/13 02:26:16 by llelievr         ###   ########.fr       */
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

typedef struct	s_map
{
	int		*points;
	int		z_factor;
	int		max_height;
	int		size;
	int		cols;
	int		rows;
}				t_map;

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		rotation;
	t_mat4		matrix;
	t_mat4		projection;
}				t_cam;

typedef struct	s_zpixel
{
	int		x;
	int		y;
	int		z_index;
	int		color;
}				t_zpixel;

typedef struct	s_img
{
	int		s_line;
	int		s_pixel;
	int		endian;
	t_pixel	size;
	void	*img_ptr;
	char	*img_buf;
}				t_img;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	t_zpixel	*p_img;
	t_img		*img;
	t_pixel		size;
	t_map		*map;
	t_cam		camera;
}				t_fdf;

t_cam			init_camera(void);
void			apply_matrix(t_cam *cam);
t_map			*init_map(char	*file);

t_img			*new_img(t_fdf *inst, t_pixel size);


t_zpixel		zpixel(t_pixel p);

t_mat4			cam_view(t_cam *cam, float yaw, float pitch);

int				c_rgb(int r, int g, int b);

t_bool			put_pixel(t_fdf *inst, t_zpixel p);
void			draw_line(t_fdf *inst, t_zpixel p1, t_zpixel p2);
int				draw_map(t_fdf *inst);


#endif
