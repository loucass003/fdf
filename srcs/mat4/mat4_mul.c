/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:07:35 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/05 15:31:50 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4			mat4_mul(t_mat4 s, t_mat4 m)
{
	t_mat4	o;

	o.x = vec4_mul(s.x, m.x.x, m.y.x, m.z.x, m.w.x);
	o.y = vec4_mul(s.y, m.x.y, m.y.y, m.z.y, m.w.y);
	o.z = vec4_mul(s.z, m.x.z, m.y.z, m.z.z, m.w.z); 
	o.w = vec4_mul(s.w, m.x.w, m.y.w, m.z.w, m.w.w);
	return (o);
}