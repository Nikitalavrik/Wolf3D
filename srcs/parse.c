/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:32:38 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/08 15:53:17 by nlavrine         ###   ########.fr       */
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

void			check_texture(char *texture)
{
	int i;

	i = 0;
	while (texture[i])
	{
		if (!ft_isdigit(texture[i]))
			print_error(texture," : non digit character\n");
		if (ft_strlen(texture) > 1)
			print_error(texture, " : non valid size\n");
		i++;
	}
}

t_coords		**put_coords(t_coords **coords, char **splited, int y, int size)
{
	int			x;

	x = 0;
	while (x < size)
	{
		coords[y][x].x = x;
		coords[y][x].y = y;
		check_texture(splited[x]);
		coords[y][x].texture = ft_atoi(splited[x]);

		if (coords[y][x].texture > 9 || coords[y][x].texture < 0)
			print_error(splited[x], " : non valid size\n");
		x++;
	}
	free_splited(splited, size);
	return (coords);
}

void			check_close(char **splited, int coords_in_line, t_coords *size, int i)
{
	int	j;

	j = 0;
	if (coords_in_line != size->x)
		print_error(ft_itoa(i + 1), " : line has different size\n");
	if (splited[0][0] == '0' || splited[size->x - 1][0] == '0')
		print_error(ft_itoa(i + 1), " : line hasn`t wall\n");
	if (i == 0 || i == size->y - 1)
		while (splited[j])
		{
			if (!ft_strcmp(splited[j], "0"))
				print_error(ft_itoa(i + 1), " : line hasn`t wall\n");
			j++;
		}
}

t_coords		**check_lines(int fd, t_coords *size,
									t_coords **coords, char *line)
{
	char		**splited;
	int			coords_in_line;
	int			i;

	i = 0;
	size->x = 0;
	while (get_next_line(fd, &line) == 1)
	{
		splited = ft_strsplit(line, ' ');
		if (!size->x)
		{
			size->x = split_len(splited);
			if (!size->x)
				print_error("Map validation : ", "no lines\n");
		}
		coords_in_line = split_len(splited);
		check_close(splited, coords_in_line, size, i);
		coords[i] = ft_memalloc(sizeof(t_coords) * (size->x + 1));
		coords = put_coords(coords, splited, i, size->x);
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
		print_error(filename, " : can`t open file\n");
	size->y = check_file(fd);
	if (!size->y)
		print_error(filename, " : empty\n");
	if ((fd = open(filename, O_RDONLY)) == -1)
		print_error(filename, " : can`t open file\n");
	line = NULL;
	coords = ft_memalloc(sizeof(t_coords *) * (size->y + 1));
	coords = check_lines(fd, size, coords, line);
	close(fd);
	return (coords);
}
