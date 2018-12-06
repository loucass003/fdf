/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:02:19 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/06 21:46:52 by llelievr         ###   ########.fr       */
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
** Camera
*/

typedef struct	s_cam
{
	t_mat4		pos;
	t_mat4		rotation;
	t_vec3		up;
}				t_cam;

int				c_rgb(int r, int g, int b);

void			draw_line(void *mlx, void *window, t_pixel p1, t_pixel p2, int color);

t_map			*read_map(char *file);

int				m_value(t_map *map, size_t col, size_t row);

#endif
