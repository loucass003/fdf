/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 21:31:15 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/11 21:25:15 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

void		del_line(void *e, size_t s)
{
	(void)s;
	ft_memdel(&e);
}

void		clean(t_map **map, t_line **content, char **line)
{
	if (map && (*map)->lines)
		ft_lstdel(&((*map)->lines), &del_line);
	ft_memdel((void **)map);
	ft_memdel((void **)content);
	ft_memdel((void **)line);
}

t_line		*read_line(char **values)
{
	t_line	*line;
	size_t	len;

	if (!(line = (t_line*)malloc(sizeof(t_line))))
		return (NULL);
	len = 0;
	while (values[len])
		len++;
	if (!(line->values = (int *)malloc(sizeof(int) * len)))
	{
		ft_memdel((void **)line);
		return (NULL);
	}
	line->len = len;
	line->max = 0;
	line->min = 0;
	while (len-- > 0)
	{
		line->values[len] = ft_atoi(values[len]);
		line->max = fmax(line->values[len], line->max);
		line->min = fmin(line->values[len], line->min);
	}
	return (line);
}

t_map		*read_map(char *file)
{
	int		fd;
	char	*line;
	t_map	*map;
	t_line	*content;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->lines = NULL;
	map->cols = 0;
	map->rows = 0;
	map->min = 0;
	map->max = 0;
	while (ft_gnl(fd, &line) > 0)
	{
		content = read_line(ft_strsplit(line, ' '));
		if (!content || (map->cols > 0 && map->cols != content->len))
		{
			clean(&map, &content, &line);
			return (NULL);
		}
		map->max = fmax(map->max, content->max);
		map->min = fmin(map->min, content->min);
		map->cols = content->len;
		if (!map->lines)
			map->lines = ft_lstnew(content, sizeof(t_line));
		else
			ft_lstput(&(map->lines), ft_lstnew(content, sizeof(t_line)));
		clean(NULL, &content, &line);
		if (!map->lines)
		{
			clean(&map, NULL, NULL);
			return (NULL);
		}
		map->rows++;
	}
	if (map->rows == 0)
		return (NULL);
	map->a = ((float)map->cols / map->rows) / ((float)ft_abs(map->max - map->min) * 10);
	return (map);
}

int		m_value(t_map *map, size_t col, size_t row)
{
	t_list	*line;
	size_t	r;

	if (col > map->cols || row > map->rows)
		return (0);
	line = map->lines;
	r = 0;
	while (r++ < row)
		line = line->next;
	return (((t_line *)line->content)->values[col]);
}
