/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:38:44 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/06 14:52:15 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

t_wolf3d	*init_wolf3d(t_coords sizes, t_coords **coords)
{
	t_wolf3d	*wolf3d;
 	// int 		image_flags;

	wolf3d = ft_memalloc(sizeof(t_wolf3d));
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		print_error("SDL Init error\n");
	wolf3d->win = SDL_CreateWindow("Wolf3D", 650, 300, 1280, 720, SDL_WINDOW_SHOWN);
	if (!wolf3d->win)
		print_error("SDL Window create error\n");
	// image_flags = IMG_INIT_PNG;
	// if (!(IMG_Init(image_flags) & image_flags))
	// 	print_error("SDL Image init error\n");
	wolf3d->surf = SDL_GetWindowSurface(wolf3d->win);
	wolf3d->width = sizes.x;
	wolf3d->height = sizes.y;
	wolf3d->coords = coords;
	return (wolf3d);
}

t_player	*init_player(void)
{
	t_player	*player;

	player = ft_memalloc(sizeof(t_player));
	player->x = 3;
	player->y = 3;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	return (player);
}
