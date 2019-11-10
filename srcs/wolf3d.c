/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:38:44 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/10 12:37:25 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void		init_music_font(t_wolf3d *wolf3d)
{
	TTF_Init();
	wolf3d->font = TTF_OpenFont("fonts/Aller_b.ttf", 24);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		print_error("SDL : ", " mixer didn`t init\n");
	wolf3d->music = Mix_LoadMUS("music/Majestic.mp3");
	if (!wolf3d->music)
		print_error("SDL : ", "cant`t find music\n");
	Mix_PlayMusic(wolf3d->music, -1);
	wolf3d->mouse = 0;
}

t_wolf3d	*init_wolf3d(t_coords sizes, t_coords **coords)
{
	t_wolf3d	*wolf3d;

	wolf3d = ft_memalloc(sizeof(t_wolf3d));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		print_error("SDL : ", "init error\n");
	wolf3d->win = SDL_CreateWindow("Wolf3D", 650, 300, WIDTH,
											HEIGHT, SDL_WINDOW_SHOWN);
	if (!wolf3d->win)
		print_error("SDL : ", "window create error\n");
	wolf3d->surf = SDL_GetWindowSurface(wolf3d->win);
	wolf3d->width = sizes.x;
	wolf3d->height = sizes.y;
	wolf3d->coords = coords;
	wolf3d->fg.r = 252;
	wolf3d->fg.g = 136;
	wolf3d->fg.b = 3;
	wolf3d->fg.a = 255;
	wolf3d->speed = 0.05;
	wolf3d->txt = 1;
	init_music_font(wolf3d);
	return (wolf3d);
}

void		put_player(t_player *player, t_coords **coords, t_coords size)
{
	int y;
	int x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (!coords[y][x].texture)
			{
				player->x = x;
				player->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	print_error("Player : ", "can`t find place to put on\n");
}

t_player	*init_player(t_coords **coords, t_coords size)
{
	t_player	*player;

	player = ft_memalloc(sizeof(t_player));
	put_player(player, coords, size);
	player->x += 0.5;
	player->y += 0.5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	return (player);
}
