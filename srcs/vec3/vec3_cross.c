/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:42:54 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/05 11:47:13 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	vec3_cross(t_vec3 self, t_vec3 v)
{
	return (vec3(
		self.y * v.z - self.z * v.y,
		self.z * v.x - self.x * v.z,
		self.x * v.y - self.y * v.x
	));
}