/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:32:38 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 12:30:47 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

int				check_file(int fd)
{
	char	*line;
	int		size;

	line = NULL;
	size = 0;
	while (get_next_line(fd, &line) == 1)
	{
		ft_memdel((void **)&line);
		size++;
	}
	ft_memdel((void **)&line);
	close(fd);
	return (size);
}

t_coords		**put_coords(t_coords **coords, char **splited, int y, int size)
{
	int			x;

	x = 0;
	while (x < size)
	{
		coords[y][x].x = x;
		coords[y][x].y = y;
		coords[y][x].texture = ft_atoi(splited[x]);
		if (coords[y][x].texture > 9 || coords[y][x].texture < 0)
			print_error("Too big z coord\n");
		x++;
	}
	free_splited(splited, size);
	return (coords);
}

t_coords		**check_lines(int fd, int *in_line,
									t_coords **coords, char *line)
{
	char		**splited;
	int			coords_in_line;
	int			i;

	i = 0;
	*in_line = 0;
	while (get_next_line(fd, &line) == 1)
	{
		splited = ft_strsplit(line, ' ');
		if (!*in_line)
		{
			*in_line = split_len(splited);
			if (!*in_line)
				print_error("Map validation failed\n");
		}
		coords_in_line = split_len(splited);
		if (coords_in_line != *in_line)
			print_error("Map validation failed\n");
		coords[i] = ft_memalloc(sizeof(t_coords) * (*in_line + 1));
		coords = put_coords(coords, splited, i, *in_line);
		ft_memdel((void **)&line);
		i++;
	}
	ft_memdel((void **)&line);
	return (coords);
}

t_coords		**parse_file(t_coords *size, char *filename)
{
	int			fd;
	char		*line;
	t_coords	**coords;

	if ((fd = open(filename, O_RDONLY)) == -1)
		print_error("Something wrong with file\n");
	size->y = check_file(fd);
	if (!size->y)
		print_error("Empty file\n");
	if ((fd = open(filename, O_RDONLY)) == -1)
		print_error("Something wrong with file\n");
	line = NULL;
	coords = ft_memalloc(sizeof(t_coords *) * (size->y + 1));
	coords = check_lines(fd, &size->x, coords, line);
	if (size->x == 1 && size->y == 1)
		print_error("Small map\n");
	close(fd);
	return (coords);
}
