/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 21:31:15 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/13 01:23:12 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	size_t		len;

	len = !(*s == c);
	while (*++s)
		if (s[-1] == c && *s != c)
			len++;
	return (len);
}

static int		ft_atoip(char **str)
{
	char		*o;
	int			result;
	char		mod;

	o = *str;
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
	result = 0;
	mod = **str == '-' || **str == '+' ? *(*str)++ == '-' : 0;
	if (**str >= '0' && **str <= '9')
		while (**str >= '0' && **str <= '9')
			result = result * 10 + *(*str)++ - '0';
	else
	{
		*str = o;
		return (0);
	}
	return (mod ? -result : result);
}

static void		*free_ret(void *addr)
{
	free(addr);
	return (NULL);
}

static int 		*parse_file(const int fd, int *size, int *cols, int *max_height)
{
	char		*line[2];
	int			i;
	int			*arr;

	*cols = 0;
	*size = 0;
	arr = NULL;
	while (ft_gnl(fd, line) > 0)
	{
		if (!*cols)
			*cols = count_words(*line, ' ');
		line[1] = line[0];
		arr = ft_realloc(arr, *size * sizeof(int), (*size + *cols) * sizeof(int));
		i = -1;
		while (++i < *cols)
			if (!**line)
				return (free_ret(arr));
			else if (ft_abs(arr[*size + i] = ft_atoip(line)) > *max_height)
				*max_height = ft_abs(arr[*size + i]);
		if (**line)
			return (free_ret(arr));
		*size += *cols;
		free(line[1]);
	}
	return (arr);
}

t_map			*init_map(char	*file)
{
	int			fd;
	t_map		*map;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->points = parse_file(fd, &map->size, &map->cols, &map->max_height)) || map->size == 0)
	{
		ft_memdel((void **)map);
		return (NULL);
	}
	map->rows = map->size / map->cols;
	map->z_factor = 1;
	return (map);
}