/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:35:45 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/04 15:36:08 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3		vec3_add(t_vec3 p, float x, float y, float z)
{
	p.x += x;
	p.y += y;
	p.z += z;
	return (p);
}

t_vec3		vec3_addv(t_vec3 p1, t_vec3 p2)
{
	return (vec3_add(p1, p2.x, p2.y, p2.z));
}