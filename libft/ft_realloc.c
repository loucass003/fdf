/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:29:20 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/15 01:46:35 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *o_ptr, size_t oldsize, size_t newsize)
{
	void	*ptr;

	ptr = malloc(newsize);
	if (oldsize)
	{
		ft_memcpy(ptr, o_ptr, oldsize);
		free(o_ptr);
	}
	return (ptr);
}
