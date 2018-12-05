/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:30:51 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/04 15:36:33 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3		vec3_sub(t_vec3 p, float x, float y, float z)
{
	p.x -= x;
	p.y -= y;
	p.z -= z;
	return (p);
}

t_vec3		vec3_subv(t_vec3 p1, t_vec3 p2)
{
	return (vec3_sub(p1, p2.x, p2.y, p2.z));
}