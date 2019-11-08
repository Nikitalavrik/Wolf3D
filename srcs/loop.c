/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:38:31 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/08 19:37:52 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	hide_cursor(void)
{
	SDL_Cursor *cursor;
	Uint8 tmp_data[1];
	Uint8	tmp_mask[1];

	tmp_data[0] = 0;
	tmp_mask[0] = 0;
	cursor = SDL_CreateCursor(tmp_data, tmp_mask, 1, 1, 0, 0);
	SDL_SetCursor(cursor);
}

int		main_loop(t_wolf3d *wolf3d)
{
	int			quit;

	double		start_clock;
	// int			 cursorData[2] = {0, 0};

	quit = 0;
	// SDL_SetRelativeMouseMode(SDL_ENABLE);
	hide_cursor();
	while (!quit)
	{
		start_clock = SDL_GetTicks();
		ft_bzero(wolf3d->surf->pixels, WIDTH * HEIGHT * sizeof(int));
		draw_surface(wolf3d);
		draw_minimap(wolf3d);
		quit = detect_event(wolf3d);
		wolf3d->frame = (SDL_GetTicks() - start_clock) / 1000.0;
		// draw_fps(wolf3d);
		// SDL_Flip(wolf3d->surf);
		SDL_UpdateWindowSurface(wolf3d->win);
	}
	return (0);
}