/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:38:44 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 13:17:41 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

t_wolf3d	*init_wolf3d(void)
{
	t_wolf3d	*wolf3d;

	wolf3d = ft_memalloc(sizeof(t_wolf3d));
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ft_printf("HELLLLLLOOOO\n");
	}
	wolf3d->win = SDL_CreateWindow("Hello, SDL 2!", 0, 0, 1280, 720, SDL_WINDOW_SHOWN);
	if (!wolf3d->win)
		ft_printf("win drope\n");
	wolf3d->screen_surface = SDL_GetWindowSurface(wolf3d->win);
    // SDL_FillRect(wolf3d->screen_surface, NULL, SDL_MapRGB( wolf3d->screen_surface->format, 0, 255, 0));
    SDL_UpdateWindowSurface(wolf3d->win);
    SDL_Delay(8000);
    SDL_DestroyWindow(wolf3d->win);
    SDL_Quit();
	return (wolf3d);
}
