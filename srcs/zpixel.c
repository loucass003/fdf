/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zpixel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 23:23:36 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/11 00:39:13 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_zpixel		zpixel(t_pixel p)
{
	return ((t_zpixel){ p.x, p.y, 0});
}