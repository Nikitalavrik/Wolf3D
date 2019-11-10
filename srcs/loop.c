/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:38:31 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/10 12:38:15 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

int		main_loop(t_wolf3d *wolf3d)
{
	int			quit;
	double		start_clock;

	quit = 0;
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	while (!quit)
	{
		start_clock = SDL_GetTicks();
		ft_bzero(wolf3d->surf->pixels, WIDTH * HEIGHT * sizeof(int));
		draw_surface(wolf3d);
		draw_minimap(wolf3d);
		quit = detect_event(wolf3d);
		wolf3d->frame = (SDL_GetTicks() - start_clock) / 1000.0;
		draw_fps(wolf3d);
		SDL_UpdateWindowSurface(wolf3d->win);
	}
	SDL_FreeSurface(wolf3d->surf);
	SDL_DestroyWindow(wolf3d->win);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	return (0);
}
