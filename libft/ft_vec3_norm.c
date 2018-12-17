/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:09:15 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/06 18:33:08 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3		ft_vec3_norm(t_vec3 v)
{
	const float	len = ft_vec3_len(v);

	return (ft_vec3_div(v, (t_vec3) { len, len, len }));
}
