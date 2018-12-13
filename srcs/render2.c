/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:15:45 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/13 03:59:17 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_bool	project(t_fdf *inst, t_vec3 p_raster, t_vec3 *raster)
{
	t_vec3 vec;
	vec = ft_vec3_mul(p_raster, (t_vec3){1, -1, 1});
	vec = ft_vec3_div(vec, (t_vec3){inst->map->cols, inst->map->max_height, inst->map->rows});
	vec = ft_mat4_mulv(inst->camera.matrix, vec);

	//printf("point -> (%f, %f, %f)\n", vec.x, vec.y, vec.z);
	if (vec.x < -2 || vec.x > 2 || vec.y < -2 || vec.y > 2 || vec.z < -1)
		return (FALSE);

	*raster = ((t_vec3){
		((vec.x + 1) * 0.5 * inst->size.x),
		((1 - (vec.y + 1) * 0.5) * inst->size.y),
		-vec.z
	});
	return (TRUE);
}

t_bool			put_pixel(t_fdf *inst, t_zpixel p)
{
	if (p.x < 0 || p.x >= inst->size.x - 1 || p.y < 0 || p.y >= inst->size.y - 1)
		return (FALSE);
	if (p.z_index < inst->p_img[(p.y * inst->size.x) + p.x].z_index)
		return (FALSE);
	inst->p_img[(p.y * inst->size.x) + p.x] = p;
	return (TRUE);
}

float 			min3(float a, float b, float c) 
{ 
	return fmin(a, fmin(b, c));
}  
 
float 			max3(float a, float b, float c) 
{ 
	return fmax(a, fmax(b, c)); 
}

float edgeFunction(const t_vec3 a, const t_vec3 b, const t_vec3 c)
{ 
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
} 

t_img			*refresh_img(t_img *img)
{
	if (!!(img->img_buf = mlx_get_data_addr(img->img_ptr, &img->s_pixel, &img->s_line, &img->endian)))
		ft_bzero(img->img_buf, (img->size.y * img->s_line));
	return (img);
}

static float	ft_absf(float f)
{
	return (f < 0 ? -f : f);
}

static int rgb(float percent)
{
	//printf("%f\n", percent);
	if (percent < 0)
	{
		int p = ft_absf(percent);

		int r = (0 + (78 - 0) * p);
		int g = (255 + (46 - 255) * p);
		int b = (0 + (40 - 0) * p);
		return (c_rgb(r, g, b));
	}
	if (percent == 0)
		return (c_rgb(70,130, 180));
	
	int r = (0 + (255 - 0) * percent);
    int g = (255 + (0 - 255) * percent);
    int b = (0 + (0 - 0) * percent);

    return c_rgb(r, g, b);
}

