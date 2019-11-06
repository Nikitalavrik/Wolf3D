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

	quit = 0;
	while (!quit)
	{
		ft_bzero(wolf3d->surf->pixels, WIDTH * HEIGHT * sizeof(int));
		draw_surface(wolf3d);
		detect_event(wolf3d);
		SDL_UpdateWindowSurface(wolf3d->win);
	}
	return (0);
}