/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:38:31 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 18:25:02 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

int		main_loop(t_wolf3d *wolf3d)
{
	int			quit;
	SDL_Event	event;
	double tmp_dir_x;
	double tmp_plane_x;

	quit = 0;
	while (!quit)
	{
		ft_bzero(wolf3d->surf->pixels, WIDTH * HEIGHT * sizeof(int));
		draw_surface(wolf3d);
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = 1;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					tmp_dir_x = wolf3d->player->dir_x;
					wolf3d->player->dir_x = wolf3d->player->dir_x * cos(ROT) - wolf3d->player->dir_y * sin(ROT);
					wolf3d->player->dir_y = tmp_dir_x * sin(ROT) + wolf3d->player->dir_y * cos(ROT);
					tmp_plane_x = wolf3d->player->plane_x;
					wolf3d->player->plane_x = wolf3d->player->plane_x * cos(ROT) - wolf3d->player->plane_y * sin(ROT);
					wolf3d->player->plane_y  = tmp_plane_x * sin(ROT) + wolf3d->player->plane_y * cos(ROT);
				}
			}
		}
		SDL_UpdateWindowSurface(wolf3d->win);
	}
	return (0);
}