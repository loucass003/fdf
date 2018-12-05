/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:10:30 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/04 15:36:19 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3		vec3_div(t_vec3 p, float x, float y, float z)
{
	p.x /= x;
	p.y /= y;
	p.z /= z;
	return (p);
}

t_vec3		vec3_divv(t_vec3 p1, t_vec3 p2)
{
	return (vec3_div(p1, p2.x, p2.y, p2.z));
}