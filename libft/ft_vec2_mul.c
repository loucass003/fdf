/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2_mul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:59:13 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/12 15:26:30 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec2		ft_vec2_mul(t_vec2 a, t_vec2 b)
{
	a.x *= b.x;
	a.y *= b.y;
	return (a);
}
