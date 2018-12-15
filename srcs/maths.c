/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 00:01:16 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 00:36:03 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	min3f(float a, float b, float c)
{
	return (fmin(a, fmin(b, c)));
}

float	max3f(float a, float b, float c)
{
	return (fmax(a, fmax(b, c)));
}

float	edgef(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}
