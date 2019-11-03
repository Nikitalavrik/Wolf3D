/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:24:41 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 15:06:02 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

int		main(int argc, char **argv)
{
	t_coords 	sizes;
	t_coords 	**coords;
	t_wolf3d	*wolf3d;

	if (argc != 2)
		print_error("Whoops, what file I need to open ?\n");
	coords = parse_file(&sizes, argv[1]);
	print_coords(coords, sizes.y, sizes.x);
	wolf3d = init_wolf3d(sizes, coords);
	wolf3d->player = init_player();
	main_loop(wolf3d);
	return (0);
}
