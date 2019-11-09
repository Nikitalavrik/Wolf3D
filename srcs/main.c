/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:24:41 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 16:10:48 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

int		main(int argc, char **argv)
{
	t_coords	sizes;
	t_coords	**coords;
	t_wolf3d	*wolf3d;

	if (argc != 2)
		print_error("Check open : ", "whoops, what file I need to open ?\n");
	ft_printf("Parsing ...\n");
	coords = parse_file(&sizes, argv[1]);
	ft_printf("Structure init ...\n");
	wolf3d = init_wolf3d(sizes, coords);
	wolf3d->player = init_player(coords, sizes);
	ft_printf("Loading textures ...\n");
	load_textures(wolf3d);
	ft_printf("Let`s the play begin !\n");
	main_loop(wolf3d);
	return (0);
}