int			draw_map(t_fdf *inst)
{
	t_pixel	p;
	t_vec3	vert[3];
//	int		v;
//	int		even;
	
	p = (t_pixel){-1, -1};
	refresh_img(inst->img);
	float *depthBuffer = malloc(sizeof(float) * (inst->size.x * inst->size.y));
    for (int i = 0; i < inst->size.x * inst->size.y; ++i) 
		depthBuffer[i] = 1000;
	while (p.y++ < inst->map->rows - 2)
	{
		p.x = -1;
		while (p.x++ < inst->map->cols - 2)
		{
			for (int j = 0; j < 2; j++)
			{
				if (j == 0)
				{
					vert[2] = (t_vec3){p.x, inst->map->points[(p.y * inst->map->cols) + p.x], p.y};
					vert[1] = (t_vec3){p.x + 1, inst->map->points[(p.y * inst->map->cols) + p.x + 1], p.y};
					vert[0] = (t_vec3){p.x, inst->map->points[((p.y + 1) * inst->map->cols) + p.x], p.y + 1};
					//printf("part1\n");
				}
				else
				{
					
					vert[1] = (t_vec3){p.x, inst->map->points[((p.y + 1) * inst->map->cols) + p.x], p.y + 1};
					vert[2] = (t_vec3){p.x + 1, inst->map->points[((p.y + 1)* inst->map->cols) + p.x + 1], p.y + 1};
					vert[0] = (t_vec3){p.x + 1, inst->map->points[((p.y) * inst->map->cols) + p.x + 1], p.y};
					//printf("part2\n");
				}
				/*if (p.y + (even ? 1 : -1) < 0 || p.y + (even ? 1 : -1) >= inst->map->rows)
					continue;*/
				
			//	printf("% 3d ",  inst->map->points[(p.y * inst->map->cols) + p.x]);
				t_vec3 a_r, b_r, c_r;
				project(inst, vert[0], &a_r);
				project(inst, vert[1], &b_r);
				project(inst, vert[2], &c_r);
				
				a_r.z = 1 / a_r.z;
				b_r.z = 1 / b_r.z;
				c_r.z = 1 / c_r.z;

				t_vec2 born_x = (t_vec2){ min3(a_r.x, b_r.x, c_r.x), max3(a_r.x, b_r.x, c_r.x) };
				t_vec2 born_y = (t_vec2){ min3(a_r.y, b_r.y, c_r.y), max3(a_r.y, b_r.y, c_r.y) };

				if (born_x.x > inst->size.x - 1 || born_x.y < 0 || born_y.x > inst->size.y - 1 || born_y.y < 0)
					continue ;

				int x0 = fmax(0, (int)(floor(born_x.x))); 
				int x1 = fmin(inst->size.x - 1, (int)(floor(born_x.y)));
				int y0 = fmax(0, (int)(floor(born_y.x))); 
				int y1 = fmin(inst->size.y - 1, (int)(floor(born_y.y)));

				float area = edgeFunction(a_r, b_r, c_r);
				for (int y = y0; y <= y1; ++y) 
				{ 
					for(int x = x0; x <= x1; ++x) 
					{
						t_vec3 pixelSample = (t_vec3){x + 0.5, y + 0.5, 0};
						float w0 = edgeFunction(b_r, c_r, pixelSample);
						float w1 = edgeFunction(c_r, a_r, pixelSample);
						float w2 = edgeFunction(a_r, b_r, pixelSample);
						if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
							w0 /= area;
							w1 /= area;
							w2 /= area;
							float oneOverZ = a_r.z * w0 + b_r.z * w1 + c_r.z * w2; 
							float z = 1 / oneOverZ;
							if (z < depthBuffer[y * inst->size.x + x]) { 
								depthBuffer[y * inst->size.x + x] = z;
								int c =  c_rgb(0, 0, rgb(ft_absf(vert[0].y / inst->map->max_height)));
								ft_memmove(inst->img->img_buf + (y * inst->img->s_line) + (x * 4), &c, 4);
							} 
						}
					}
				}
			}
		}
	//	printf("\n");
	}
	mlx_put_image_to_window(inst->mlx, inst->win, inst->img->img_ptr, 0, 0);
	return (0);
}


/*


t_vec3 a = (t_vec3){col, -(line->values[col]), row};
t_line *n_line = lst->next ? (lst->next)->content : NULL;
if (col + 1 >= (inst->map)->cols)
	continue ;
t_vec3 b = (t_vec3){(col + 1), -(line->values[col + 1]), row};
int even = (y % 2 == 0);
t_vec3 c = (t_vec3){col + (!even), -(n_line->values[col]), row + 1};

t_vec3 a_r, b_r, c_r;
project(inst, a, &a_r);
project(inst, b, &b_r);
project(inst, c, &c_r);

a_r.z = 1 / a_r.z;
b_r.z = 1 / b_r.z;
c_r.z = 1 / c_r.z;

t_vec2 born_x = (t_vec2){ min3(a.x, b.x, c.x), max3(a.x, b.x, c.x) };
t_vec2 born_y = (t_vec2){ min3(a.y, b.y, c.y), max3(a.y, b.y, c.y) };

if (born_x.x > inst->size.x - 1 || born_x.y < 0 || born_y.x > inst->size.y - 1 || born_y.y < 0)
	continue ;

int x0 = fmax(0, (int)(floor(born_x.x))); 
int x1 = fmin(inst->size.x - 1, (int)(floor(born_x.y)));
int y0 = fmax(0, (int)(floor(born_y.x))); 
int y1 = fmin(inst->size.y - 1, (int)(floor(born_y.y)));

float area = 0;
for (int y = y0; y <= y1; ++y)
{ 
	for(int x = x0; x <= x1; ++x)
	{
		
	}
}



*/