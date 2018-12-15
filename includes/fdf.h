/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:02:19 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 19:38:12 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "stdlib.h"
# include "math.h"

#ifndef __linux__
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
	#define KEY_R (15)
	#define KEY_C (8)
#else
	#define KEY_ESC (65307)
	#define KEY_W (119)
	#define KEY_A (97)
	#define KEY_S (115)
	#define KEY_D (100)
	#define KEY_I (105)
	#define KEY_J (106)
	#define KEY_K (107)
	#define KEY_L (108)
	#define KEY_SHIFT (65505)
	#define KEY_SPACE (32)
	#define KEY_PAGE_U (65365)
	#define KEY_PAGE_D (65366)
	#define KEY_R (114)
	#define KEY_C (99)
#endif

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
	float	z_factor;
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
	float	z_index;
}				t_zpixel;

typedef struct	s_img
{
	int		s_line;
	int		s_pixel;
	int		endian;
	t_pixel	size;
	void	*img_ptr;
	char	*img_buf;
	float	*z_buff;
}				t_img;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_pixel		size;
	t_map		*map;
	t_cam		camera;
	t_bool		grid_mode;
	t_bool		perspective_mode;
}				t_fdf;

int				key_event(int k, t_fdf *inst);
int				close_main(t_fdf *inst, char *msg);

t_cam			init_camera(t_fdf *inst);
void			apply_matrix(t_fdf *inst, t_cam *cam);
t_map			*init_map(char	*file);

t_img			*new_img(t_fdf *inst, t_pixel size);
t_img			*refresh_img(t_img *img);
t_bool			put_pixel(t_img *img, t_zpixel p, int c);
void			clear_img(t_fdf *inst, t_img *img);

t_zpixel		zpixel(t_pixel p);

int				c_rgb(int r, int g, int b);
int				c_gradient(int a, int b, float percent);

void			draw_line(t_img *img, t_zpixel p1, t_zpixel p2, int c[2]);
int				draw_map(t_fdf *inst);
void			draw_filled_map(t_fdf *inst);
void			draw_grid_map(t_fdf *inst);

float			min3f(float a, float b, float c);
float			max3f(float a, float b, float c);
float			edgef(t_vec3 a, t_vec3 b, t_vec3 c);

#endif
