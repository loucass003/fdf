/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:49:12 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/14 18:18:11 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float		ft_sqrt(int n)
{
	float	out;
	float	last;

	if (n <= 0)
		return (0);
	last = 0;
	out = n / 2;
	while (out != last)
	{
		last = out;
		out = 0.5 * (out + n / out);
	}
	return (out);
}
